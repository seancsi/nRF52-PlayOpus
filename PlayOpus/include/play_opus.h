/*  PlayOpus
    play_opus.h - Functions to handle the playing of Opus files.
*/

#include <nrfx_i2s.h>

#define PIN_LRCK    26//NRF_GPIO_PIN_MAP(0, 27) // D10
#define PIN_SCK     6//NRF_GPIO_PIN_MAP(0, 6) // D11
#define PIN_MCK     8//NRF_GPIO_PIN_MAP(0, 7 ) // D12
#define PIN_SDOUT   27//NRF_GPIO_PIN_MAP(0, 26) // D9

#define BUFFER_LENGTH 1000
#define OGG_BUF_LEN 0xFF

void OPUS_Init(void);
void OPUS_PlayFile(void);
void OPUS_Stop(void);
static void OPUS_DataHandler(nrfx_i2s_buffers_t const * p_released, uint32_t status);