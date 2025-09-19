#include<stdint.h>           
#include<stm32f407xx.h>   //including the standard header files of registers definition of F407 discovery board



int main(){

RCC->AHB1ENR |= (1<<3);    // Enabling the GPIOD peripheral clock

GPIOD->MODER &= ~(3<<(12*2));    // clearing the 24th and 25th bit field of MODER register
GPIOD->MODER |= (1<<(12*2));    // setting the 24th bit so that pin 12 behave as OUTPUT pin 


while (1)
{
    GPIOD->ODR ^= (1<<12);     // toggling the 12th pin 

    for (volatile uint32_t i = 0; i <1000000; i++)   // creatintg the crude delay function 
    {
        __asm("NOP");
    }

    
}

    return 0;
}