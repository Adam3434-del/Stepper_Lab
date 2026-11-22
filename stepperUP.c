#include "stepperUP.h"

static uint16_t adc_read(uint8_t ch){
    adc_regular_channel_config(ADC0, 0, ch, ADC_SAMPLETIME_55POINT5);
    adc_software_trigger_enable(ADC0, ADC_REGULAR_CHANNEL);
    while(!adc_flag_get(ADC0, ADC_FLAG_EOC));
    adc_flag_clear(ADC0, ADC_FLAG_EOC);
    return adc_regular_data_read(ADC0);
}

void stepperUP_init(void){
    motor_init(GPIOA, GPIO_PIN_0, GPIO_PIN_1, GPIO_PIN_2, GPIO_PIN_3);
    debug_button_init(GPIOA, GPIO_PIN_7);

   
}

static void step_delay(void){
   // For some reason depending on what stuff you have added you need to change the delay to get the motor to run at a reasonable speed.
    for (volatile uint32_t i = 0; i < 100000u; i++) {
    }
}

void stepperUP_step(void){
    motor_run();
    step_delay();
    debug_button_read();
    debug_lamp(GPIOB, GPIO_PIN_0, 0);
    debug_lamp(GPIOB, GPIO_PIN_1, 1);
    debug_lamp(GPIOB, GPIO_PIN_2, 2);

    //debug_button_read();

    /*
    if(right > 1600){
        input = -1;
        gpio_bit_reset(GPIOB, GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2);
        gpio_bit_set(GPIOB, GPIO_PIN_0);
    }
    if(left > 1600){
        input = 1;
        gpio_bit_reset(GPIOB, GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2);
        gpio_bit_set(GPIOB, GPIO_PIN_1 | GPIO_PIN_2);
    }
        */
    

  
    
}
