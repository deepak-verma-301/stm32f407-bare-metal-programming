#include<stdint.h>
#include<stm32f407xx.h>


int main(){

    RCC->AHB1ENR |= (1<<0);      // Enabling the portA clock
    RCC->AHB1ENR |= (1<<3);     // Enabling the portD clock 

    GPIOD->MODER &= ~(3<<(13*2));
    GPIOD->MODER |= (1<<(13*2));  // setting the portD pin 13 as output pin

    GPIOA->MODER &= ~(3<<0);     // setting the portA pin 0 as input pin for button

    while (1)
    {
        if (GPIOA->IDR & (1<<0))   // checking the IDR register if the button is pressed or not
        {
            GPIOD->ODR |= (1<<13);   // turn on the led if button is pressed
        }

        else{
            GPIOD->ODR &= ~(1<<13);  // turn off the led if the button is released
        }
        
    }
    


    return 0;
}