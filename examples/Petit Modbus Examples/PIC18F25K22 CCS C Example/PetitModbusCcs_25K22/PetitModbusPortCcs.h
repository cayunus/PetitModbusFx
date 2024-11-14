/*  PetitModbus Version 1.0
 *  Author  :   Firat DEVECI
 *  Date    :   27.07.16
 *  
 *  Tips    :   If you want to use RS485 you have to use RX-Pull-Up Resistor!
 */
#ifndef __PETITMODBUSPORT__H
#define __PETITMODBUSPORT__H

#include "PetitModbusCcs.h"

#ifndef TRUE
#define TRUE  1
#endif
#ifndef FALSE
#define FALSE 0
#endif

extern volatile unsigned int8    PetitReceiveBuffer[PETITMODBUS_RECEIVE_BUFFER_SIZE];
extern volatile unsigned int8    PetitReceiveCounter;

extern void             PetitModBus_UART_Initialise(void);
extern void             PetitModBus_TIMER_Initialise(void);
extern void             PetitModBus_UART_Putch(unsigned int8 c);
extern unsigned int8    PetitModBus_UART_String(unsigned int8 *s, unsigned int16 Length);

extern void             ReceiveInterrupt(unsigned int8 Data);
extern void             PetitModBus_TimerValues(void);

#endif
