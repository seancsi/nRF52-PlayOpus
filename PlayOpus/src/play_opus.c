/*  PlayOpus
    play_opus.c - Functions to handle the playing of Opus files.
*/

#include "nrfx.h"
#include "nrfx_config.h"
#include "nrf_gpio.h"
#include "nrfx_i2s.h"
#include "nrf_log.h"
#include "ff.h"
#include "app_fifo.h"

#include "ogg_stripper.h"
#include "play_opus.h"
#include "opus-1.2.1/opus.h"

FIL dataFile;
//FIL outFile;
uint32_t outFileBytesWritten = 0;
OpusDecoder *decoder;
static int decoderError;

uint8_t oggBuf[OGG_BUF_LEN];

int16_t decBuf[DEC_BUF_LEN];
size_t decBufSamplesReady;

int16_t bufA[DEC_BUF_LEN];
int16_t bufB[DEC_BUF_LEN];
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

    if ( nrfx_i2s_init(&config, &OPUS_DataHandler) != NRF_SUCCESS ) {
        NRF_LOG_INFO("ERROR: I2S Config Failed.");
    }

    decoder = opus_decoder_create(16000, 1, &decoderError);
    opus_decoder_ctl(decoder, OPUS_SET_LSB_DEPTH(16));
}

void OPUS_PlayFile(void) {
    int bytesPulled;
    size_t firstPagePointer;
    FRESULT res;

//    res = f_open(&outFile, "out.raw", FA_CREATE_ALWAYS | FA_WRITE);
    // Read the header data from the file.
    res = f_open(&dataFile, "sample.ogg", FA_READ);
    if ( res == FR_OK ) {
        if ( OggPrepareFile(&dataFile) ) {
            bytesPulled = OPUS_FetchAndDecodePage(&dataFile, decBuf, DEC_BUF_LEN);
            if ( bytesPulled > 0 ) {
                isPlaying = true;
                decBufSamplesReady = 0;
                OPUS_ProcessAudio(); // Make sure we have the next one ready to go.

                // First, we need to massage the first page since it's not the same size as the rest.
                // The Opus decoder also starts with some bytes that need to be discarded.
                memset(bufA, 0, DEC_BUF_LEN * sizeof(int16_t) );
                firstPagePointer = OggGetLastIDHeader()->PreSkip;

                // If the first packet is short.  Offset that.
                if (decBufSamplesReady > bytesPulled)
                    firstPagePointer += (decBufSamplesReady - bytesPulled);

                // Copy the bytes over.
                memcpy_fast(bufA + firstPagePointer, decBuf + OggGetLastIDHeader()->PreSkip,
                            DEC_BUF_LEN - firstPagePointer);

                // Send off the first transaction.
                firstBuf.p_rx_buffer = NULL;
                firstBuf.p_tx_buffer = (uint32_t *)bufA;

                printf("Starting %d %d\r\n", bytesPulled, decBufSamplesReady);
                if ( nrfx_i2s_start(&firstBuf, decBufSamplesReady / 2, 0) != NRFX_SUCCESS)
                    NRF_LOG_INFO("ERROR: I2S Failed to Start.");
            }
        }
    }
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
    int samplesPulled;

    if ( (isPlaying) && (!decBufSamplesReady) ) {
        samplesPulled = OPUS_FetchAndDecodePage(&dataFile, decBuf, DEC_BUF_LEN);
        if ( samplesPulled > 0 ) {
            decBufSamplesReady = samplesPulled;
            printf("Plop %d\r\n", decBufSamplesReady);
        } else {
            OPUS_Stop();
        }
    }
}

// Pull the next page into a local buffer and decode it into another buffer.
// Returns the number of bytes put into the decode buffer.
int OPUS_FetchAndDecodePage(FIL * oggFile, uint16_t * decodeBuf, size_t maxLen) {
    int bytesPulled;
    unsigned int samplesWritten = 0;
    size_t i;
    size_t oggBufPtr = 0;
    size_t packetLen;
    int decoderError;

    bytesPulled = OggGetNextDataPage(&dataFile, oggBuf, OGG_BUF_LEN);
    if (bytesPulled > 0) {
        for (i = 0; i < OggGetLastPageHeader()->Segments; i++) {
            packetLen = OggGetLastPageHeader()->SegmentTable[i];
            decoderError = opus_decode(decoder, oggBuf + oggBufPtr, packetLen, decodeBuf+samplesWritten, DEC_BUF_LEN, 0);
            oggBufPtr += packetLen;
            if (decoderError > 0)
                samplesWritten += decoderError;
        }
        //if (decoderError > 0)
        //    f_write(&outFile, bufA, decoderError * 2, &samplesWritten);
        //f_sync(&outFile);
        return samplesWritten;
    } else {
        return bytesPulled; // This will contain an error code from OggGetNextDataPage.  Hopefully an EOF.
    }
}

// Callback invoked when we need more data in the I2S module.
static void OPUS_DataHandler(nrfx_i2s_buffers_t const * p_released, uint32_t status) {
    newBuf.p_rx_buffer = NULL;
    static int i = 0;

    if (status == NRFX_I2S_STATUS_NEXT_BUFFERS_NEEDED) {
        if (p_released->p_tx_buffer)
            newBuf.p_tx_buffer = p_released->p_tx_buffer;
        else
            newBuf.p_tx_buffer = (uint32_t *)bufB; // On the first run, bufA will be consumed and nothing will be freed, so queue B.

        if ( decBufSamplesReady > END_DISCARD_THRESHOLD ) {
            memcpy_fast(newBuf.p_tx_buffer, decBuf, decBufSamplesReady);
            decBufSamplesReady = 0;
            nrfx_i2s_next_buffers_set(&newBuf);
        } else if (decBufSamplesReady > 0) {
            // This is a short end page.  Discard it and stop.
            ; // TODO: Figure out a way to stop after the current packet.
        } else {
            printf("Possible buffer underflow, or EOF.\r\n");
            OPUS_Stop();
        }
    }
}