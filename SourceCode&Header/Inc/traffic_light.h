/*
 * traffic_light.h
 *
 *  Created on: Oct 28, 2026
 *      Author: Admin
 */

#ifndef INC_TRAFFIC_LIGHT_H_
#define INC_TRAFFIC_LIGHT_H_

#include <stdint.h>

void traffic_light_init(void);
void traffic_light_update(void);

uint8_t traffic_light_get_horizontal_remaining(void);
uint8_t traffic_light_get_vertical_remaining(void);

#endif /* INC_TRAFFIC_LIGHT_H_ */
