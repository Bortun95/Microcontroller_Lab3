/*
 * display_7seg.c
 *
 *  Created on: Oct 28, 2026
 *      Author: Admin
 */
#include "main.h"
#include "input_processing.h"
#include "traffic_light.h"
#include "display_7seg.h"
#include "timer.h"

#define DISPLAY_SCAN_INTERVAL_MS 100U

static GPIO_TypeDef *segmentPorts[7] = {
    SEG0_GPIO_Port, SEG1_GPIO_Port, SEG2_GPIO_Port,
    SEG3_GPIO_Port, SEG4_GPIO_Port, SEG5_GPIO_Port, SEG6_GPIO_Port
};
static const uint16_t segmentPins[7] = {
    SEG0_Pin, SEG1_Pin, SEG2_Pin, SEG3_Pin, SEG4_Pin, SEG5_Pin, SEG6_Pin
};
static GPIO_TypeDef *digitPorts[4] = {
    EN0_GPIO_Port, EN1_GPIO_Port, EN2_GPIO_Port, EN3_GPIO_Port
};
static const uint16_t digitPins[4] = {
    EN0_Pin, EN1_Pin, EN2_Pin, EN3_Pin
};

static const uint8_t digitPatterns[10] = {
    0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F
};

static uint8_t displayDigits[4] = {0, 0, 0, 0};
static uint8_t currentDigit = 0;

static void disable_all_digits(void)
{
    for (uint8_t i = 0; i < 4; i++) {
        HAL_GPIO_WritePin(digitPorts[i], digitPins[i], GPIO_PIN_SET);
    }
}

static void set_segments(uint8_t number)
{
    uint8_t pattern = digitPatterns[number % 10U];
    for (uint8_t i = 0; i < 7; i++) {
        GPIO_PinState pinState = (pattern & (1U << i)) ? GPIO_PIN_RESET : GPIO_PIN_SET;
        HAL_GPIO_WritePin(segmentPorts[i], segmentPins[i], pinState);
    }
}

static void update_display_values(void)
{
    uint8_t mode = get_mode();
    uint8_t value;

    if (mode == 1) {
        value = traffic_light_get_horizontal_remaining();
        displayDigits[0] = value / 10U;
        displayDigits[1] = value % 10U;

        value = traffic_light_get_vertical_remaining();
        displayDigits[2] = value / 10U;
        displayDigits[3] = value % 10U;
    } else {
        value = get_edit_duration();
        displayDigits[0] = value / 10U;
        displayDigits[1] = value % 10U;

        displayDigits[2] = 0;
        displayDigits[3] = mode;
    }
}

void display_7seg_init(void)
{
    disable_all_digits();
    currentDigit = 0;
    set_timer(TIMER_DISPLAY_ID, DISPLAY_SCAN_INTERVAL_MS);
}

void display_7seg_update(void)
{
    if (!is_timer_expired(TIMER_DISPLAY_ID)) return;

    set_timer(TIMER_DISPLAY_ID, DISPLAY_SCAN_INTERVAL_MS);

    if (currentDigit == 0) {
        update_display_values();
    }

    disable_all_digits();
    set_segments(displayDigits[currentDigit]);
    HAL_GPIO_WritePin(digitPorts[currentDigit], digitPins[currentDigit], GPIO_PIN_RESET);

    currentDigit++;
    if (currentDigit >= 4) currentDigit = 0;
}
