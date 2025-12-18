#include <stdint.h>
#include <stm32f446xx.h>
#include "main.h"
#include "gpio.h"
#include "bus_spi.h"

/*SPI_PINOUT mosiSPI1 = {GPIOA, 6};
SPI_PINOUT misoSPI1 = {GPIOA, 7};*/


uint8_t SPI1_TransmiReceive(uint8_t spiData){
	SPI1->DR = spiData;
	while(SPI1-> SR & SPI_SR_TXE_Msk);
	while(SPI1-> SR & SPI_SR_RXNE_Msk);
	return SPI1->DR;

}

#define SX1272_CS_PORT GPIOA
#define SX1272_CS_PIN  6

void SPI1_ResetSS(void){
    SX1272_CS_PORT->ODR &= ~(1U << SX1272_CS_PIN); // CS = 0
}

void SPI1_SetSS(void){
    SX1272_CS_PORT->ODR |= (1U << SX1272_CS_PIN);  // CS = 1
}
