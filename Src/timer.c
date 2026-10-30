/*
 * timer.c
 *
 *  Created on: Oct 28, 2026
 *      Author: Admin
 */
#include "timer.h"
#include "main.h"
#include "input_reading.h"

#define MAX_TIMERS 4

static volatile int timer_counters[MAX_TIMERS] = {0};
static volatile uint8_t timer_flags[MAX_TIMERS] = {0};
static volatile int TIMER_TICK = 10;

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if (htim->Instance == TIM2)
    {
        button_reading();
        timer_run();
    }
}

void set_timer(uint8_t index, uint32_t duration_ms)
{
    if (index >= MAX_TIMERS) return;

    int tick = (TIMER_TICK > 0) ? TIMER_TICK : 1;
    int ticks = (int)(duration_ms / tick);

    if (ticks <= 0 && duration_ms > 0)
    {
        ticks = 1;
    }

    timer_counters[index] = ticks;
    timer_flags[index] = 0;
}

void timer_run(void)
{
    for (int i = 0; i < MAX_TIMERS; i++)
    {
        if (timer_counters[i] > 0)
        {
            timer_counters[i]--;
            if (timer_counters[i] <= 0)
                timer_flags[i] = 1;
        }
    }
}

uint8_t is_timer_expired(uint8_t index)
{
    if (index < MAX_TIMERS)
    {
        if (timer_flags[index] == 1)
        {
            timer_flags[index] = 0;
            return 1;
        }
    }
    return 0;
}

void set_timer_tick(int psc, int arr)
{
    int calculated_tick = (psc + 1) * (arr + 1) / 8000;
    TIMER_TICK = (calculated_tick > 0) ? calculated_tick : 1;
}
