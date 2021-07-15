/**
  ******************************************************************************
  * File Name          : Task05.c
  * Description        : Code for freeRTOS Task03 Application
  ******************************************************************************
  * @author  kmakise
  * @version V1.0.0
  * @date    2021-6-2
  * @brief   timer event
	******************************************************************************
  * @attention
  * <h2><center>&copy; Copyright (c) kmakise
  * All rights reserved.
  *
  *
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "cmsis_os.h"
#include "adc.h"
#include "usart.h"
#include "gpio.h"
#include "Task01.h"
#include "Task02.h"
#include "Task03.h"

/* Golbal data space ---------------------------------------------------------*/
uint32_t g_sec = 0;
uint8_t  g_trun = 0;

/* data write/read -----------------------------------------------------------*/
uint32_t getTimeVal(void)
{
	return g_sec;
}

void setTimeVal(uint32_t sec)
{
	g_sec = sec;
}

uint8_t getTimeState(void)
{
	return g_trun;
}

void setTimeState(uint8_t st)
{
	g_trun = st;
}

/* app func ------------------------------------------------------------------*/

void timeRunner(void)
{
	static uint32_t unsec = 0;
	
	unsec++;
	if(unsec > 9)
	{
		unsec = 0;
		if(g_trun != 0)
		{
			if(g_sec > 0)
			{
				g_sec--;
			}
		}
	}
}

void runLEDFlash(void)
{
	static uint16_t div = 0;
	div++;
	
	if(div < 5)
	{
		RUN_LED_GPIO_Port->BSRR = RUN_LED_Pin;
	}
	else if((5 <= div)&&(div <= 10))
	{
		RUN_LED_GPIO_Port->BRR = RUN_LED_Pin;
	}
	else
	{
		div = 0;
	}
}




void Task03Main(void)
{
	osDelay(100);
	for(;;)
	{
		runLEDFlash();
		timeRunner();
		osDelay(100);
	}
}



