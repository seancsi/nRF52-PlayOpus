/*  PlayOpus
    play_opus.c - Functions to handle the playing of Opus files.
*/

#include "nrfx.h"
#include "nrfx_config.h"
#include "nrf_gpio.h"
#include "nrfx_i2s.h"
#include "nrf_log.h"
#include "ff.h"

#include "ogg_stripper.h"
#include "play_opus.h"
#include "opus-1.2.1/opus.h"


FIL dataFile;
OpusDecoder *decoder;
static int decoderError;

uint8_t oggBuf[OGG_BUF_LEN];

int16_t bufA[BUFFER_LENGTH];
int16_t bufB[BUFFER_LENGTH];
nrfx_i2s_buffers_t firstBuf;
nrfx_i2s_buffers_t newBuf;

void OPUS_Init(void) {
/*    // Configure the I2S module.
    nrfx_i2s_config_t config;

    config.sck_pin = PIN_SCK;
    config.lrck_pin = PIN_LRCK;
    config.mck_pin = PIN_MCK;
    config.sdout_pin = PIN_SDOUT;
    config.sdin_pin = NRF_I2S_PIN_NOT_CONNECTED;
    config.irq_priority = 2;
    config.mode = NRF_I2S_MODE_MASTER;
    config.format = NRF_I2S_FORMAT_I2S;
    config.alignment = NRF_I2S_ALIGN_LEFT;
    config.sample_width = NRF_I2S_SWIDTH_16BIT;
    config.channels = NRF_I2S_CHANNELS_LEFT;
    config.mck_setup = NRF_I2S_MCK_32MDIV31;
    config.ratio = NRF_I2S_RATIO_64X;

    if (nrfx_i2s_init(&config, &OPUS_DataHandler) != NRF_SUCCESS) {
        NRF_LOG_INFO("ERROR: I2S Config Failed.");
    }

    decoder = opus_decoder_create(16000, 1, &decoderError);
    //opus_decoder_ctl(decoder, OPUS_SET_LSB_DEPTH(16));
    */

    static int16_t sine_table[] = { 0, 0, 23170, 23170, 32767, 32767, 23170, 23170, 0, 0, -23170, -23170, -32768, -32768, -23170, -23170};

    // Enable transmission
    NRF_I2S->CONFIG.TXEN = (I2S_CONFIG_TXEN_TXEN_ENABLE << I2S_CONFIG_TXEN_TXEN_Pos);

    // Enable MCK generator
    NRF_I2S->CONFIG.MCKEN = (I2S_CONFIG_MCKEN_MCKEN_ENABLE << I2S_CONFIG_MCKEN_MCKEN_Pos);

    // MCKFREQ = 4 MHz
    NRF_I2S->CONFIG.MCKFREQ = I2S_CONFIG_MCKFREQ_MCKFREQ_32MDIV11  << I2S_CONFIG_MCKFREQ_MCKFREQ_Pos;

    // Ratio = 64 
    NRF_I2S->CONFIG.RATIO = I2S_CONFIG_RATIO_RATIO_64X << I2S_CONFIG_RATIO_RATIO_Pos;

    // Master mode, 16Bit, left aligned
    NRF_I2S->CONFIG.MODE = I2S_CONFIG_MODE_MODE_MASTER << I2S_CONFIG_MODE_MODE_Pos;
    NRF_I2S->CONFIG.SWIDTH = I2S_CONFIG_SWIDTH_SWIDTH_16BIT << I2S_CONFIG_SWIDTH_SWIDTH_Pos;
    NRF_I2S->CONFIG.ALIGN = I2S_CONFIG_ALIGN_ALIGN_LEFT << I2S_CONFIG_ALIGN_ALIGN_Pos;

    // Format = I2S
    NRF_I2S->CONFIG.FORMAT = I2S_CONFIG_FORMAT_FORMAT_I2S << I2S_CONFIG_FORMAT_FORMAT_Pos;

    // Use stereo 
    NRF_I2S->CONFIG.CHANNELS = I2S_CONFIG_CHANNELS_CHANNELS_STEREO << I2S_CONFIG_CHANNELS_CHANNELS_Pos;

    // Configure pins
    NRF_I2S->PSEL.MCK = (PIN_MCK << I2S_PSEL_MCK_PIN_Pos);
    NRF_I2S->PSEL.SCK = (PIN_SCK << I2S_PSEL_SCK_PIN_Pos); 
    NRF_I2S->PSEL.LRCK = (PIN_LRCK << I2S_PSEL_LRCK_PIN_Pos); 
    NRF_I2S->PSEL.SDOUT = (PIN_SDOUT << I2S_PSEL_SDOUT_PIN_Pos);

    NRF_I2S->ENABLE = 1;

    // Configure data pointer
    NRF_I2S->TXD.PTR = (uint32_t)&sine_table[0];
    NRF_I2S->RXTXD.MAXCNT = sizeof(sine_table) / sizeof(uint32_t);

    // Start transmitting I2S data
    NRF_I2S->TASKS_START = 1;
}

void OPUS_PlayFile(void) {
    static int decoderError;
    int bytesPulled;
    FRESULT res;

    // Read the header data from the file.
    res = f_open(&dataFile, "sample.ogg", FA_READ);
    if ( res == FR_OK ) {
        if ( OggPrepareFile(&dataFile) ) {
            bytesPulled = OggGetNextPacket(&dataFile, oggBuf, OGG_BUF_LEN);
            if (bytesPulled > 0)
                decoderError = opus_decode(decoder, oggBuf, bytesPulled, bufA, BUFFER_LENGTH, 0);
        }
    }

    // Send off the first transaction.
    firstBuf.p_rx_buffer = NULL;
    firstBuf.p_tx_buffer = (uint32_t *)bufA;
    if ( nrfx_i2s_start(&firstBuf, 10, 0) != NRFX_SUCCESS)
        NRF_LOG_INFO("ERROR: I2S Failed to Start.");
}

void OPUS_Stop(void) {
    //nrfx_i2s_stop(); // Probably done.
    //f_close(&dataFile);
}

// Callback invoked when we need more data in the I2S module.
static void OPUS_DataHandler(nrfx_i2s_buffers_t const * p_released, uint32_t status) {
  int bytesPulled;
  newBuf.p_rx_buffer = NULL;

  if (status == NRFX_I2S_STATUS_NEXT_BUFFERS_NEEDED) {
    if (p_released->p_tx_buffer)
      newBuf.p_tx_buffer = p_released->p_tx_buffer;
    else
      newBuf.p_tx_buffer = (uint32_t *)bufB; // On the first run, bufA will be consumed and nothing will be freed, so queue B.
  }

  // Load up the recently freed buffer with new PCM data.
  if ( &dataFile ) {
      bytesPulled = OggGetNextPacket(&dataFile, oggBuf, OGG_BUF_LEN);
      if (bytesPulled > 0)
        memset(newBuf.p_tx_buffer, 0x69, bytesPulled);
        //decoderError = opus_decode(decoder, oggBuf, bytesPulled, (int16_t *)newBuf.p_tx_buffer, BUFFER_LENGTH, 0);
      else
        OPUS_Stop();
  } else {
    OPUS_Stop(); // Probably done.
  }

  nrfx_i2s_next_buffers_set(&newBuf);
}