#include "General.h"                  // Device header



int main(void)
{
	unsigned long DummyCounter;
	
	for(DummyCounter=0;DummyCounter<1000000;DummyCounter++);
	
	General_GPIO_Init();
	

	InitPetitModbus(1);
	Timer_Init();
	while(1) 
	{
		ProcessPetitModbus();	
		
	}
	
	return 0;
}

