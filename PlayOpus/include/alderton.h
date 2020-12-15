/**
 * Header for Alderton
 */
#ifndef ALDERTON_H
#define ALDERTON_H

#ifdef __cplusplus
extern "C" {
#endif

#include "nrf_gpio.h"

#define LEDS_NUMBER    2

#define LED_1          NRF_GPIO_PIN_MAP(1, 9)
#define LED_2          NRF_GPIO_PIN_MAP(1, 10)
#define LED_START      LED_1
#define LED_STOP       LED_2

#define LEDS_ACTIVE_STATE 0

#define LEDS_LIST { LED_1, LED_2 }

#define LEDS_INV_MASK  LEDS_MASK

#define BSP_LED_0      LED_1
#define BSP_LED_1      LED_2

#define BUTTONS_NUMBER 1

#define BUTTON_1       NRF_GPIO_PIN_MAP(1, 2)

#define BUTTON_PULL    NRF_GPIO_PIN_PULLUP

#define BUTTONS_ACTIVE_STATE 0

#define BUTTONS_LIST { BUTTON_1 }

#define BSP_BUTTON_0   BUTTON_1

#define RX_PIN_NUMBER  NRF_GPIO_PIN_MAP(0, 24)
#define TX_PIN_NUMBER  NRF_GPIO_PIN_MAP(0, 25)
#define HWFC           false

#define BSP_QSPI_SCK_PIN   NRF_GPIO_PIN_MAP(0, 19)
#define BSP_QSPI_CSN_PIN   NRF_GPIO_PIN_MAP(0, 20)
#define BSP_QSPI_IO0_PIN   NRF_GPIO_PIN_MAP(0, 17)
#define BSP_QSPI_IO1_PIN   NRF_GPIO_PIN_MAP(0, 22)
#define BSP_QSPI_IO2_PIN   NRF_GPIO_PIN_MAP(0, 23)
#define BSP_QSPI_IO3_PIN   NRF_GPIO_PIN_MAP(0, 21)

// Arduino board mappings
#define ARDUINO_SCL_PIN             27    // SCL signal pin
#define ARDUINO_SDA_PIN             26    // SDA signal pin
#define ARDUINO_AREF_PIN            2     // Aref pin

#define ARDUINO_13_PIN              NRF_GPIO_PIN_MAP(1, 9)   // Digital pin 13
#define ARDUINO_12_PIN              NRF_GPIO_PIN_MAP(0, 8)   // Digital pin 12
#define ARDUINO_11_PIN              NRF_GPIO_PIN_MAP(0, 6)   // Digital pin 11
#define ARDUINO_10_PIN              NRF_GPIO_PIN_MAP(0, 27)  // Digital pin 10
#define ARDUINO_9_PIN               NRF_GPIO_PIN_MAP(0, 26)  // Digital pin 9
#define ARDUINO_6_PIN               NRF_GPIO_PIN_MAP(0, 7)   // Digital pin 6
#define ARDUINO_5_PIN               NRF_GPIO_PIN_MAP(1, 8)   // Digital pin 5
#define ARDUINO_2_PIN               NRF_GPIO_PIN_MAP(0, 10)  // Digital pin 2

#define ARDUINO_A0_PIN              NRF_GPIO_PIN_MAP(0, 4)   // Analog channel 0
#define ARDUINO_A1_PIN              NRF_GPIO_PIN_MAP(0, 5)   // Analog channel 1
#define ARDUINO_A2_PIN              NRF_GPIO_PIN_MAP(0, 30)   // Analog channel 2
#define ARDUINO_A3_PIN              NRF_GPIO_PIN_MAP(0, 28)   // Analog channel 3
#define ARDUINO_A4_PIN              NRF_GPIO_PIN_MAP(0, 2)   // Analog channel 4
#define ARDUINO_A5_PIN              NRF_GPIO_PIN_MAP(0, 3)   // Analog channel 5


#ifdef __cplusplus
}
#endif

#endif
