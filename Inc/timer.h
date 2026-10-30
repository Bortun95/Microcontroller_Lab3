/*
 * timer.h
 *
 *  Created on: Oct 30, 2026
 *      Author: Admin
 */

#ifndef INC_TIMER_H_
#define INC_TIMER_H_

#include <stdint.h>

#define TIMER_DISPLAY_ID    0
#define TIMER_TRAFFIC_1S_ID 1
#define TIMER_BLINK_ID      2

void set_timer(uint8_t index, uint32_t duration_ms);
uint8_t is_timer_expired(uint8_t index);
void timer_run(void);
void set_timer_tick(int psc, int arr);

#endif /* INC_TIMER_H_ */
