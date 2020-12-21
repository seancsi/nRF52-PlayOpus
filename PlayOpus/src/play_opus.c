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
//FIL outFile;
uint32_t outFileBytesWritten = 0;
OpusDecoder *decoder;
static int decoderError;

uint8_t oggBuf[OGG_BUF_LEN];

int16_t bufA[BUFFER_LENGTH];
int16_t bufB[BUFFER_LENGTH];
nrfx_i2s_buffers_t firstBuf;
nrfx_i2s_buffers_t newBuf;

bool isPlaying;

void OPUS_Init(void) {
    isPlaying = false;

    // Configure the I2S module.
    nrfx_i2s_config_t config;

    config.sck_pin = PIN_SCK;
    config.lrck_pin = PIN_LRCK;
    config.mck_pin = PIN_MCK;
    config.sdout_pin = PIN_SDOUT;
    config.sdin_pin = NRFX_I2S_PIN_NOT_USED;
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

    decoder = opus_decoder_create(24000, 1, &decoderError);
    opus_decoder_ctl(decoder, OPUS_SET_LSB_DEPTH(16));
}

void OPUS_PlayFile(void) {
    static int decoderError;
    int bytesPulled;
    unsigned int bytesWritten;
    FRESULT res;

//    res = f_open(&outFile, "out.raw", FA_CREATE_ALWAYS | FA_WRITE);
    // Read the header data from the file.
    res = f_open(&dataFile, "sample.ogg", FA_READ);
    if ( res == FR_OK ) {
        if ( OggPrepareFile(&dataFile) ) {
            bytesPulled = OggGetNextPacket(&dataFile, oggBuf, OGG_BUF_LEN);
            if (bytesPulled > 0) {
                decoderError = opus_decode(decoder, oggBuf, bytesPulled, bufA, BUFFER_LENGTH, 0);
                //if (decoderError > 0)
                //    f_write(&outFile, bufA, decoderError * 2, &bytesWritten);
                outFileBytesWritten += bytesWritten;
                //f_sync(&outFile);
                isPlaying = true;
            }
        }
    }

    // Send off the first transaction.
    firstBuf.p_rx_buffer = NULL;
    firstBuf.p_tx_buffer = (uint32_t *)bufA;
    if ( nrfx_i2s_start(&firstBuf, BUFFER_LENGTH / 2, 0) != NRFX_SUCCESS)
        NRF_LOG_INFO("ERROR: I2S Failed to Start.");
}

void OPUS_Stop(void) {
    isPlaying = false;
    nrfx_i2s_stop(); // Probably done.
    f_close(&dataFile);
    //f_sync(&outFile);
    //f_close(&outFile);
    printf("DONE!\r\n");
}

void OPUS_ProcessAudio(void) {
    int bytesPulled;
    unsigned int bytesWritten;

    if (isPlaying) {
        bytesPulled = OggGetNextPacket(&dataFile, oggBuf, OGG_BUF_LEN);
        if (bytesPulled > 0) {
            decoderError = opus_decode(decoder, oggBuf, bytesPulled, bufA, BUFFER_LENGTH, 0);
            if (decoderError > 0) {
                //f_write(&outFile, bufA, decoderError * 2, &bytesWritten);
                outFileBytesWritten += bytesWritten;
                //f_sync(&outFile);
            } else {
                OPUS_Stop();
            }
        } else {
            OPUS_Stop();
        }
    }
}

// Callback invoked when we need more data in the I2S module.
static void OPUS_DataHandler(nrfx_i2s_buffers_t const * p_released, uint32_t status) {
    int bytesPulled;
    newBuf.p_rx_buffer = NULL;
    static int i = 0;

    if (status == NRFX_I2S_STATUS_NEXT_BUFFERS_NEEDED) {
        if (p_released->p_tx_buffer)
            newBuf.p_tx_buffer = p_released->p_tx_buffer;
        else
            newBuf.p_tx_buffer = (uint32_t *)bufB; // On the first run, bufA will be consumed and nothing will be freed, so queue B.

        // Load up the recently freed buffer with new PCM data.
        if ( &dataFile ) {
            //bytesPulled = OggGetNextDataPage(&dataFile, oggBuf, OGG_BUF_LEN);
            //if (bytesPulled > 0)
                memset(newBuf.p_tx_buffer, i++, 40);
                //decoderError = opus_decode(decoder, oggBuf, bytesPulled, (int16_t *)newBuf.p_tx_buffer, BUFFER_LENGTH, 0);
            //else
            //    OPUS_Stop();
        } else {
            OPUS_Stop(); // Probably done.
        }

        nrfx_i2s_next_buffers_set(&newBuf);
    }
}