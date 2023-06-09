#include "uart.h"

void USART2_Init(void){
//1.enable clock access to uart2
RCC->APB1ENR  |= 0x20000; 
//2.enable clock access to portA
RCC->AHB1ENR  |= 0x01;
//3.Enable pins for alternate functions, pa2, pa3
GPIOA->MODER &= ~0x00F0;
GPIOA->MODER |= 0x00A0; /*Enable alt. function for PA2, PA3*/ 
//4.Configure type of alternate function

GPIOA->AFR[0] &= ~0xFF00;  // Set type of alternative function to AF7
GPIOA->AFR[0] |= 0x7700;

//Configure uart

USART2->BRR  =  0x0683; /* Manage the baud rate on the development board */
USART2->CR1  =  0x000C; /*Enabled tx rx, 8-bit data*/
USART2->CR2  =  0x000;  /* Resets CR2 */
USART2->CR3  =  0x000;  /* Resets CR3 */
USART2->CR1  |= 0x2000; /* Enable uart at bit 13 */
	
	

}

int USART2_write(int ch){

	while(!(USART2->SR & 0x0080)){}
	USART2->DR = (ch & 0xFF);
	
  return ch;
}

int USART2_read(void){
  while(!(USART2->SR & 0x0020)){}
	return USART2->DR;
}

