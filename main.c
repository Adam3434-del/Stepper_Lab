#include "stepperUP.h"
int main(void) {

    stepperUP_init();
    
    while(1){
        stepperUP_step();
    }
  
}