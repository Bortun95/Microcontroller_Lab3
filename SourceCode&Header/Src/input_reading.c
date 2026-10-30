/*
 * input_reading.c
 *
 *  Created on: Oct 28, 2026
 *      Author: Admin
 */
#include "main.h"
#include "input_reading.h"

#define NO_OF_BUTTONS 3
#define BUTTON_IS_PRESSED GPIO_PIN_RESET
#define BUTTON_IS_RELEASED GPIO_PIN_SET

static GPIO_TypeDef *buttonPorts[NO_OF_BUTTONS] = {
    BUTTON1_GPIO_Port, BUTTON2_GPIO_Port, BUTTON3_GPIO_Port
};

static const uint16_t buttonPins[NO_OF_BUTTONS] = {
    BUTTON1_Pin, BUTTON2_Pin, BUTTON3_Pin
};

static GPIO_PinState buttonBuffer[NO_OF_BUTTONS] = {
    BUTTON_IS_RELEASED, BUTTON_IS_RELEASED, BUTTON_IS_RELEASED
};
static GPIO_PinState debounceButtonBuffer1[NO_OF_BUTTONS] = {
    BUTTON_IS_RELEASED, BUTTON_IS_RELEASED, BUTTON_IS_RELEASED
};
static GPIO_PinState debounceButtonBuffer2[NO_OF_BUTTONS] = {
    BUTTON_IS_RELEASED, BUTTON_IS_RELEASED, BUTTON_IS_RELEASED
};

static uint8_t flagForButtonPress[NO_OF_BUTTONS] = {0};

void button_reading(void)
{
    for (uint8_t i = 0; i < NO_OF_BUTTONS; i++) {
        debounceButtonBuffer2[i] = debounceButtonBuffer1[i];
        debounceButtonBuffer1[i] = HAL_GPIO_ReadPin(buttonPorts[i], buttonPins[i]);

        if (debounceButtonBuffer1[i] == debounceButtonBuffer2[i]) {
            if (buttonBuffer[i] != debounceButtonBuffer1[i]) {
                buttonBuffer[i] = debounceButtonBuffer1[i];

                if (buttonBuffer[i] == BUTTON_IS_PRESSED) {
                    flagForButtonPress[i] = 1;
                }
            }
        }
    }
}

unsigned char is_button_pressed(unsigned char index)
{
    if (index >= NO_OF_BUTTONS) return 0;

    if (flagForButtonPress[index] == 1) {
        flagForButtonPress[index] = 0;
        return 1;
    }
    return 0;
}
