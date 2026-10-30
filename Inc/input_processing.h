/*
 * input_processing.h
 *
 *  Created on: Oct 28, 2026
 *      Author: Admin
 */

#ifndef INC_INPUT_PROCESSING_H_
#define INC_INPUT_PROCESSING_H_

void fsm_for_input_processing(void);
uint8_t get_mode(void);
uint8_t get_red_duration(void);
uint8_t get_yellow_duration(void);
uint8_t get_green_duration(void);
uint8_t get_edit_duration(void);

#endif /* INC_INPUT_PROCESSING_H_ */
