
#ifndef STEPPERUP_H
#define STEPPERUP_H 
#include "gd32vf103_gpio.h" //remove after the bsp_motor and bsp_sensor are implemented
#include "bsp_motor/bsp_motor.h"
#include "bsp_sensor/bsp_sensor.h"
#include "lcd.h"



void stepperUP_init(void);
void stepperUP_step(void);
#endif
