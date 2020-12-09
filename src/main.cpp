/*
  PlayOpusExample - main.c
  Simple example to play an Opus file on an nRF52.
  
  Copyright (C) 2020  Sean Reynolds
  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.
  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.
  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <Arduino.h>
#include <Adafruit_SPIFlash.h>
#include <Adafruit_USBD_MSC.h>
#include <nrfx_i2s.h> // Adafruit's nRF52 core doesn't include this.
#include "libopus/opus.h"
#include "ogg_stripper.h"

#ifndef NRFX_I2S_DEFAULT_CONFIG_IRQ_PRIORITY
#define NRFX_I2S_DEFAULT_CONFIG_IRQ_PRIORITY 7
#endif

#define PIN_LRCK    NRF_GPIO_PIN_MAP(0, 27) // D10
#define PIN_SCK    NRF_GPIO_PIN_MAP(0, 6) // D11
#define PIN_MCK   NRF_GPIO_PIN_MAP(0, 7) // D12
#define PIN_SDOUT  NRF_GPIO_PIN_MAP(0, 26) // D9
#define BUFFER_LENGTH 1920

#define OGG_BUF_LEN 0xFF

void playFile(void);
int32_t msc_write_cb (uint32_t lba, uint8_t* buffer, uint32_t bufsize);
int32_t msc_read_cb (uint32_t lba, void* buffer, uint32_t bufsize);
void msc_flush_cb (void);
static void data_handler(nrfx_i2s_buffers_t const * p_released, uint32_t status);
void loadBuffer(int16_t * dest, const int16_t * src, size_t samples);

File dataFile;
OpusDecoder *decoder;

uint32_t offset = 0;

uint8_t oggBuf[OGG_BUF_LEN];

int16_t bufA[BUFFER_LENGTH];
int16_t bufB[BUFFER_LENGTH];
nrfx_i2s_buffers_t firstBuf;
nrfx_i2s_buffers_t newBuf;

Adafruit_FlashTransport_QSPI flashTransport;
Adafruit_SPIFlash flash(&flashTransport);
FatFileSystem fatfs;

Adafruit_USBD_MSC usb_msc;

FatFile root;
FatFile file;

// Set to true when PC write to flash
bool changed;

void setup()
{
  flash.begin();
  fatfs.begin(&flash);

  // Set disk vendor id, product id and revision with string up to 8, 16, 4 characters respectively
  usb_msc.setID("Adafruit", "External Flash", "1.0");
  // Set callback
  usb_msc.setReadWriteCallback(msc_read_cb, msc_write_cb, msc_flush_cb);

  // Set disk size, block size should be 512 regardless of spi flash page size
  usb_msc.setCapacity(flash.size()/512, 512);

  // MSC is ready for read/write
  usb_msc.setUnitReady(true);
  usb_msc.begin();

  // Init file system on the flash
  fatfs.begin(&flash);

  Serial.begin(115200);

  Serial.println("Adafruit TinyUSB Mass Storage External Flash example");
  Serial.print("JEDEC ID: "); Serial.println(flash.getJEDECID(), HEX);
  Serial.print("Flash size: "); Serial.println(flash.size());

  changed = true; // to print contents initially

  // Configure the I2S module.
  nrfx_i2s_config_t config = NRFX_I2S_DEFAULT_CONFIG(PIN_SCK, PIN_LRCK, NRFX_I2S_PIN_NOT_USED,
                                                     PIN_SDOUT, NRFX_I2S_PIN_NOT_USED);
  config.ratio = NRF_I2S_RATIO_64X;
  config.mck_setup = NRF_I2S_MCK_32MDIV31;
  if (nrfx_i2s_init(&config, &data_handler) != NRF_SUCCESS)
  {
      // Initialization failed. Take recovery action.
      Serial.print("ERROR: I2S Config Failed.");
  }
}

void loop()
{
  static size_t n = 0;
  if ( changed )
  {
    changed = false;
    if ( !root.open("/") )
    {
      Serial.println("open root failed");
      return;
    }
    Serial.println("Flash contents:");
    // Open next file in root.
    // Warning, openNext starts at the current directory position
    // so a rewind of the directory may be required.
    while ( file.openNext(&root, O_RDONLY) )
    {
      file.printFileSize(&Serial);
      Serial.write(' ');
      file.printName(&Serial);
      if ( file.isDir() )
      {
        // Indicate a directory.
        Serial.write('/');
      }
      Serial.println();
      file.close();
    }
    root.close();
    Serial.println();
    delay(1000);
  }

  if (n++ == 5)
    playFile();

  delay(1000);

}

void playFile(void) {
  static int decoderError;
  int bytesPulled;
  decoder = opus_decoder_create(16000, 1, &decoderError);
  
  dataFile = fatfs.open("sample.ogg", FILE_READ);

  // Read the header data from the file.
  if ( dataFile.available() ) {
    if ( OggPrepareFile(&dataFile) ) {
      bytesPulled = OggGetNextPacket(&dataFile, oggBuf, OGG_BUF_LEN);
      if (bytesPulled > 0)
        decoderError = opus_decode(decoder, oggBuf, bytesPulled, bufA, BUFFER_LENGTH, 1);
    }
  }

  // Send off the first transaction.
  firstBuf.p_rx_buffer = NULL;
  firstBuf.p_tx_buffer = (uint32_t *)bufA;
  if ( nrfx_i2s_start(&firstBuf, BUFFER_LENGTH/2, 0) != NRFX_SUCCESS)
    Serial.print("ERROR: I2S Failed to Start.");

  // Go ahead and prep bufB.
  if ( dataFile.available() ) {
    bytesPulled = OggGetNextPacket(&dataFile, oggBuf, OGG_BUF_LEN);
    //if (bytesPulled > 0)
      //decoderError = opus_decode(decoder, oggBuf, bytesPulled, bufB, BUFFER_LENGTH, 1);
  }
}

// Callback invoked when received READ10 command.
// Copy disk's data to buffer (up to bufsize) and 
// return number of copied bytes (must be multiple of block size) 
int32_t msc_read_cb (uint32_t lba, void* buffer, uint32_t bufsize)
{
  // Note: SPIFLash Bock API: readBlocks/writeBlocks/syncBlocks
  // already include 4K sector caching internally. We don't need to cache it, yahhhh!!
  return flash.readBlocks(lba, (uint8_t*) buffer, bufsize/512) ? bufsize : -1;
}

// Callback invoked when received WRITE10 command.
// Process data in buffer to disk's storage and 
// return number of written bytes (must be multiple of block size)
int32_t msc_write_cb (uint32_t lba, uint8_t* buffer, uint32_t bufsize)
{
  digitalWrite(LED_BUILTIN, HIGH);

  // Note: SPIFLash Bock API: readBlocks/writeBlocks/syncBlocks
  // already include 4K sector caching internally. We don't need to cache it, yahhhh!!
  return flash.writeBlocks(lba, buffer, bufsize/512) ? bufsize : -1;
}

// Callback invoked when WRITE10 command is completed (status received and accepted by host).
// used to flush any pending cache.
void msc_flush_cb (void)
{
  // sync with flash
  flash.syncBlocks();
  // clear file system's cache to force refresh
  fatfs.cacheClear();
  changed = true;
  digitalWrite(LED_BUILTIN, LOW);
}

// Callback invoked when we need more data in the I2S module.
static void data_handler(nrfx_i2s_buffers_t const * p_released, uint32_t status)
{
  static int decoderError;
  int bytesPulled;
  newBuf.p_rx_buffer = NULL;

  if (status == NRFX_I2S_STATUS_NEXT_BUFFERS_NEEDED) {
    if (p_released->p_tx_buffer)
      newBuf.p_tx_buffer = p_released->p_tx_buffer;
    else
      newBuf.p_tx_buffer = (uint32_t *)bufB; // On the first run, bufA will be consumed and nothing will be freed, so queue B.
  }

  // Load up the recently freed buffer with new PCM data.
  if ( dataFile.available() ) {
      bytesPulled = OggGetNextPacket(&dataFile, oggBuf, OGG_BUF_LEN);
      if (bytesPulled > 0)
        decoderError = opus_decode(decoder, oggBuf, bytesPulled, (int16_t *)newBuf.p_tx_buffer, BUFFER_LENGTH, 1);
      else
        nrfx_i2s_stop(); // Probably done.
  } else {
    nrfx_i2s_stop(); // Probably done.
  }

  nrfx_i2s_next_buffers_set(&newBuf);
}
