#ifndef __BSP_MOTOR_H
#define __BSP_MOTOR_H	

#include "gd32vf103_gpio.h"

void motor_init(uint32_t gpio_periph, uint32_t pin1, uint32_t pin2, uint32_t pin3, uint32_t pin4);

void motor_run(int8_t direction);

void debug_button_init(uint32_t gpio_periph, uint32_t pin);

void debug_lamp(uint32_t gpio_periph, uint32_t pin1);

#endif