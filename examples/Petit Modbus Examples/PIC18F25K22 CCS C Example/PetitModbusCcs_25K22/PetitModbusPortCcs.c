

#include "PetitModbusCcs.h"
#include "PetitModbusPortCcs.h"

// Modbus RTU Variables
volatile unsigned int8   PetitReceiveBuffer[PETITMODBUS_RECEIVE_BUFFER_SIZE];   // Buffer to collect data from hardware
volatile unsigned int8   PetitReceiveCounter=0;                                 // Collected data number



// UART Initialize for Microconrollers, yes you can use another phsycal layer!
void PetitModBus_UART_Initialise(void)
{
    //InitUART();
}

// Timer Initialize for Petit Modbus, 1ms Timer will be good for us!
void PetitModBus_TIMER_Initialise(void)
{
    //InitTMR1();
}

// This is used for send one character
void PetitModBus_UART_Putch(unsigned int8 c)
{
   while(!TRMT);
   TXREG1 = c;
   //putc(c);
}

// This is used for send string, better to use DMA for it ;)
unsigned int8 PetitModBus_UART_String(unsigned int8 *s, unsigned int16 Length)
{
    unsigned int16  DummyCounter;    
	
    for(DummyCounter=0;DummyCounter<Length;DummyCounter++){
        PetitModBus_UART_Putch(s[DummyCounter]);
    }    
    
    return TRUE;
}

/*************************Interrupt Fonction Slave*****************************/
// Call this function into your UART Interrupt. Collect data from it!
// Better to use DMA
void ReceiveInterrupt(unsigned int8 Data)
{
    PetitReceiveBuffer[PetitReceiveCounter]   =Data;
    PetitReceiveCounter++;

    if(PetitReceiveCounter>PETITMODBUS_RECEIVE_BUFFER_SIZE)  
        PetitReceiveCounter=0;

    PetitModbusTimerValue=0;
}

// Call this function into 1ms Interrupt or Event!
void PetitModBus_TimerValues(void)
{
    PetitModbusTimerValue++;
}
/******************************************************************************/
