#include "General.h"

#define STK_SIZE		128
#define TASK1_PRIO	1
#define TASK2_PRIO	2
#define TASK3_PRIO	3
#define TASK4_PRIO	4

OS_STK	Task1_Stk[STK_SIZE];
OS_STK	Task2_Stk[STK_SIZE];
OS_STK	Task3_Stk[STK_SIZE];
OS_STK	Task4_Stk[STK_SIZE];

void Task_1(void *pdata)
{
	for(;;)
	{
		CoTickDelay(1);
		
		ProcessPetitModbus();
	}
}

void Task_2(void *pdata)
{
	for(;;)
	{
		if(PetitRegisters[6].ActValue == 1)
			LEDU_ON;
		else
			LEDU_OFF;
		
		if(PetitRegisters[7].ActValue == 1)
			LEDD_ON;
		else
			LEDD_OFF;
		
		if(PetitRegisters[8].ActValue == 1)
			LEDR_ON;
		else
			LEDR_OFF;
		
		if(PetitRegisters[9].ActValue == 1)
			LEDL_ON;
		else
			LEDL_OFF;
		
		CoTickDelay(10);
	}
}

void Task_3(void *pdata)
{
	for(;;)
	{
		PetitRegisters[4].ActValue = PetitRegisters[3].ActValue;
		CoTickDelay(250);
		PetitRegisters[2].ActValue = GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0);
	}
}

void Task_4(void *pdata)
{
	for(;;)
	{
		CoTickDelay(1000);
		PetitRegisters[5].ActValue++;
	}
}

int main(void)
{
	General_GPIO_Init();
	
	InitPetitModbus(1);
	
  CoInitOS ();
	CoCreateTask(Task_1,0,TASK1_PRIO,&Task1_Stk[STK_SIZE-1],STK_SIZE);
	CoCreateTask(Task_2,0,TASK2_PRIO,&Task2_Stk[STK_SIZE-1],STK_SIZE);
	CoCreateTask(Task_3,0,TASK3_PRIO,&Task3_Stk[STK_SIZE-1],STK_SIZE); 
	CoCreateTask(Task_4,0,TASK4_PRIO,&Task4_Stk[STK_SIZE-1],STK_SIZE);
	CoStartOS();
}
