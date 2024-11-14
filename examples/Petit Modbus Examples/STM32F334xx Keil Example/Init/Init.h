#ifndef __INIT_H
#define __INIT_H

#define LEDU_ON						GPIO_WriteBit(GPIOB, GPIO_Pin_6, Bit_SET)
#define LEDU_OFF					GPIO_WriteBit(GPIOB, GPIO_Pin_6, Bit_RESET)
#define LEDR_ON						GPIO_WriteBit(GPIOB, GPIO_Pin_9, Bit_SET)
#define LEDR_OFF					GPIO_WriteBit(GPIOB, GPIO_Pin_9, Bit_RESET)
#define LEDD_ON						GPIO_WriteBit(GPIOB, GPIO_Pin_7, Bit_SET)
#define LEDD_OFF					GPIO_WriteBit(GPIOB, GPIO_Pin_7, Bit_RESET)
#define LEDL_ON						GPIO_WriteBit(GPIOB, GPIO_Pin_8, Bit_SET)
#define LEDL_OFF					GPIO_WriteBit(GPIOB, GPIO_Pin_8, Bit_RESET)

extern void General_GPIO_Init(void);
extern void General_EXTI0_Config(void);
extern void General_Timer_Init(void);
extern void General_USART_Init(void);
extern void General_SPI_Init(void);
extern void General_DAC_Init(void);
extern void General_ADC_Init(void);
extern void General_DMA_Init(void);
extern void General_SPI_Init(void);

#endif
