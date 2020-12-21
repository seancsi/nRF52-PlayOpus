/*  PlayOpus
    play_opus.h - Functions to handle the playing of Opus files.
*/

#include <nrfx_i2s.h>

#define PIN_LRCK    NRF_GPIO_PIN_MAP(0, 27) // D10
#define PIN_SCK     NRF_GPIO_PIN_MAP(0, 6) // D11
#define PIN_MCK     NRF_GPIO_PIN_MAP(0, 8 ) // D12
#define PIN_SDOUT   NRF_GPIO_PIN_MAP(0, 26) // D9

#define BUFFER_LENGTH 4096
#define OGG_BUF_LEN 0xA0*0x1A // From hex editor, our encoder used a max of 0x1A pages 0xA0 in length.

void OPUS_Init(void);
void OPUS_PlayFile(void);
void OPUS_Stop(void);
void OPUS_ProcessAudio(void);
static void OPUS_DataHandler(nrfx_i2s_buffers_t const * p_released, uint32_t status);