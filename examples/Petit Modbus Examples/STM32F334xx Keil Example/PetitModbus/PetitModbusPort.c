#include "General.h"
#include "PetitModbus.h"
#include "PetitModbusPort.h"

unsigned char   PetitReceiveBuffer[PETITMODBUS_RECEIVE_BUFFER_SIZE];
unsigned char   PetitReceiveCounter=0;

unsigned char   U3TxDmaBuf[PETITMODBUS_TRANSMIT_BUFFER_SIZE];                   // DMA Transmit Isleminde Kullanilacaktir!

void PetitModBus_UART_Initialise(void)
{
    General_USART_Init();
}

void PetitModBus_TIMER_Initialise(void)
{
    General_Timer_Init();
}

void PetitModBus_UART_Putch(unsigned char c)
{
	//Wait for the uart to finish sending the byte.
	while(USART_GetFlagStatus(USART2, USART_FLAG_TXE) == RESET);
	
	USART_SendData(USART2,c);
}

unsigned char PetitModBus_UART_String(unsigned char *s, unsigned int Length)
{

    while(Length)
    {
        PetitModBus_UART_Putch(*s++);
        Length--;
    }
    return TRUE;
}

/***************************Interrupt For Slave********************************/

void USART2_IRQHandler(void)
{
	if(USART_GetITStatus(USART2,USART_IT_RXNE)==SET)
	{
		USART_ClearFlag(USART2, USART_IT_RXNE);
		
		PetitReceiveBuffer[PetitReceiveCounter]   =USART_ReceiveData(USART2);
    PetitReceiveCounter++;

    if(PetitReceiveCounter>PETITMODBUS_RECEIVE_BUFFER_SIZE)  
        PetitReceiveCounter=0;

    PetitModbusTimerValue=0;
	}
}

/******************************************************************************/
void PetitModBus_TimerValues(void)
{
    PetitModbusTimerValue++;
}

void TIM3_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM3,TIM_IT_Update)==SET)
	{
		TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
		
		PetitModBus_TimerValues();
	}
}
