
#include <18F25K22.h>
#device ADC=16

#FUSES NOWDT                    //No Watch Dog Timer
#FUSES WDT128                   //Watch Dog Timer uses 1:128 Postscale
#FUSES NOBROWNOUT               //No brownout reset
#FUSES NOPBADEN                 //PORTB pins are configured as digital I/O on RESET
#FUSES NOLVP                    //No low voltage prgming, B3(PIC16) or B5(PIC18) used for I/O
#FUSES NOXINST                  //Extended set extension and Indexed Addressing mode disabled (Legacy mode)
#FUSES WRT                      //Program Memory Write Protected

#use delay(crystal=20MHz,clock=20MHz)
#use rs232(baud=57600,parity=N,xmit=PIN_C6,rcv=PIN_C7,bits=8)

#byte TXSTA1 = 0x0FAC
#bit  TRMT = TXSTA1.1

#byte PIR1 = 0x0F9E
#bit  TX1IF = PIR1.4
#bit  RC1IF = PIR1.5

#byte TXREG1 = 0x0FAD

/*

PIR1 0x0F9E
bit 4 TX1IF: EUSART1 Transmit Interrupt Flag bit
1 = The EUSART1 transmit buffer, TXREG1, is empty (cleared when TXREG1 is written)
0 = The EUSART1 transmit buffer is full

bit 5 RC1IF: EUSART1 Receive Interrupt Flag bit
1 = The EUSART1 receive buffer, RCREG1, is full (cleared when RCREG1 is read)
0 = The EUSART1 receive buffer is empty


TXSTA1 0x0FAC
bit 1 TRMT: Transmit Shift Register Status bit
1 = TSR empty
0 = TSR full
*/
#define Buton input(PIN_C0)
#define Tx_Rx_Cnt PIN_C5
#define LED0 PIN_C1
#define LED1 PIN_C2
#define LED2 PIN_C3
#define LED3 PIN_C4

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <PetitModbusCcs.h>
#include <PetitModbusCcs.c>
#include <PetitModbusPortCcs.h>
#include <PetitModbusPortCcs.c>
#include <PetitRegConstantCcs.c>

#use fast_io(a)
#use fast_io(b)
#use fast_io(c)


unsigned int16 Tmr1_Deger=64911;
unsigned int16 Timer1_Tick_Counter;


void Set_LED0(int1 x){
   if(x) output_high(LED0); else  output_low(LED0);
}
void Set_LED1(int1 x){
   if(x) output_high(LED1); else  output_low(LED1);
}
void Set_LED2(int1 x){
   if(x) output_high(LED2); else  output_low(LED2);
}
void Set_LED3(int1 x){
   if(x) output_high(LED3); else  output_low(LED3);
}


#INT_TIMER1
void  TIMER1_isr(void) 
{
   Set_Timer1(Tmr1_Deger);
   Timer1_Tick_Counter ++;        
   PetitModBus_TimerValues();
   clear_interrupt(INT_TIMER1);
   

}

#INT_RDA
void  RDA_isr(void) 
{
   ReceiveInterrupt(getch());//RCREG
   RC1IF=0;
   //clear_interrupt(int_rda);
}


void main()
{


   setup_timer_0(RTCC_INTERNAL|RTCC_DIV_1|RTCC_8_bit);        
   setup_timer_1(T1_INTERNAL|T1_DIV_BY_8);     
   Set_Timer1(Tmr1_Deger);
   Setup_Timer_2(T2_Disabled,0,1); 
   Setup_CCP1(CCP_OFF);
   Setup_Comparator(NC_NC_NC_NC); 
   Setup_Adc(ADC_OFF);   
   Setup_Adc_Ports(NO_ANALOGS);   
   
   disable_interrupts(INT_TIMER0);
   disable_interrupts(INT_TIMER1);
   disable_interrupts(INT_RDA);
   disable_interrupts(INT_TBE);
   disable_interrupts(GLOBAL);
   
   set_tris_A(0x00);
   set_tris_B(0x00);
   set_tris_C(0x81);
  
   output_A(0x00);
   output_B(0x00);  
   output_C(0x00);
   
   delay_ms(50);
   
   disable_interrupts(INT_TIMER0);
   enable_interrupts(INT_TIMER1);
   enable_interrupts(INT_RDA);
   enable_interrupts(GLOBAL);

   
   Set_LED0(0);
   Set_LED1(0);
   Set_LED2(0);
   Set_LED3(0);
   InitPetitModbus(1);
   
   while(TRUE)
   {
      
      ProcessPetitModbus();
      
      output_bit(LED0,bit_test(PetitRegisters[0].ActValue,0));
      output_bit(LED1,bit_test(PetitRegisters[0].ActValue,1));
      output_bit(LED2,bit_test(PetitRegisters[0].ActValue,2));
      output_bit(LED3,bit_test(PetitRegisters[0].ActValue,3));      
      
      PetitRegisters[2].ActValue = Buton;
      
      PetitRegisters[4].ActValue=PetitRegisters[3].ActValue;
        
      if(Timer1_Tick_Counter>1000){
         Timer1_Tick_Counter=0;
            
         PetitRegisters[5].ActValue ++;
      }     
      
      //PetitRegisters[10].ActValue = 12345;
      
   }

}
