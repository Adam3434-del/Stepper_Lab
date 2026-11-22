#ifndef __BSP_SENSOR_H
#define __BSP_SENSOR_H

#include "gd32vf103_gpio.h"

void sensor_init(uint32_t gpio_periph, uint32_t pin1, uint32_t pin2);

void sensor_read(void);

#endif
