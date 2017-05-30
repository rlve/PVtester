#include "stm32f4xx.h"
#include "pvtest_tim_config.h"

void Timer_configuration(void){
	//Setting main timer - TIM2/
	RCC->APB1ENR |= RCC_APB1ENR_TIM2EN; 			//enable clock for timer
//	RCC->APB1LPENR &= ~(RCC_APB1ENR_TIM2EN); 		//disable clock in sleep mode

	TIM2->PSC=42000-1;								//prescaler, 84MHz/42000 = 2kHz
//	TIM2->ARR=2000-1;								//counting to 2000 = 1s
	TIM2->ARR=400-1;								//counting to 40 = 20ms
	TIM2->DIER|=TIM_DIER_UIE;						//enable interrupt
//	TIM2->CR1|=TIM_CR1_CEN; 						//turn on timer

	NVIC_EnableIRQ(TIM2_IRQn); 						//enable interrupt controller

}
