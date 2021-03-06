#include "stm32f4xx.h"
#include "pvtest_gpio_config.h"
#include "gpio.h"
#include "bb.h"

const uint16_t resistors_state[84]={0b0001000000000000,
		0b0000000000100000,
		0b0000000000010000,
		0b0001100000000000,
		0b0000100000100000,
		0b0000000000001000,
		0b0001000000010000,
		0b0000100000010000,
		0b0000000000000100,
		0b0001110000000000,
		0b0000000000110000,
		0b0001000000001000,
		0b0000100000001000,
		0b0001100000010000,
		0b0001000000000100,
		0b0000100000000100,
		0b0001111000000000,
		0b0000000000011000,
		0b0001100000001000,
		0b0001110000010000,
		0b0001100000000100,
		0b0001000000011000,
		0b0001111100000000,
		0b0001110000001000,
		0b0001000000010100,
		0b0001111000010000,
		0b0001110000000100,
		0b0001100000011000,
		0b0001111110000000,
		0b0001000000001100,
		0b0001111000001000,
		0b0001100000010100,
		0b0001111100010000,
		0b0001111000000100,
		0b0001110000011000,
		0b0001111111000000,
		0b0001100000001100,
		0b0001111100001000,
		0b0001110000010100,
		0b0001111110010000,
		0b0001111100000100,
		0b0001111000011000,
		0b0001110000001100,
		0b0001111111100000,
		0b0001111000010100,
		0b0001111111010000,
		0b0001111110000100,
		0b0001111100011000,
		0b0001111000001100,
		0b0001111111001000,
		0b0001111100010100,
		0b0001110000011100,
		0b0001111110011000,
		0b0001111100001100,
		0b0001111111101000,
		0b0001111110010100,
		0b0001111000011100,
		0b0001111111011000,
		0b0001111110001100,
		0b0001111111010100,
		0b0001111100011100,
		0b0001111111111000,
		0b0001111111110100,
		0b0001111111101100,
		0b0001111111011100,
		0b0001111111111100,
		0b0001100000000010,
		0b0001111000000010,
		0b0001000000011010,
		0b0001111000010010,
		0b0001111000001010,
		0b0001111111000010,
		0b0001111100001010,
		0b0001111111100010,
		0b0001111111001010,
		0b0001111111101010,
		0b0001111111010110,
		0b0001111111110110,
		0b0001111111101110,
		0b0001111111011110,
		0b0001111111111110,
		0b0001111110000001,
		0b0001111000000011,
		0b0001111111111111/*0x1FFF*/};

void GPIO_configuration(void){
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN|RCC_AHB1ENR_GPIOBEN|RCC_AHB1ENR_GPIOCEN|RCC_AHB1ENR_GPIODEN|RCC_AHB1ENR_GPIOEEN;			// enable clocks
	RCC->AHB1LPENR &= ~(RCC_AHB1LPENR_GPIOALPEN|RCC_AHB1LPENR_GPIOBLPEN|RCC_AHB1LPENR_GPIOCLPEN|RCC_AHB1LPENR_GPIODLPEN|RCC_AHB1LPENR_GPIOELPEN); 	// disable clocks in sleep mode
	__DSB();															// wait for memmory synchronization (just in case)

	/*4 LEDS*/
	gpio_pin_cfg(GPIOD, PD12, gpio_mode_output_PP_LS);
	gpio_pin_cfg(GPIOD, PD13, gpio_mode_output_PP_LS);
	gpio_pin_cfg(GPIOD, PD14, gpio_mode_output_PP_LS);
	gpio_pin_cfg(GPIOD, PD15, gpio_mode_output_PP_LS);

	/*Buttton */
	gpio_pin_cfg(GPIOA, PA0, gpio_mode_in_PD);

	/*Mosfets state control*/
	gpio_pin_cfg(GPIOE, PE13, gpio_mode_output_PP_HS); 	//R14 NA PEWNO
	gpio_pin_cfg(GPIOE, PE14, gpio_mode_output_PP_HS); 	//R13
	gpio_pin_cfg(GPIOE, PE11, gpio_mode_output_PP_HS); 	//R12
	gpio_pin_cfg(GPIOE, PE12, gpio_mode_output_PP_HS); 	//R11
	gpio_pin_cfg(GPIOE, PE9, gpio_mode_output_PP_HS); 	//R10
	gpio_pin_cfg(GPIOE, PE10, gpio_mode_output_PP_HS); 	//R9
	gpio_pin_cfg(GPIOE, PE8, gpio_mode_output_PP_HS); 	//R8
	gpio_pin_cfg(GPIOB, PB1, gpio_mode_output_PP_HS); 	//R7
	gpio_pin_cfg(GPIOA, PA7, gpio_mode_output_PP_HS); 	//R6
	gpio_pin_cfg(GPIOA, PA6, gpio_mode_output_PP_HS); 	//R5
	gpio_pin_cfg(GPIOA, PA3, gpio_mode_output_PP_HS); 	//R4
	gpio_pin_cfg(GPIOA, PA2, gpio_mode_output_PP_HS); 	//R3
	gpio_pin_cfg(GPIOE, PE15, gpio_mode_output_PP_HS); 	//R2
	gpio_pin_cfg(GPIOA, PA1, gpio_mode_output_PP_HS); 	//R1

	/*ADC inputs*/
	//gpio_pin_cfg(GPIOC,PC1,gpio_mode_analog);
	//gpio_pin_cfg(GPIOC,PC2,gpio_mode_analog);

	/* SEPIC PWM */
	//gpio_pin_cfg(GPIOE, PE14, gpio_mode_AF1_PP_PD_FS);

}

void MOSFET_control(uint8_t counter){
	if (counter==0){
		 BB(GPIOE->ODR,PE13)=0;		//R14
		 BB(GPIOE->ODR,PE14)=0;		//R13
		 BB(GPIOE->ODR,PE11)=0;		//R12
		 BB(GPIOE->ODR,PE12)=0;		//R11
		 BB(GPIOE->ODR,PE9)=0;		//R10
		 BB(GPIOE->ODR,PE10)=0;		//R9
		 BB(GPIOE->ODR,PE8)=0;		//R8
		 BB(GPIOB->ODR,PB1)=0;		//R7
		 BB(GPIOA->ODR,PA7)=0;		//R6
		 BB(GPIOA->ODR,PA6)=0;		//R5
		 BB(GPIOA->ODR,PA3)=0;		//R4
		 BB(GPIOA->ODR,PA2)=0;		//R3
		 BB(GPIOE->ODR,PE15)=0;		//R2
		 BB(GPIOA->ODR,PA1)=0;		//R1
	}

	else if (counter==85){
		BB(GPIOE->ODR,PE13)=1;
		BB(GPIOE->ODR,PE14)=0;
		BB(GPIOE->ODR,PE11)=0;
		BB(GPIOE->ODR,PE12)=0;
		BB(GPIOE->ODR,PE9)=0;
		BB(GPIOE->ODR,PE10)=0;
		BB(GPIOE->ODR,PE8)=0;
		BB(GPIOB->ODR,PB1)=0;
		BB(GPIOA->ODR,PA7)=0;
		BB(GPIOA->ODR,PA6)=0;
		BB(GPIOA->ODR,PA3)=0;
		BB(GPIOA->ODR,PA2)=0;
		BB(GPIOE->ODR,PE15)=0;
		BB(GPIOA->ODR,PA1)=0;
	}

	else if (counter==86){
		BB(GPIOE->ODR,PE13)=0;
		BB(GPIOE->ODR,PE14)=0;
		BB(GPIOE->ODR,PE11)=0;
		BB(GPIOE->ODR,PE12)=0;
		BB(GPIOE->ODR,PE9)=0;
		BB(GPIOE->ODR,PE10)=0; //change for BB(GPIOE->ODR,PE13) (!!!!)
		BB(GPIOE->ODR,PE8)=0;
		BB(GPIOB->ODR,PB1)=0;
		BB(GPIOA->ODR,PA7)=0;
		BB(GPIOA->ODR,PA6)=0;
		BB(GPIOA->ODR,PA3)=0;
		BB(GPIOA->ODR,PA2)=0;
		BB(GPIOE->ODR,PE15)=0;
		BB(GPIOA->ODR,PA1)=0;
//		TIM2->CR1^=TIM_CR1_CEN;
	}

	else{
		BB(GPIOA->ODR,PA1)=(uint32_t)(resistors_state[counter-1]&0b0001000000000000)>>12; //R1
		BB(GPIOE->ODR,PE15)=(uint32_t)(resistors_state[counter-1]&0b0000100000000000)>>11;
		BB(GPIOA->ODR,PA2)=(uint32_t)(resistors_state[counter-1]&0b0000010000000000)>>10;
		BB(GPIOA->ODR,PA3)=(uint32_t)(resistors_state[counter-1]&0b0000001000000000)>>9;
		BB(GPIOA->ODR,PA6)=(uint32_t)(resistors_state[counter-1]&0b0000000100000000)>>8;
		BB(GPIOA->ODR,PA7)=(uint32_t)(resistors_state[counter-1]&0b0000000010000000)>>7; //change for BB(GPIOE->ODR,PE13) (!!!!)
		BB(GPIOB->ODR,PB1)=(uint32_t)(resistors_state[counter-1]&0b0000000001000000)>>6;
		BB(GPIOE->ODR,PE8)=(uint32_t)(resistors_state[counter-1]&0b0000000000100000)>>5;
		BB(GPIOE->ODR,PE10)=(uint32_t)(resistors_state[counter-1]&0b0000000000010000)>>4;
		BB(GPIOE->ODR,PE9)=(uint32_t)(resistors_state[counter-1]&0b0000000000001000)>>3;
		BB(GPIOE->ODR,PE12)=(uint32_t)(resistors_state[counter-1]&0b0000000000000100)>>2;
		BB(GPIOE->ODR,PE11)=(uint32_t)(resistors_state[counter-1]&0b0000000000000010)>>1;
		BB(GPIOE->ODR,PE14)=(uint32_t)(resistors_state[counter-1]&0b0000000000000001);
		BB(GPIOE->ODR,PE13)=0;															//R14
	}

}
