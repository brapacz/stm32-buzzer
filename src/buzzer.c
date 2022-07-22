/*
 * status_led.h
 *
 *  Created on: 19.07.2022
 *      Author: bartek
 */

#include "./buzzer.h"

void Buzzer_Note(Buzzer_HandleTypeDef* handle, uint32_t noteFreq) {
//	printf("note %d\r\n", noteFreq);
	if(noteFreq > 0) {
		handle->Init.timer->Instance->ARR=handle->Init.timerClockFreqHz/(handle->Init.timer->Init.Prescaler+1)/noteFreq;
		__HAL_TIM_SET_COMPARE(handle->Init.timer, handle->Init.channel, handle->Init.timer->Instance->ARR/2);
	} else
		__HAL_TIM_SET_COMPARE(handle->Init.timer, handle->Init.channel, 0);
}

void Buzzer_NoNote(Buzzer_HandleTypeDef* handle) {
	Buzzer_Note(handle,0);
}

void Buzzer_Init(Buzzer_HandleTypeDef* handle, Buzzer_InitTypeDef* config) {
	handle->Init = *config;
}

void Buzzer_Start(Buzzer_HandleTypeDef* handle) {
	Buzzer_NoNote(handle);
	HAL_TIM_PWM_Start(handle->Init.timer, handle->Init.channel);
}
