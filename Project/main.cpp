#include "Ethernet_W5100.h"
#include <stm32f4xx.h>
#include <stdint.h>
#include <string>

/* Some comments */ 

/*	Fsysclk = 100MHZ
*	Fhclk = 100MHZ 
*	FAPB1 = FAPB2 = 25MHZ 
*/ 

#define DELAY_HALF_SEC 500
#define _DEBUG_MODE_ 

#ifdef _DEBUG_MODE_

	#define BAUDRATE9600 (9600)
	uint8_t TX_buffer;
	static void print_string(std::string &string_address);
	static void print_integer(uint32_t data); 
	static void UsartConfigUsb(void);
	std::string string_to_send = "Sending data ";
	uint32_t data = 323232323;
	char buffer_range[30];
#endif

int main(){
	
	HAL_Init();
	
	InitializeEthernet();
	
	#ifdef _DEBUG_MODE_
	
		UsartConfigUsb();
	
	#endif

	while(1){

		HAL_Delay(DELAY_HALF_SEC);
		print_string(string_to_send);
	    sprintf(buffer_range,"%d",data);
	
	}		
}


static void UsartConfigUsb(void){
	
	/* Verify that PORTA clock is enabled */ 
	
	if(!__HAL_RCC_GPIOA_IS_CLK_ENABLED()){

		__HAL_RCC_GPIOA_CLK_ENABLE();
	}
	
	/* Set up the configuration for the alternated function 
	*	PIN2 = TX, PIN3 = RX 
	*/

	GPIO_InitTypeDef gpio_config = {.Pin = (GPIO_PIN_2|GPIO_PIN_3),.Mode = GPIO_MODE_AF_PP,.Pull= GPIO_NOPULL, .Speed = GPIO_SPEED_FREQ_VERY_HIGH,.Alternate = GPIO_AF7_USART2};

	HAL_GPIO_Init(GPIOA,&gpio_config);
	
	if(!__HAL_RCC_USART2_IS_CLK_ENABLED()){
		
		__HAL_RCC_USART2_CLK_ENABLE();
	
	}
	
	/* USART_InitTypeDef*/
	USART_InitTypeDef Usart_basic_configuration ={0};
	
	/* end */
	
	/* USART_HandleTypeDef*/
	
	uint32_t Buff_size = sizeof(TX_buffer)/(sizeof(uint8_t));
	USART_HandleTypeDef Usart_other_configurations ={0};
	
	Usart_other_configurations.Instance = USART2;
	Usart_other_configurations.Init.BaudRate = BAUDRATE9600;
	Usart_other_configurations.pTxBuffPtr = &TX_buffer;
	Usart_other_configurations.TxXferSize = Buff_size;
	Usart_other_configurations.Init.Mode = USART_MODE_TX;
	
	/* end  */
	
    HAL_USART_Init(&Usart_other_configurations);
}

static void print_string( std::string &string_address){

	uint8_t datareg;
	uint32_t Size_of_string = string_address.size();
	uint32_t location =0; 
	for( uint32_t location =0; location < Size_of_string ; location++){
		datareg = string_address.at(location);
		USART2->DR = datareg; 
		while(!((USART2->SR)&(USART_SR_TXE))){}
	}
}

static void print_integer(uint32_t data){
	
	
	
}