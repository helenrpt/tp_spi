#include <stdint.h>
#include <stm32f446xx.h>
#include <stdio.h>
#include "main.h"
#include "gpio.h"
#include "usart.h"
#include "timer.h"
#include "util.h"
#include "bus_spi.h"


uint8_t rx;

int main(void)
{
	FPU_Init();
	GPIO_Init();
	USART2_Init();
	SYSTICK_Init();
	SPI1_Init();

	while(1){
		SYSTICK_Delay(2000);

		SPI1_SetSS();
		SPI1_ResetSS();

		rx = SPI1_TransmiReceive(0xA5);

		SPI1_SetSS();

		printf("%02X \r\n", rx);
	}
}
