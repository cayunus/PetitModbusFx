#ifndef __INIT_H
#define __INIT_H

#define VERSION_NUMBER		1001

#define def10ms						10
#define def20ms						20
#define def30ms						20

#define defSOH						0x55
#define defEOT						0xAA
#define defPhotoWrite			0xA0
#define defDataWrite			0x15
	
#define LED0_ON													GPIO_WriteBit(GPIOC, GPIO_Pin_13, Bit_SET)
#define LED0_OFF												GPIO_WriteBit(GPIOC, GPIO_Pin_13, Bit_RESET)
#define LED0_TOGGLE											GPIO_WriteBit(GPIOC, GPIO_Pin_13, Bit_SET ^ 1)

#define DISCOVERY_GREEN_LED_ON					GPIO_WriteBit(GPIOD, GPIO_Pin_12, Bit_SET)
#define DISCOVERY_GREEN_LED_OFF					GPIO_WriteBit(GPIOD, GPIO_Pin_12, Bit_RESET)

#define DISCOVERY_ORANGE_LED_ON					GPIO_WriteBit(GPIOD, GPIO_Pin_13, Bit_SET)
#define DISCOVERY_ORANGE_LED_OFF				GPIO_WriteBit(GPIOD, GPIO_Pin_13, Bit_RESET)

#define CLK_ENCODER_A_B_ON							GPIO_WriteBit(GPIOC, GPIO_Pin_14, Bit_SET)
#define CLK_ENCODER_A_B_OFF							GPIO_WriteBit(GPIOC, GPIO_Pin_14, Bit_RESET)

#define LATCH_ENCODER_A_B_ON						GPIO_WriteBit(GPIOB, GPIO_Pin_14, Bit_SET)
#define LATCH_ENCODER_A_B_OFF						GPIO_WriteBit(GPIOB, GPIO_Pin_14, Bit_RESET)


#define CLK_EYEREAD_ON									GPIO_WriteBit(GPIOC, GPIO_Pin_15, Bit_SET)
#define CLK_EYEREAD_OFF									GPIO_WriteBit(GPIOC, GPIO_Pin_15, Bit_RESET)

#define LATCH_EYEREAD_ON								GPIO_WriteBit(GPIOB, GPIO_Pin_15, Bit_SET)
#define LATCH_EYEREAD_OFF								GPIO_WriteBit(GPIOB, GPIO_Pin_15, Bit_RESET)



#define PROBE_ON												GPIO_WriteBit(GPIOB, GPIO_Pin_13, Bit_SET)
#define PROBE_OFF												GPIO_WriteBit(GPIOB, GPIO_Pin_13, Bit_RESET)

#define ENCODERA_INPUT									GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0)

#define TimerTick												5
#define LatchWidth											( 80 / TimerTick )
#define LatchToClkWidth									( 10 / TimerTick )		
#define EncoderBitCount									19
#define FlowStartWait										( 100 / TimerTick )

#define EyeLatchWidth										( 80 / TimerTick )
#define EyeLatchToClkWidth							( 10 / TimerTick )	
#define EyeEncoderBitCount							199 
#define EyeFlowStartWait								( 100 / TimerTick )

#define Clk25KHz												2
#define Clk20KHz												3


#define FLOW_STARTING										1
#define FLOW_FIRST_LATCH								2
#define FLOW_LATCH_CLK_WAIT							3
#define FLOW_CLK												4
#define FLOW_SECOND_LATCH								5
#define FLOW_CLK_LATCH_WAIT							6


extern void Init_USART1(uint32_t baudrate);
extern void General_GPIO_Init(void);
extern void General_Timer_Init(void);
extern void General_USART_Init(void);
extern void General_ADC_Init(void);
extern void General_DMA_Init(void);
extern void InitUart1(void);
extern void InitUart4(void);
extern void Watchdog_Init(void);


extern void General_RTC_Init(void);
extern void InitSPI(void);

extern void Timer_Init(void);
extern void EXTI9_5_Config_EyeRead(void);
extern void EXTI0_Config_EncoderA(void);	
extern void EXTI1_Config_EncoderB(void);
#endif
