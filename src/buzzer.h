/*
 * status_led.h
 *
 *  Created on: 19.07.2022
 *      Author: bartek
 */

#include "main.h"

#ifndef BUZZER_H_
#define BUZZER_H_

#ifdef __cplusplus
extern "C" {
#endif

typedef struct
{
	TIM_HandleTypeDef *timer;
	__IO uint32_t channel;
	uint32_t timerClockFreqHz;
} Buzzer_InitTypeDef;

typedef struct
{
	Buzzer_InitTypeDef Init;
	uint8_t value;
	uint16_t blinkFreqHz;
	uint16_t clock;
	uint16_t clockPeriod;
} Buzzer_HandleTypeDef;

void Buzzer_Note(Buzzer_HandleTypeDef* handle, uint32_t noteFreq);
void Buzzer_NoNote(Buzzer_HandleTypeDef* handle);
void Buzzer_Init(Buzzer_HandleTypeDef* handle, Buzzer_InitTypeDef* config);
void Buzzer_Start(Buzzer_HandleTypeDef* handle);


#ifdef __cplusplus
}
#endif

#endif /* BUZZER_H_ */
