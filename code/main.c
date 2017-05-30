#include "stm32f4xx.h"
#include "bb.h"
#include "gpio.h"
#include "pvtest_gpio_config.h"
#include "pvtest_uc_config.h"
#include "pvtest_tim_config.h"
#include "pvtest_adcdma_config.h"

volatile uint8_t timer_cycles=0;							//main timer cycles counter
extern uint16_t *wyniki;
	int tim3=0;
	int tim2=0;
	int licznik=0;

int main(void){
	Initialization_uC();
	GPIO_configuration();
	Timer_configuration();
	ADCDMA_configuration();

	LED3_Toggle;
//	timer_cycles=0;										//clear counter
//	TIM2->CR1|=TIM_CR1_CEN; 							//turn on timer

//	LED1_Toggle;
//
//	RCC->APB1LPENR |= RCC_APB1LPENR_TIM2LPEN; 				//enable clock in sleep mode
//	RCC->APB1LPENR |= RCC_APB1LPENR_TIM3LPEN; 				//enable clock in sleep mode
//	RCC->AHB1LPENR |= RCC_AHB1LPENR_DMA2LPEN; 		//enable clock in sleep mode
//	RCC->APB2LPENR |= RCC_APB2LPENR_ADC1LPEN;		//enable clock in sleep mode
//	RCC->APB2LPENR |= RCC_APB2LPENR_TIM1LPEN;

	DBGMCU->CR |= DBGMCU_CR_DBG_SLEEP;
	SCB->SCR |= SCB_SCR_SLEEPONEXIT_Msk; 					//enter sleep on return from an interrupt service routine
	__WFI();												//sleeping mode, wait for interrupt
}
void EXTI0_IRQHandler(void){
	if(EXTI->PR&EXTI_PR_PR0){								//check interrupt flag
		EXTI->PR=EXTI_PR_PR0;								//clear flag

//		LED3_On;
//		LED4_On;
		timer_cycles=0;										//clear counter
		TIM2->CR1|=TIM_CR1_CEN; 							//turn on timer
		RCC->APB1LPENR |= RCC_APB1LPENR_TIM2LPEN; 				//enable clock in sleep mode
		RCC->APB1LPENR |= RCC_APB1LPENR_TIM3LPEN; 				//enable clock in sleep mode
		RCC->AHB1LPENR |= RCC_AHB1LPENR_DMA2LPEN; 		//enable clock in sleep mode
		RCC->APB2LPENR |= RCC_APB2LPENR_ADC1LPEN;		//enable clock in sleep mode
		RCC->APB2LPENR |= RCC_APB2LPENR_TIM1LPEN;
	}
}

 void TIM2_IRQHandler(void){
	 if(TIM2->SR & TIM_SR_UIF){								//checking interrupt flag
	 		TIM2->SR &= ~TIM_SR_UIF;								//clear flag
//	 		++tim2;
	 		LED1_Toggle;
	 		LED3_Toggle;
	 		MOSFET_control(timer_cycles);

//	 		/* pwm test */
//	 		if (++licznik<20)
//	 		{
//	 		TIM1->CCR4 = licznik;}
//	 		else if (licznik>=20){licznik=0;}

		if(++timer_cycles>=87){								//increase counter, if reaches threshold, disable timer
			TIM2->CR1^=TIM_CR1_CEN;
//			ADC1->SR &= ~(ADC_SR_EOC);
			RCC->APB1LPENR &= ~(RCC_APB1LPENR_TIM2LPEN); 		//disable clock in sleep mode
			RCC->APB1LPENR &= ~(RCC_APB1LPENR_TIM3LPEN); 		//disable clock in sleep mode
			RCC->AHB1LPENR &= ~(RCC_AHB1LPENR_DMA2LPEN); 		//disable clock in sleep mode
			RCC->APB2LPENR &= ~(RCC_APB2LPENR_ADC1LPEN);		//disable clock in sleep mode
			RCC->APB2LPENR &= ~(RCC_APB2LPENR_TIM1LPEN);

//			LED3_Off;
//			LED4_Off;
		}
	}
 }

//void TIM3_IRQHandler(void){
//	if(TIM3->SR & TIM_SR_UIF){								//checking interrupt flag
//		TIM3->SR &= ~TIM_SR_UIF;							//clear flag
//		LED3_Toggle;
//		++tim3;
//	}
//}
//
//void ADC_IRQHandler(void){
//
//		LED4_Toggle;
////		printf(wyniki[0], wyniki[1]);
//}

/*
void SysTick_Handler(void){
		BB(GPIOD->ODR, PD13) ^= 1;
	}
*/

void test_run(uint8_t counter){

	//	 BB(GPIOA->ODR,PA1)=1;		//R1
	//	 BB(GPIOA->ODR,PA1)=0;		//R1
	//
	//	 BB(GPIOA->ODR,PA0)=1;		//R2
	//	 BB(GPIOA->ODR,PA0)=0;		//R2
	//
	//	 BB(GPIOA->ODR,PA2)=1;		//R3
	//	 BB(GPIOA->ODR,PA2)=0;		//R3
	//
	//	 BB(GPIOA->ODR,PA3)=1;		//R4
	//	 BB(GPIOA->ODR,PA3)=0;		//R4
	//
	//	 BB(GPIOA->ODR,PA6)=1;		//R5
	//	 BB(GPIOA->ODR,PA6)=0;		//R5
	//
	//	 BB(GPIOA->ODR,PA7)=1;		//R6
	//	 BB(GPIOA->ODR,PA7)=0;		//R6
	//
	//	 BB(GPIOB->ODR,PB1)=1;		//R7
	//	 BB(GPIOB->ODR,PB1)=0;		//R7
	//
	//	 BB(GPIOE->ODR,PE8)=1;		//R8
	//	 BB(GPIOE->ODR,PE8)=0;		//R8
	//
	//	 BB(GPIOE->ODR,PE10)=1;		//R9
	//	 BB(GPIOE->ODR,PE10)=0;		//R9
	//
	//	 BB(GPIOE->ODR,PE9)=1;		//R10
	//	 BB(GPIOE->ODR,PE9)=0;		//R10
	//
	//	 BB(GPIOE->ODR,PE12)=1;		//R11
	//	 BB(GPIOE->ODR,PE12)=0;		//R11
	//
	//	 BB(GPIOE->ODR,PE11)=1;		//R12
	//	 BB(GPIOE->ODR,PE11)=0;		//R12
	//
	//	 BB(GPIOE->ODR,PE14)=1;		//R13
	//	 BB(GPIOE->ODR,PE14)=0;		//R13
	//
	//	 BB(GPIOE->ODR,PE13)=1;		//R14
	//	 BB(GPIOE->ODR,PE13)=0;		//R14

}
