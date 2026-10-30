/*
 * traffic_light.c
 *
 *  Created on: Oct 28, 2026
 *      Author: Admin
 */
#include "main.h"
#include "input_processing.h"
#include "traffic_light.h"
#include "timer.h"

typedef enum {
    HORIZONTAL_GREEN,
    HORIZONTAL_YELLOW,
    VERTICAL_GREEN,
    VERTICAL_YELLOW
} TrafficState;

static TrafficState state = HORIZONTAL_GREEN;
static uint8_t horizontalRemaining = 0;
static uint8_t verticalRemaining = 0;

static void set_traffic_leds(
    uint8_t redH, uint8_t yellowH, uint8_t greenH,
    uint8_t redV, uint8_t yellowV, uint8_t greenV)
{
    HAL_GPIO_WritePin(LED_RED_HOR_GPIO_Port, LED_RED_HOR_Pin,
                      redH ? GPIO_PIN_RESET : GPIO_PIN_SET);
    HAL_GPIO_WritePin(LED_YELLOW_HOR_GPIO_Port, LED_YELLOW_HOR_Pin,
                      yellowH ? GPIO_PIN_RESET : GPIO_PIN_SET);
    HAL_GPIO_WritePin(LED_GREEN_HOR_GPIO_Port, LED_GREEN_HOR_Pin,
                      greenH ? GPIO_PIN_RESET : GPIO_PIN_SET);

    HAL_GPIO_WritePin(LED_RED_VER_GPIO_Port, LED_RED_VER_Pin,
                      redV ? GPIO_PIN_RESET : GPIO_PIN_SET);
    HAL_GPIO_WritePin(LED_YELLOW_VER_GPIO_Port, LED_YELLOW_VER_Pin,
                      yellowV ? GPIO_PIN_RESET : GPIO_PIN_SET);
    HAL_GPIO_WritePin(LED_GREEN_VER_GPIO_Port, LED_GREEN_VER_Pin,
                      greenV ? GPIO_PIN_RESET : GPIO_PIN_SET);
}

void traffic_light_init(void)
{
    state = HORIZONTAL_GREEN;

    horizontalRemaining = get_green_duration();
    verticalRemaining = get_red_duration();

    set_traffic_leds(0, 0, 1, 1, 0, 0);

    set_timer(TIMER_TRAFFIC_1S_ID, 1000);
    set_timer(TIMER_BLINK_ID, 250);
}

void traffic_light_update(void)
{
    uint8_t mode = get_mode();
    static uint8_t last_mode = 0;
    static uint8_t blink_state = 0;

    if (last_mode >= 2 && last_mode <= 4 && mode == 1) {
        traffic_light_init();
    }

    if (mode >= 2 && mode <= 4) {
        if (is_timer_expired(TIMER_BLINK_ID) || mode != last_mode) {
            set_timer(TIMER_BLINK_ID, 250);

            if (mode != last_mode) {
                blink_state = 1;
            } else {
                blink_state = !blink_state;
            }

            set_traffic_leds(
                mode == 2 ? blink_state : 0,
                mode == 3 ? blink_state : 0,
                mode == 4 ? blink_state : 0,
                mode == 2 ? blink_state : 0,
                mode == 3 ? blink_state : 0,
                mode == 4 ? blink_state : 0
            );
        }
        last_mode = mode;
        return;
    }

    last_mode = mode;

    if (is_timer_expired(TIMER_TRAFFIC_1S_ID)) {
        set_timer(TIMER_TRAFFIC_1S_ID, 1000);

        if (horizontalRemaining > 0) horizontalRemaining--;
        if (verticalRemaining > 0)   verticalRemaining--;

        if ((state == HORIZONTAL_GREEN  && horizontalRemaining == 0) ||
            (state == HORIZONTAL_YELLOW && horizontalRemaining == 0) ||
            (state == VERTICAL_GREEN    && verticalRemaining == 0)   ||
            (state == VERTICAL_YELLOW   && verticalRemaining == 0))
        {
            switch (state) {
            case HORIZONTAL_GREEN:
                state = HORIZONTAL_YELLOW;
                horizontalRemaining = get_yellow_duration();
                break;

            case HORIZONTAL_YELLOW:
                state = VERTICAL_GREEN;
                horizontalRemaining = get_red_duration();
                verticalRemaining = get_green_duration();
                break;

            case VERTICAL_GREEN:
                state = VERTICAL_YELLOW;
                verticalRemaining = get_yellow_duration();
                break;

            case VERTICAL_YELLOW:
                state = HORIZONTAL_GREEN;
                horizontalRemaining = get_green_duration();
                verticalRemaining = get_red_duration();
                break;
            }
        }

        switch (state) {
        case HORIZONTAL_GREEN:
            set_traffic_leds(0, 0, 1, 1, 0, 0);
            break;

        case HORIZONTAL_YELLOW:
            set_traffic_leds(0, 1, 0, 1, 0, 0);
            break;

        case VERTICAL_GREEN:
            set_traffic_leds(1, 0, 0, 0, 0, 1);
            break;

        case VERTICAL_YELLOW:
            set_traffic_leds(1, 0, 0, 0, 1, 0);
            break;
        }
    }
}

uint8_t traffic_light_get_horizontal_remaining(void)
{
    return horizontalRemaining;
}

uint8_t traffic_light_get_vertical_remaining(void)
{
    return verticalRemaining;
}
