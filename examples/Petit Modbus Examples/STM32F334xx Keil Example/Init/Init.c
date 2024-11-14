#include "General.h"

void General_GPIO_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);
	
	// Inputs
	GPIO_InitStructure.GPIO_Mode	= GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_Pin		= GPIO_Pin_0;
	GPIO_InitStructure.GPIO_PuPd	= GPIO_PuPd_NOPULL;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	// Outputs
	GPIO_InitStructure.GPIO_Mode	= GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_Pin		= GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd	= GPIO_PuPd_NOPULL;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOB,&GPIO_InitStructure);
}

void General_Timer_Init(void)
{
	TIM_TimeBaseInitTypeDef TIM_InitStructure;
	NVIC_InitTypeDef 				NVIC_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1ENR_TIM3EN, ENABLE);
	
	TIM_InitStructure.TIM_Period						=36000;
	TIM_InitStructure.TIM_Prescaler					=1;
	TIM_InitStructure.TIM_ClockDivision			=TIM_CKD_DIV1;
	TIM_InitStructure.TIM_RepetitionCounter	=0;
	TIM_InitStructure.TIM_CounterMode 			=TIM_CounterMode_Up;
	NVIC_InitStructure.NVIC_IRQChannel 		  =TIM3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd	  =ENABLE;
	
	TIM_TimeBaseInit(TIM3,&TIM_InitStructure);
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE);
	NVIC_Init(&NVIC_InitStructure);
	TIM_Cmd(TIM3,ENABLE);
}

void General_USART_Init(void)
{
	GPIO_InitTypeDef 	GPIO_InitStructure;
	NVIC_InitTypeDef 	NVIC_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	
  /* Enable GPIO clock */
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);
  
  /* Enable USART2 Clock */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
	
	USART_DeInit(USART2);
	
	/* USART2 Pins configuration ************************************************/
  /* Connect pin to Periph */
  GPIO_PinAFConfig(GPIOB, GPIO_PinSource3, GPIO_AF_7); 
  GPIO_PinAFConfig(GPIOB, GPIO_PinSource4, GPIO_AF_7);    
  
  /* Configure pins as AF pushpull */
  GPIO_InitStructure.GPIO_Pin 									= GPIO_Pin_3 | GPIO_Pin_4;
  GPIO_InitStructure.GPIO_Mode 									= GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed 								= GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_OType 								= GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd 									= GPIO_PuPd_UP;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
	
  /* USART1 IRQ Channel configuration */
  NVIC_InitStructure.NVIC_IRQChannel 						= USART2_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelCmd 				= ENABLE;
  NVIC_Init(&NVIC_InitStructure);
	
	USART_InitStructure.USART_BaudRate 						= 115200;
  USART_InitStructure.USART_WordLength 					= USART_WordLength_8b;
  USART_InitStructure.USART_StopBits 						= USART_StopBits_1;
  USART_InitStructure.USART_Parity 							= USART_Parity_No;
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_InitStructure.USART_Mode 								= USART_Mode_Rx | USART_Mode_Tx;
	
	USART_Init(USART2, &USART_InitStructure);				// Repare uart to receive a data packet
	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);	// Disable USART2 Receive interrupts
	USART_ITConfig(USART2, USART_IT_TXE, DISABLE);	// Disable USART2 Transmit interrupts
	USART_Cmd(USART2, ENABLE);											// Enable the USART2
}

void General_ADC_Init(void)
{

}

void General_DMA_Init(void)
{

}

void General_SPI_Init(void)
{
	GPIO_InitTypeDef		GPIO_InitStructure;
	SPI_InitTypeDef 		SPI_InitStructure;
	
	/* Enable GPIO clock */
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);
	/* DMA1 clock enable */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2 , ENABLE);
	
	/* Connect pin to Periph */
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource13, GPIO_AF_0);		// SCK
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource14, GPIO_AF_0);		// MISO
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource15, GPIO_AF_0);		// MOSI
	
	GPIO_InitStructure.GPIO_Mode	= GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Pin		= GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd	= GPIO_PuPd_NOPULL;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	
	SPI_I2S_DeInit(SPI2);
	
	SPI_InitStructure.SPI_Direction 				= SPI_Direction_2Lines_FullDuplex; 	// Initially Tx
	SPI_InitStructure.SPI_Mode 							= SPI_Mode_Master;
	SPI_InitStructure.SPI_DataSize 					= SPI_DataSize_8b;
	SPI_InitStructure.SPI_CPOL 							= SPI_CPOL_Low; 										// Clock steady low
	SPI_InitStructure.SPI_CPHA 							= SPI_CPHA_1Edge; 									// Data write on rising (second) edge
	SPI_InitStructure.SPI_NSS 							= SPI_NSS_Soft;
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_16;
	SPI_InitStructure.SPI_FirstBit 					= SPI_FirstBit_MSB;
	SPI_InitStructure.SPI_CRCPolynomial 		= 0;
	
	SPI_Init(SPI2, &SPI_InitStructure);
	SPI_Cmd(SPI2, ENABLE);
}
