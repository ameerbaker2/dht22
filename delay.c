#include "delay.h"
#include "stm32f10x.h"

// For store tick counts in us
static __IO uint32_t usTicks;

// SysTick_Handler function will be called every 1 us
void systick_init(void)
{
    while (SysTick_Config(SystemCoreClock / 1000000) == 1);
}
void SysTick_Handler()
{
	if (usTicks != 0)
	{
		usTicks--;
	}
}

void DelayInit()
{
	// Update SystemCoreClock value
	SystemCoreClockUpdate();
	// Configure the SysTick timer to overflow every 1 us
	SysTick_Config((SystemCoreClock / (uint32_t)(120000)));
}

void DelayUs(uint32_t us)
{
	// Reload us value
	usTicks = us;
	// Wait until usTick reach zero
	while (usTicks);
}

void DelayMs(uint32_t ms)
{
	// Wait until ms reach zero
	while (ms--)
	{
		// Delay 1ms
		DelayUs(1000);
	}
}
