/****************************************************
* Microcontroller: STM32F103
* Revision: 1.0
* Description: System interface
* Author: ValarHao
*****************************************************
* Note:
* 2018.09.17 V1.0
****************************************************/
#include "sys_stm32f103.h"

Task *ptask;

static void InitSysTick(void);
static void DelayUs(unsigned short nus);
static void DelayMs(unsigned long nms);

Sys sys = { 0, InitSysTick, DelayUs, DelayMs };

static void InitSysTick(void)
{
	SysTick->CTRL &= SysTick_CLKSource_HCLK_Div8;   // External divider 8
	SysTick->LOAD  = LOAD_VAL;
	SysTick->VAL   = 0x000000;   // Clear counter
	SysTick->CTRL |= SysTick_CTRL_TICKINT_Msk;   // Enable SYSTICK interrupt
	SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;   // Enable SYSTICK

	sys.tick = 0;
}

static void DelayUs(unsigned short nus)
{
	u32 lastVal, nusVal, nowVal, usCnt = 0;

	nusVal = (u32) nus * TICK_1US;

  #ifndef UCOSII
	//DisableInterrupt();
  #else
	if (OSRunning == TRUE)
		OSSchedLock();
  #endif

	lastVal = SysTick->VAL;

	while (TRUE)
	{
		nowVal = SysTick->VAL;

		if (nowVal != lastVal)
		{
			if (nowVal < lastVal)
				usCnt += lastVal - nowVal;
			else
				usCnt += LOAD_VAL - nowVal + lastVal;

			lastVal = nowVal;

			if (usCnt >= nusVal)
				break;
		}
	}

  #ifndef UCOSII
	//EnableInterrupt();
  #else
	if (OSRunning == TRUE)
		OSSchedUnlock();
  #endif
}

static void DelayMs(unsigned long nms)
{
	u32 t;

  #ifdef UCOSII
	if (OSRunning == TRUE)
	{
		t = nms / (1000 / OS_TICKS_PER_SEC);

		if (t != 0)
			OSTimeDly(t);

		t = nms % (1000 / OS_TICKS_PER_SEC);

		if (t != 0)
			DelayUs(t * 1000);
	}
	else
	{
		for (t=0; t<nms; t++)
			DelayUs(1000);
	}
  #else
	for (t=0; t<nms; t++)
		DelayUs(1000);
  #endif
}

void SysTick_Handler(void)
{
  #ifndef UCOSII
	sys.tick++;
  #else
	if (OSRunning == TRUE)
	{
		OSIntEnter();
		OSTimeTick();
		OSIntExit();
	}
  #endif
}
