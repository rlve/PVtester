#include "stm32f4xx.h"
#include "gpio.h"
#include "pvtest_uc_config.h"

void Initialization_uC(void){
	/**************************************************************************/
	/*Clocks and flash initialization */
	//enable HSE clock 8MHz, bypass for access to HSE
	RCC->CR |= RCC_CR_HSEON | RCC_CR_HSEBYP;
	//PLL configuration M=4, N=168, Q=7, P=2, PLL source HSE, reserved bit
	RCC->PLLCFGR = 4ul<<0 | 168ul<<6 | 7ul<<24 | RCC_PLLCFGR_PLLSRC_HSE | 1ul<<29;
	//spread spectrum configuration (?)
	RCC->SSCGR = 500ul<<0 | 44ul<<13 | RCC_SSCGR_SSCGEN;
	while (!(RCC->CR & RCC_CR_HSERDY)); 								// wait for HSE
	RCC->CR |= RCC_CR_PLLON; 											// enable PLL
	RCC->CFGR = RCC_CFGR_PPRE1_DIV4 | RCC_CFGR_PPRE2_DIV2; 				// bus prescalers

	FLASH->ACR = FLASH_ACR_DCRST | FLASH_ACR_ICRST; 					// flash cache reset
	//enable flash features, necessary latency 5waitstates
	FLASH->ACR = FLASH_ACR_DCEN | FLASH_ACR_ICEN | FLASH_ACR_PRFTEN | FLASH_ACR_LATENCY_5WS;
	while ((FLASH->ACR & FLASH_ACR_LATENCY) != FLASH_ACR_LATENCY_5WS); 	// wait for new configuration

	while (!(RCC->CR & RCC_CR_PLLRDY)); 								// waiting for PLL
	RCC->CFGR |= RCC_CFGR_SW_PLL; 										// SYSCLK from PLL
	while ((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_PLL); 			// waiting for new setup
	RCC->CR &= ~RCC_CR_HSION;											// disable HSI

	/**************************************************************************/
	/* SYSTICK */
//	SysTick_Config(168000000ul/8/2); 									// interrupt per 0.5 s
//	SysTick->CTRL &= ~SysTick_CTRL_CLKSOURCE_Msk; 						// source for systick AHB/8


	/**************************************************************************/
	/* IO cell compensation */
	RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;  								// SYSCFG enable
	SYSCFG->CMPCR = SYSCFG_CMPCR_CMP_PD;
	while (!(SYSCFG->CMPCR & SYSCFG_CMPCR_READY));


	/**************************************************************************/
	/* Interrupt from button */
//	RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN; 								//enabled before, systick!
	EXTI->IMR|=EXTI_IMR_MR0; 											//interrupt line 0, button on PA0
	EXTI->RTSR|=EXTI_RTSR_TR0;											//rising edge trigger

	NVIC_EnableIRQ(EXTI0_IRQn);											//enable interrupt controller
}
