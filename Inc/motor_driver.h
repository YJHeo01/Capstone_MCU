/*
 * motor_driver.h
 *
 *  Created on: Nov 5, 2025
 *      Author: YJHeo01
 */


#ifndef DIR_PWM_DRIVER_H
#define DIR_PWM_DRIVER_H

#include "stm32f4xx_hal.h"
#include <stdint.h>

typedef struct {
    GPIO_TypeDef*       dir_port;   // DIRx
    uint16_t            dir_pin;
    TIM_HandleTypeDef*  htim;       // PWM 타이머
    uint32_t            pwm_channel;// TIM_CHANNEL_x
    uint32_t            arr;        // PWM 분해능 캐시
    uint8_t             invert;     // 방향 반전
} DirPwmMotor;

void DirPwm_Init(DirPwmMotor* m,
                 TIM_HandleTypeDef* htim, uint32_t channel,
                 GPIO_TypeDef* dir_port, uint16_t dir_pin,
                 uint8_t invert);

// speed: -1000 ~ +1000 (부호=방향, 크기=듀티)
void DirPwm_SetSpeed(DirPwmMotor* m, int16_t speed);

// 코스트(출력 OFF)
void DirPwm_Coast(DirPwmMotor* m);

#endif // DIR_PWM_DRIVER_H
