#include <stdint.h>
#include <stm32f446xx.h>
#include "main.h"
#include "gpio.h"
#include "bus_spi.h"

/*SPI_PINOUT mosiSPI1 = {GPIOA, 6};
SPI_PINOUT misoSPI1 = {GPIOA, 7};*/


void SPI1_Init(void){
	/* Enable SPI1 clock */
	RCC->APB2ENR |= RCC_APB2ENR_SPI1EN;

	/* Configure SPI1 */
	SPI1->CR1 = SPI_CR1_MSTR       // Mode master
	          | SPI_CR1_SSM        // NSS logiciel activé
	          | SPI_CR1_SSI        // NSS interne à 1 (valide le master)
	          | SPI_CR1_BR_1       // Baudrate prescaler fPCLK/16
	          | SPI_CR1_SPE;       // Activation du SPI
}

uint8_t SPI1_TransmiReceive(uint8_t spiData){
	SPI1->DR = spiData;
	while(!(SPI1->SR & SPI_SR_TXE_Msk));  // Attendre que TX buffer soit vide
	while(!(SPI1->SR & SPI_SR_RXNE_Msk)); // Attendre que RX buffer contienne des données
	return SPI1->DR;
}

#define SX1272_CS_PORT GPIOA
#define SX1272_CS_PIN  4

void SPI1_ResetSS(void){
    SX1272_CS_PORT->ODR &= ~(1U << SX1272_CS_PIN); // CS = 0
}

void SPI1_SetSS(void){
    SX1272_CS_PORT->ODR |= (1U << SX1272_CS_PIN);  // CS = 1
}
