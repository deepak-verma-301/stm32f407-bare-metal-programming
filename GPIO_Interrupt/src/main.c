#include<stdint.h>
#include<stm32f407xx.h>
#include<core_cm4.h>

void EXTI0_IRQHandler(){              // IRQHandler function 
    if(EXTI->PR & (1<<0)){            // check if the PR register bits is set or not 
        EXTI->PR |= (1<<0);          // clear the bit after checking the bit status
        if(GPIOA->IDR & (1<<0)){     // check if the button is pressed or not 
        GPIOD->ODR |= (1<<13);      // if button pressed turn on the led 
        }
        else{
            GPIOD->ODR &= ~(1<<13); // if button not pressed turn off the led 
        }
    }

    
}

int main(){

    RCC->AHB1ENR |= (1<<0);     //enabling portA for onboard user button 
    RCC->AHB1ENR |= (1<<3);     //enabling portD for onboard user led 
    RCC->APB2ENR |= (1<<14);    //enabling SYSCFG for mapping the ports with EXTI lines 

   
    GPIOA->MODER &= ~(3<<0);    //setting the PortA pin 0 as Input Mode
    GPIOD->MODER &= ~(3<<(13*2)); 
    GPIOD->MODER |= (1<<(13*2)); //setting the PortD pin 13 as Output Mode
    GPIOD->MODER &= ~(3<<(14*2)); 
    GPIOD->MODER |= (1<<(14*2)); //setting the PortD pin 14 as Output Mode

    SYSCFG->EXTICR[0] &= ~(0XF << 0); //mapping the portA to the EXTI lines
    EXTI->RTSR |= (1<<0);       //set for rising edge for the button
    EXTI->FTSR |= (1<<0);       //set for falling edge for the button 
    EXTI->IMR |= (1<<0);    // Interrupt request for EXTI line 0 is enabled
    EXTI->PR |= (1<<0);     // clearing the PR register if triggered previously

    NVIC->ISER[0] |= (1<<6);  //writting the IRQ number to the cortex-M4 NVIC register for EXTI0 lines


    while(1){
        GPIOD->ODR ^= (1<<14);
        for(volatile uint32_t i = 0; i<=100000;i++){
            __asm("NOP");
        }
    }

    return 0;
}