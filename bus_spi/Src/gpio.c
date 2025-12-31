#include <stdint.h>
#include <stm32f446xx.h>
#include "main.h"
#include "gpio.h"

void GPIO_Init(void){
	/* Clock Init */
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN | RCC_AHB1ENR_GPIOCEN;

	/* GPIO Init */

	GPIOC->MODER |= INPUT_MODE	<< 26;		// PC13 Input Push-Button

	/* SPI1 GPIO init */
	GPIOA->MODER |= OUTPUT_MODE << 8;  // PA4 Output (CS)
	GPIOA->MODER |= ALT_MODE << 10;    // PA5 Alternate (SCK)
	GPIOA->MODER |= ALT_MODE << 12;    // PA6 Alternate (MISO)
	GPIOA->MODER |= ALT_MODE << 14;    // PA7 Alternate (MOSI)

	/* Clear AFRL bits for PA5, PA6, PA7 */
	GPIOA->AFR[0] &= ~(GPIO_AFRL_AFSEL5_Msk | GPIO_AFRL_AFSEL6_Msk | GPIO_AFRL_AFSEL7_Msk);

	/* Set AF5 for SPI1 */
	GPIOA->AFR[0] |= (5U << GPIO_AFRL_AFSEL5_Pos)  // PA5 SCK
	               | (5U << GPIO_AFRL_AFSEL6_Pos)  // PA6 MISO
	               | (5U << GPIO_AFRL_AFSEL7_Pos); // PA7 MOSI

}


void GPIO_SetPin(GPIO_TypeDef* GPIO, uint16_t pin){
	GPIO->ODR |= 1 << pin ;
}

void GPIO_ResetPin(GPIO_TypeDef* GPIO, uint16_t pin){
	GPIO->ODR &= ~(1 << pin) ;
}

void GPIO_TogglePin(GPIO_TypeDef* GPIO, uint16_t pin){
	GPIO->ODR ^= 1 << pin ;
}

uint16_t GPIO_ReadPin(GPIO_TypeDef* GPIO, uint16_t pin){
	if((GPIO->IDR & (1 << pin)) !=0)	return 1;
	else 								return 0;
}
