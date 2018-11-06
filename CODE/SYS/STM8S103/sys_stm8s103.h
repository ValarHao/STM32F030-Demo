#ifndef __SYS_STM8S103_H
#define __SYS_STM8S103_H

/*------------------------------*
*  include head files           *
*-------------------------------*/
#include "sys_stm.h"
#include "stm8s.h"

/*------------------------------*
*  macros for others            *
*-------------------------------*/
#define   SYSCLK   16

#define   BIT_ADDR(addr, bitnum)   (*((volatile BYTE_BITS *)addr)).bit##bitnum

#define   GPIOA_ODR_ADDR   GPIOA_BaseAddress
#define   GPIOB_ODR_ADDR   GPIOB_BaseAddress
#define   GPIOC_ODR_ADDR   GPIOC_BaseAddress
#define   GPIOD_ODR_ADDR   GPIOD_BaseAddress

#define   GPIOA_IDR_ADDR   GPIOA_BaseAddress + 1
#define   GPIOB_IDR_ADDR   GPIOB_BaseAddress + 1
#define   GPIOC_IDR_ADDR   GPIOC_BaseAddress + 1
#define   GPIOD_IDR_ADDR   GPIOD_BaseAddress + 1

#define   PAout(n)   BIT_ADDR(GPIOA_ODR_ADDR, n)
#define   PAin(n)    BIT_ADDR(GPIOA_IDR_ADDR, n)
#define   PBout(n)   BIT_ADDR(GPIOB_ODR_ADDR, n)
#define   PBin(n)    BIT_ADDR(GPIOB_IDR_ADDR, n)
#define   PCout(n)   BIT_ADDR(GPIOC_ODR_ADDR, n)
#define   PCin(n)    BIT_ADDR(GPIOC_IDR_ADDR, n)
#define   PDout(n)   BIT_ADDR(GPIOD_ODR_ADDR, n)
#define   PDin(n)    BIT_ADDR(GPIOD_IDR_ADDR, n)

#define   Hx(val)     *((char *) &val)
#define   xH(val)     *(((char *) &val) + 1)
#define   Hxxx(val)   *((char *) &val)
#define   xHxx(val)   *(((char *) &val) + 1)
#define   xxHx(val)   *(((char *) &val) + 2)
#define   xxxH(val)   *(((char *) &val) + 3)

#define   LOAD_VAL   124   // 1MS

/*------------------------------*
*  macros for functions         *
*-------------------------------*/
#define   EnableInterrupt()    asm("rim")
#define   DisableInterrupt()   asm("sim")
#define   NOP()   asm("nop")

/*------------------------------*
*  type definitions             *
*-------------------------------*/
typedef struct
{
	u8 bit0: 1;
	u8 bit1: 1;
	u8 bit2: 1;
	u8 bit3: 1;
	u8 bit4: 1;
	u8 bit5: 1;
	u8 bit6: 1;
	u8 bit7: 1;
} BYTE_BITS;

/*------------------------------*
*  public functions             *
*-------------------------------*/
extern void SetSoftwarePriority(u8 vector, u8 level);

#endif
