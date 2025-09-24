#include<stdint.h>
#include<stdbool.h>
#include<stm32f4xx.h>
#include<stm32f407xx.h>
#include<core_cm4.h>      //***Note this header files must come after stm32f407xx.h header file otherwise build fails 

bool TIM2_INT = false;

void TIM2_IRQHandler(){
    if(TIM2->SR & (1<<0)){
         TIM2->SR &= ~(1<<0);
        TIM2_INT = !TIM2_INT;
        
    }
}

int main(){

    RCC->APB1ENR |= (1<<0);
    RCC->AHB1ENR |= (1<<3);

    GPIOD->MODER &= ~(3<<(15*2));
    GPIOD->MODER |= (1<<(15*2));

    TIM2->CR1 &= ~(3<<5);
    TIM2->CR1 &= ~(1<<4);
    TIM2->ARR = 1000;
    TIM2->PSC = 31999;
    TIM2->EGR |= (1<<0);
    TIM2->DIER |= (1<<0);
    TIM2->SR &= ~(1<<0);
    TIM2->CR1 |= (1<<0);

    NVIC->ISER[0] |= (1<<28);

    while(1){
        if(TIM2_INT){
            GPIOD->ODR |= (1<<15);
        }
        else{
            GPIOD->ODR &= ~(1<<15);
        }
    }


    return 0;
}