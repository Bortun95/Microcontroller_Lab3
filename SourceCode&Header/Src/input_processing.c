/*
 * input_processing.c
 *
 *  Created on: Oct 28, 2026
 *      Author: Admin
 */
#include "main.h"
#include "input_reading.h"
#include "input_processing.h"

#define BTN_MODE    0
#define BTN_INC     1
#define BTN_SET     2

#define MODE_NORMAL 1
#define MODE_RED    2
#define MODE_YELLOW 3
#define MODE_GREEN  4

static uint8_t mode = MODE_NORMAL;
static uint8_t redDuration = 5;
static uint8_t yellowDuration = 2;
static uint8_t greenDuration = 3;

static uint8_t tempRed = 5;
static uint8_t tempYellow = 2;
static uint8_t tempGreen = 3;

static uint8_t editDuration = 0;

static void handle_button_mode(void)
{
    uint8_t prev_mode = mode;
    mode++;
    if (mode > MODE_GREEN) {
        mode = MODE_NORMAL;
    }

    if (prev_mode == MODE_NORMAL && mode == MODE_RED) {
        tempRed = redDuration;
        tempYellow = yellowDuration;
        tempGreen = greenDuration;
    }

    if (mode == MODE_NORMAL) {
        if (tempRed == (tempGreen + tempYellow)) {
            redDuration = tempRed;
            yellowDuration = tempYellow;
            greenDuration = tempGreen;
        } else {
            if (tempRed > tempYellow) {
                redDuration = tempRed;
                yellowDuration = tempYellow;
                greenDuration = tempRed - tempYellow;
            } else {
                yellowDuration = tempYellow;
                greenDuration = tempGreen;
                redDuration = tempGreen + tempYellow;
            }
        }
        editDuration = 0;
        return;
    }

    switch (mode) {
    case MODE_RED:
        editDuration = tempRed;
        break;
    case MODE_YELLOW:
        editDuration = tempYellow;
        break;
    case MODE_GREEN:
        editDuration = tempGreen;
        break;
    default:
        editDuration = 0;
        break;
    }
}

static void handle_button_inc(void)
{
    if (mode == MODE_NORMAL) return;

    if (editDuration < 99) {
        editDuration++;
    } else {
        editDuration = 1;
    }
}

static void handle_button_set(void)
{
    if (mode == MODE_NORMAL) return;

    switch (mode) {
    case MODE_RED:
        tempRed = editDuration;
        break;

    case MODE_YELLOW:
        tempYellow = editDuration;
        break;

    case MODE_GREEN:
        tempGreen = editDuration;
        break;

    default:
        break;
    }
}

void fsm_for_input_processing(void)
{
    if (is_button_pressed(BTN_MODE)) {
        handle_button_mode();
    }

    if (is_button_pressed(BTN_INC)) {
        handle_button_inc();
    }

    if (is_button_pressed(BTN_SET)) {
        handle_button_set();
    }
}

uint8_t get_mode(void) {
    return mode;
}
uint8_t get_red_duration(void) {
    return redDuration;
}
uint8_t get_yellow_duration(void) {
    return yellowDuration;
}
uint8_t get_green_duration(void) {
    return greenDuration;
}
uint8_t get_edit_duration(void) {
    return editDuration;
}
