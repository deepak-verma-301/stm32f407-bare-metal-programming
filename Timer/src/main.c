#include<stdint.h>
#include<stm32f407xx.h>


int main(){
    RCC->AHB1ENR |= (1<<3);     //enabling the clock for GPIOD 
    RCC->APB1ENR |= (1<<0);      //enabling the TIM2 clock 

    GPIOD->MODER &= ~(3<<(13*2));
    GPIOD->MODER |= (1<<(13*2));

    TIM2->CR1 &= ~(3<<5);       //selecting edge-aligned mode
    TIM2->CR1 |= (1<<4);       //setting the DIR bit for using up-counter
    TIM2->PSC = 15999;         //setting the prescalar value to 16000 i.e (current clock speed/(PSC+1)) 
    TIM2->ARR = 1000;         //load auto-reload-register with 1000
    TIM2->EGR |= (1<<0);     //setting the update generation bit 
    TIM2->CR1 |= (1<<0);      //enabling the counter

    while(1){
        if(TIM2->CNT < 500){         //check if the ARR i.e counter value is less than 500
            GPIOD->ODR |= (1<<13);   //if less that 500 turn on the PORTD pin 13 led
        }
        else{
            GPIOD->ODR &= ~(1<<13);  //else off thd PORTD pin 13 led 
        }
    }



    return 0;
}