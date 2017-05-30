#ifndef PVTEST_GPIO_CONFIG_H
#define PVTEST_GPIO_CONFIG_H

#define LED1_On BB(GPIOD->ODR,PD12)=1;
#define LED1_Off BB(GPIOD->ODR,PD12)=0;
#define LED1_Toggle BB(GPIOD->ODR,PD12)^=1;

#define LED2_On BB(GPIOD->ODR,PD13)=1;
#define LED2_Off BB(GPIOD->ODR,PD13)=0;
#define LED2Toggle BB(GPIOD->ODR,PD13)^=1;

#define LED3_On BB(GPIOD->ODR,PD14)=1;
#define LED3_Off BB(GPIOD->ODR,PD14)=0;
#define LED3_Toggle BB(GPIOD->ODR,PD14)^=1;

#define LED4_On BB(GPIOD->ODR,PD15)=1;
#define LED4_Off BB(GPIOD->ODR,PD15)=0;
#define LED4_Toggle BB(GPIOD->ODR,PD15)^=1;

extern const uint16_t resistors_state[84];
extern void GPIO_configuration(void);
extern void MOSFET_control(uint8_t);

#endif
