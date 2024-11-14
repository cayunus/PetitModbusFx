#include "General.h"



void USART_puts(USART_TypeDef* USARTx, volatile char *s)
{
	while(*s)
	{
		while( !(USARTx->SR & 0x00000040) );
		USART_SendData(USARTx, *s);
		*s++;
	}
}
void toggle(void)
{
	static int toggle = 0;
	
	if( toggle == 0 ) 
	{
		toggle = 1;
		//LED0_ON;
		DISCOVERY_GREEN_LED_ON;
	}
	else
	{
		toggle = 0;
		//LED0_OFF;
		DISCOVERY_GREEN_LED_OFF;
	}
}

void toggle_ORANGE(void)
{
	static int toggle = 0;
	
	if( toggle == 0 ) 
	{
		toggle = 1;
		//LED0_ON;
		DISCOVERY_ORANGE_LED_ON;
	}
	else
	{
		toggle = 0;
		//LED0_OFF;
		DISCOVERY_ORANGE_LED_OFF;
	}
}