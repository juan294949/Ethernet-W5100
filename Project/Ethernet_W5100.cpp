#include <stm32f446xx.h>
#include "Ethernet_W5100.h"

/*
	Description : 1).	Initializes the peripherals use to interface with the W5100 
				  2).	Initializes the CLOCK frequencies used for the pheripherals 
						- Fsysclk = 100MHZ
						- Fhclk = 100MHZ
						- FAPB1 = APB2 = 25MHZ 

	Inputs: none 
	Output: none 
*/

void InitializeEthernet(){
	
	HAL_StatusTypeDef status = HAL_OK;
	
	status = InitializeErrorLed();
	
	
	/* Initialize the HSI and drive the SYSCLOCK at 100MHZ frequency */
	
	RCC_OscInitTypeDef Osc_config = {0};
	Osc_config = {.OscillatorType = RCC_OSCILLATORTYPE_HSI,.HSIState = RCC_HSI_ON,.HSICalibrationValue =0x05};
	Osc_config.PLL.PLLM= 8;
	Osc_config.PLL.PLLN = 100;
	Osc_config.PLL.PLLP = 2;
	Osc_config.PLL.PLLState=RCC_PLL_ON;
	Osc_config.PLL.PLLSource = RCC_PLLSOURCE_HSI;
	

	status = HAL_RCC_OscConfig(&Osc_config);
									
	if( status == HAL_ERROR){
		
		HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5,GPIO_PIN_SET);
		
	}
	
		
	RCC_ClkInitTypeDef clk_config = {0};
	
	clk_config = {.ClockType = (RCC_CLOCKTYPE_SYSCLK|RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2),.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK,.AHBCLKDivider=RCC_SYSCLK_DIV1,\
				  .APB1CLKDivider=RCC_CFGR_PPRE1_DIV4,.APB2CLKDivider=RCC_CFGR_PPRE1_DIV4
				 };
	
	status = HAL_RCC_ClockConfig(&clk_config,3);
	
	if( status == HAL_ERROR){
		
		HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5,GPIO_PIN_SET);
		
	}
	
	
}

/* Error LED will be GPIOA pin 5 */ 

HAL_StatusTypeDef InitializeErrorLed(){
	
	HAL_StatusTypeDef status; 
	
	__HAL_RCC_GPIOA_CLK_ENABLE();
	
	GPIO_InitTypeDef gpio_config = {.Pin = GPIO_PIN_5,.Mode = GPIO_MODE_OUTPUT_PP,.Pull= GPIO_NOPULL, .Speed = GPIO_SPEED_FAST,.Alternate = 0x00};
	
	HAL_GPIO_Init(GPIOA,&gpio_config);
	
	return status;
	
}



