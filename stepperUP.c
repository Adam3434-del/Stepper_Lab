#include "stepperUP.h"

static uint16_t adc_read(uint8_t ch){
    adc_regular_channel_config(ADC0, 0, ch, ADC_SAMPLETIME_55POINT5);
    adc_software_trigger_enable(ADC0, ADC_REGULAR_CHANNEL);
    while(!adc_flag_get(ADC0, ADC_FLAG_EOC));
    adc_flag_clear(ADC0, ADC_FLAG_EOC);
    return adc_regular_data_read(ADC0);
}

void stepperUP_init(void){
    rcu_periph_clock_enable(RCU_GPIOA);
    rcu_periph_clock_enable(RCU_GPIOB);
    rcu_periph_clock_enable(RCU_ADC0);
    rcu_adc_clock_config(RCU_CKADC_CKAPB2_DIV8); 

    gpio_init(GPIOA, GPIO_MODE_OUT_PP, GPIO_OSPEED_2MHZ, GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3);//output stepper motor pins
    gpio_init(GPIOA, GPIO_MODE_AIN, GPIO_OSPEED_2MHZ, GPIO_PIN_5 | GPIO_PIN_6); //Input pins for ADC for sensors #Sensors dont work!
    gpio_init(GPIOB, GPIO_MODE_OUT_PP, GPIO_OSPEED_2MHZ, GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2); //Debugg lamps
    gpio_init(GPIOA, GPIO_MODE_IPU, GPIO_OSPEED_2MHZ, GPIO_PIN_7); 

    adc_deinit(ADC0);
    adc_mode_config(ADC_MODE_FREE);
    adc_data_alignment_config(ADC0, ADC_DATAALIGN_RIGHT);
    adc_channel_length_config(ADC0, ADC_REGULAR_CHANNEL, 1);
    adc_external_trigger_source_config(ADC0, ADC_REGULAR_CHANNEL, ADC0_1_EXTTRIG_REGULAR_NONE);
    adc_external_trigger_config(ADC0, ADC_REGULAR_CHANNEL, ENABLE);
    adc_enable(ADC0);
    adc_calibration_enable(ADC0);

    Lcd_Init(); //Initialize the LCD to debug sensor values
    LCD_Fill(WHITE, 0, 0, LCD_W - 1, LCD_H - 1);



    
}

void stepperUP_step(void){
    static uint8_t phase = 0;
    static int8_t input = -1;

    uint16_t left  = adc_read(ADC_CHANNEL_5);
    uint16_t right = adc_read(ADC_CHANNEL_6);
    uint8_t button = gpio_input_bit_get(GPIOA, GPIO_PIN_7);
    if(button == 1) input = -1;
    else(input = 1);
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
    
    
    LCD_ShowNum(0, 0, left, 4, WHITE);
    LCD_ShowNum(0, 16, right, 4, WHITE);

    gpio_bit_reset(GPIOA, GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3);
    switch(phase){
        case 0: gpio_bit_set(GPIOA, GPIO_PIN_0); break;
        case 1: gpio_bit_set(GPIOA, GPIO_PIN_1); break;
        case 2: gpio_bit_set(GPIOA, GPIO_PIN_2); break;
        case 3: gpio_bit_set(GPIOA, GPIO_PIN_3); break;
    }

    if(input == 1) phase = (phase + 1) % 4;
    else           phase = (phase + 3) % 4;   

    
}