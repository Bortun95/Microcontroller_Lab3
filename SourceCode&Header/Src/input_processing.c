/*
 * input_processing.c
 *
 *  Created on: Oct 28, 2026
 *      Author: Admin
 */
#include "main.h"
#include "input_reading.h"
#include "input_processing.h"

static uint8_t mode = 1;
static uint8_t redDuration = 5;
static uint8_t yellowDuration = 2;
static uint8_t greenDuration = 3;
static uint8_t editDuration = 0;

void fsm_for_input_processing(void)
{
    for (uint8_t i = 0; i < 3; i++) {
        if (is_button_pressed(i)) {

            if (i == 0) {
                mode++;
                if (mode > 4) mode = 1;

                if (mode == 2)      editDuration = redDuration;
                else if (mode == 3) editDuration = yellowDuration;
                else if (mode == 4) editDuration = greenDuration;
            }

            else if (i == 1 && mode != 1) {
                if (editDuration < 99) editDuration++;
                else editDuration = 1;
            }

            else if (i == 2 && mode != 1) {
                if (mode == 2) {
                    redDuration = editDuration;
                    if (redDuration > yellowDuration) {
                        greenDuration = redDuration - yellowDuration;
                    } else {
                        yellowDuration = 1;
                        greenDuration = (redDuration > 1) ? (redDuration - 1) : 1;
                        redDuration = greenDuration + yellowDuration;
                        editDuration = redDuration;
                    }
                }
                else if (mode == 3) {
                    yellowDuration = editDuration;
                    redDuration = greenDuration + yellowDuration;
                }
                else if (mode == 4) {
                    greenDuration = editDuration;
                    redDuration = greenDuration + yellowDuration;
                }
            }
        }
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
