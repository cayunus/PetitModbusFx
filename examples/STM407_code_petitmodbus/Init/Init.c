#include "General.h"
#include "stm32f4xx_usart.h"
#define ADC1_DR_Address    	0x40012440

void General_GPIO_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);

  /* Configure PD0 and PD2 in output pushpull mode */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13;				//**EYE_READ**/**ENCODER_A_B**/**LED**
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT; // GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_Init(GPIOD, &GPIO_InitStructure);

  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);

  /* Configure PD0 and PD2 in output pushpull mode */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15 | GPIO_Pin_14 | GPIO_Pin_13;				//**EYE_READ**/**ENCODER_A_B**/**LED**
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT; // GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOC, &GPIO_InitStructure);
	
		
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);

  /* Configure PD0 and PD2 in output pushpull mode */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;						//**ENCODER_A_LATCH**/**ENCODER_B_LATCH**/**EYE_LATCH**
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT; //GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOB, &GPIO_InitStructure);

}


void General_Timer_Init(void)			
{
	TIM_TimeBaseInitTypeDef TIM_InitStructure;
	NVIC_InitTypeDef 				NVIC_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1ENR_TIM3EN, ENABLE);

	TIM_InitStructure.TIM_Prescaler							=1;
	TIM_InitStructure.TIM_Period								=41999;			//1 ms 
	TIM_InitStructure.TIM_ClockDivision					=TIM_CKD_DIV1;
	TIM_InitStructure.TIM_RepetitionCounter			=0;
	TIM_InitStructure.TIM_CounterMode 					=TIM_CounterMode_Up;
	NVIC_InitStructure.NVIC_IRQChannel 		  		=TIM3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd	  		=ENABLE;
	
	TIM_TimeBaseInit(TIM3,&TIM_InitStructure);
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE);
	NVIC_Init(&NVIC_InitStructure);
	TIM_Cmd(TIM3,ENABLE);
	
}


//void InitUart1(void)
//{
//	GPIO_InitTypeDef 	GPIO_InitStructure;
//	NVIC_InitTypeDef 	NVIC_InitStructure;
//	USART_InitTypeDef USART_InitStructure;	
//	USART_ClockInitTypeDef USART_ClockInitStructure;
//	
//  /* Enable GPIO clock */
//  //RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
//  
//  /* Enable USART2 Clock */
//  //RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 | RCC_AHB1Periph_GPIOA, ENABLE);
//	
//	USART_DeInit(USART1);
//		
//	
//  GPIO_InitStructure.GPIO_Pin 									= GPIO_Pin_9;
//	GPIO_InitStructure.GPIO_Mode 									= GPIO_Mode_AF;
//	GPIO_InitStructure.GPIO_OType 								= GPIO_OType_PP;
//	GPIO_InitStructure.GPIO_PuPd 									= GPIO_PuPd_NOPULL;
//	GPIO_InitStructure.GPIO_Speed 								= GPIO_Speed_50MHz;
//  GPIO_Init(GPIOA, &GPIO_InitStructure);
//	
//  GPIO_InitStructure.GPIO_Pin 									= GPIO_Pin_10;
//  GPIO_InitStructure.GPIO_Mode 									= GPIO_AF_USART1;
//  GPIO_InitStructure.GPIO_Speed 								= GPIO_Speed_50MHz;
//  GPIO_Init(GPIOA, &GPIO_InitStructure);

//		
//		
//  /* USART1 IRQ Channel configuration */
//  NVIC_InitStructure.NVIC_IRQChannel 						= USART1_IRQn;
//  NVIC_InitStructure.NVIC_IRQChannelCmd 				= ENABLE;
//  NVIC_Init(&NVIC_InitStructure);
//	
//	USART_InitStructure.USART_BaudRate 						= 115200;
//  USART_InitStructure.USART_WordLength 					= USART_WordLength_8b;
//  USART_InitStructure.USART_StopBits 						= USART_StopBits_1;
//  USART_InitStructure.USART_Parity 							= USART_Parity_No;
//  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
//  USART_InitStructure.USART_Mode 								= USART_Mode_Rx | USART_Mode_Tx;
//	
//	USART_ClockInitStructure.USART_Clock = USART_Clock_Disable;
//	USART_ClockInitStructure.USART_CPOL = USART_CPOL_Low;
//	USART_ClockInitStructure.USART_CPHA = USART_CPHA_2Edge;
//	USART_ClockInitStructure.USART_LastBit = USART_LastBit_Disable;
//	
//	USART_Init(USART1, &USART_InitStructure);
//	USART_ClockInit(USART1, &USART_ClockInitStructure);
//	
//	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);	// Disable USART1 Receive interrupts
//	USART_ITConfig(USART1, USART_IT_TXE, DISABLE);	// Disable USART1 Transmit interrupts
//	USART_Cmd(USART1, ENABLE);											// Enable the USART1
//	
//  /* Enable DMA1 clock -------------------------------------------------------*/
//  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
//}

void Init_USART1(uint32_t baudrate)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
	 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	 
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource6, GPIO_AF_USART1);
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource7, GPIO_AF_USART1);
	 
	USART_InitStructure.USART_BaudRate = baudrate;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
	USART_Init(USART1, &USART_InitStructure);
	 
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
	 
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	 
	USART_Cmd(USART1, ENABLE);
}


void General_USART_Init(void)
{
	GPIO_InitTypeDef 	GPIO_InitStructure;
	NVIC_InitTypeDef 	NVIC_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	
	//GPIO_PinRemapConfig(GPIO_PartialRemap_USART3, ENABLE);
	
  /* Enable USART3 Clock */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART6, ENABLE);
	
  /* Enable GPIO clock */
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
  
	
	//USART_DeInit(USART6);
	
	/**USART3 GPIO Configuration    
	PB10     ------> USART3_TX
	PB11     ------> USART3_RX  */
	
	/* USART2 Pins configuration ************************************************/
  /* Connect pin to Periph */	

	
  GPIO_InitStructure.GPIO_Pin 									= GPIO_Pin_6 | GPIO_Pin_7;
  GPIO_InitStructure.GPIO_Mode 									= GPIO_Mode_AF;//  GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_OType 								= GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd 									= GPIO_PuPd_UP;
  GPIO_InitStructure.GPIO_Speed 								= GPIO_Speed_50MHz;
  GPIO_Init(GPIOC, &GPIO_InitStructure);
	
		
	/* Connect USART pins to AF */
	GPIO_PinAFConfig(GPIOC, GPIO_PinSource6, GPIO_AF_USART6);
	GPIO_PinAFConfig(GPIOC, GPIO_PinSource7, GPIO_AF_USART6);
		
  /* USART3 IRQ Channel configuration */
  NVIC_InitStructure.NVIC_IRQChannel 						= USART6_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelCmd 				= ENABLE;
  NVIC_Init(&NVIC_InitStructure);
	
	USART_InitStructure.USART_BaudRate 						= 115200;
  USART_InitStructure.USART_WordLength 					= USART_WordLength_8b;
  USART_InitStructure.USART_StopBits 						= USART_StopBits_1;
  USART_InitStructure.USART_Parity 							= USART_Parity_No;
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_InitStructure.USART_Mode 								= USART_Mode_Rx | USART_Mode_Tx;
	
	USART_Init(USART6, &USART_InitStructure);				// Repare uart to receive a data packet
	USART_ITConfig(USART6, USART_IT_RXNE, ENABLE);	// Disable USART2 Receive interrupts
	USART_ITConfig(USART6, USART_IT_TXE, DISABLE);	// Disable USART2 Transmit interrupts
	USART_Cmd(USART6, ENABLE);											// Enable the USART2
	
  /* Enable DMA1 clock -------------------------------------------------------*/
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA1, ENABLE);

}


void Watchdog_Init(void)
{
	/* IWDG timeout equal to 250 ms (the timeout may varies due to LSI frequency
     dispersion) */
  /* Enable write access to IWDG_PR and IWDG_RLR registers */
  IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);

  /* IWDG counter clock: LSI/32 */
  IWDG_SetPrescaler(IWDG_Prescaler_32);

  /* Set counter reload value to obtain 1000ms IWDG TimeOut.
     Counter Reload Value = 1000ms/IWDG counter clock period
                          = 1000ms / (LSI/32)
                          = 1s / (LsiFreq/32)
                          = LsiFreq/(32)
                          = LsiFreq/32
   */
  IWDG_SetReload(40000/32);

  /* Reload IWDG counter */
  IWDG_ReloadCounter();

  /* Enable IWDG (the LSI oscillator will be enabled by hardware) */
  IWDG_Enable();
}

//-------------------------------------------------------------------------------------//
/*
	TIM_InitStructure.TIM_Period								=36000;				//1ms 
	TIM_InitStructure.TIM_Prescaler							=1;
	TIM_InitStructure.TIM_ClockDivision					=TIM_CKD_DIV1;
*/
void Timer_Init(void)			//5 us
{
	TIM_TimeBaseInitTypeDef TIM_InitStructure;
	NVIC_InitTypeDef 				NVIC_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1ENR_TIM2EN, ENABLE);
	
	TIM_InitStructure.TIM_Period								=596;		//360 idi 
	TIM_InitStructure.TIM_Prescaler							=0;
	TIM_InitStructure.TIM_ClockDivision					=TIM_CKD_DIV1;
	TIM_InitStructure.TIM_RepetitionCounter			=0;
	TIM_InitStructure.TIM_CounterMode 					=TIM_CounterMode_Up;
	NVIC_InitStructure.NVIC_IRQChannel 		  		=TIM2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd	  		=ENABLE;
	
	TIM_TimeBaseInit(TIM2,&TIM_InitStructure);
	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);
	NVIC_Init(&NVIC_InitStructure);
	TIM_Cmd(TIM2,ENABLE);
}


/*
void Timer_Init_EyeRead(void)			
{
	TIM_TimeBaseInitTypeDef TIM_InitStructure;
	NVIC_InitTypeDef 				NVIC_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1ENR_TIM3EN, ENABLE);
	
	TIM_InitStructure.TIM_Period								=900;			//25 us * 2 => 50us - 20Khz 
	TIM_InitStructure.TIM_Prescaler							=1;
	TIM_InitStructure.TIM_ClockDivision					=TIM_CKD_DIV1;
	TIM_InitStructure.TIM_RepetitionCounter			=0;
	TIM_InitStructure.TIM_CounterMode 					=TIM_CounterMode_Up;
	NVIC_InitStructure.NVIC_IRQChannel 		  		=TIM3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd	  		=ENABLE;
	
	TIM_TimeBaseInit(TIM3,&TIM_InitStructure);
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE);
	NVIC_Init(&NVIC_InitStructure);
	TIM_Cmd(TIM3,ENABLE);
}
*/




