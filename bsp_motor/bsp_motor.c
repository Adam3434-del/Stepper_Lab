#include "bsp_motor/bsp_motor.h"



 static uint8_t dir = 1; // 1 for clockwise, 0 for counterclockwise
static int8_t phase = 0; // 0-3 for the four phases of the stepper motor
static uint8_t pins[4] = {};
static uint32_t peripheral = 0; // Store the GPIO peripheral for the motor pins

static uint32_t button_peripheral = 0; // Store the GPIO peripheral for the button pin
static uint8_t button_pin = 0; // Store the GPIO pin for the button

static void gpio_clock_on(uint32_t port){
    switch (port) {
        case GPIOA: rcu_periph_clock_enable(RCU_GPIOA); break;
        case GPIOB: rcu_periph_clock_enable(RCU_GPIOB); break;
        case GPIOC: rcu_periph_clock_enable(RCU_GPIOC); break;
        case GPIOD: rcu_periph_clock_enable(RCU_GPIOD); break;
        case GPIOE: rcu_periph_clock_enable(RCU_GPIOE); break;
        default: break;
    }
}

void motor_init(uint32_t gpio_periph, uint8_t pin1, uint8_t pin2, uint8_t pin3, uint8_t pin4){
    gpio_clock_on(gpio_periph);

    peripheral = gpio_periph;
    pins[0] = pin1;
    pins[1] = pin2;
    pins[2] = pin3;
    pins[3] = pin4;

    for(int i = 0; i < 4; i++){
        gpio_init(peripheral, GPIO_MODE_OUT_PP, GPIO_OSPEED_2MHZ, pins[i]);
    }

}

void set_motor_direction(int8_t direction){
    if(direction == 1 || direction == 0){
        dir = direction;
    }
    else{
        dir = 1; 
    }
}
void motor_run(){
    if(dir == 1){
        phase++;
        if(phase > 3) phase = 0;
    }
    else if(dir == 0){
        phase--;
        if(phase < 0) phase = 3;
    }
    else return;

    switch(phase){
        case 0:
            gpio_bit_set(peripheral, pins[0]);
            gpio_bit_reset(peripheral, pins[1] | pins[2] | pins[3]);
            break;
        case 1:
            gpio_bit_set(peripheral, pins[1]);
            gpio_bit_reset(peripheral, pins[0] | pins[2] | pins[3]);
            break;
        case 2:
            gpio_bit_set(peripheral, pins[2]);
            gpio_bit_reset(peripheral, pins[0] | pins[1] | pins[3]);
            break;
        case 3:
            gpio_bit_set(peripheral, pins[3]);
            gpio_bit_reset(peripheral, pins[0] | pins[1] | pins[2]);
            break;
    }
}

void debug_button_init(uint32_t gpio_periph, uint32_t pin){
    gpio_clock_on(gpio_periph);
    gpio_init(gpio_periph, GPIO_MODE_IPU, GPIO_OSPEED_2MHZ, pin); 
    button_peripheral = gpio_periph;
    button_pin = pin;
}

void debug_button_read(){
    dir = gpio_input_bit_get(button_peripheral, button_pin);
}

void debug_lamp(uint32_t gpio_periph, uint32_t pin1, uint8_t state){
    gpio_clock_on(gpio_periph);
    gpio_init(gpio_periph, GPIO_MODE_OUT_PP, GPIO_OSPEED_2MHZ, pin1);
    if(state == dir){
        gpio_bit_set(gpio_periph, pin1);
    }
    else{
        gpio_bit_reset(gpio_periph, pin1);
    }
}
