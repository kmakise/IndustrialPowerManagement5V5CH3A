/**
  ******************************************************************************
  * File Name          : Task02.c
  * Description        : Code for freeRTOS Task02 Application
  ******************************************************************************
  * @author  kmakise
  * @version V1.0.0
  * @date    2021-6-2
  * @brief   GUI Dwin Communication
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
#include "Dwin.h"
#include "Task01.h"
#include "Task02.h"
#include "Task03.h"
#include "Task04.h"

//蜂鸣器
uint8_t st_beep = 0;

//通信缓冲区
ComBufTypedef ComTx;
ComBufTypedef ComRx;

void setBeepState(uint8_t st)
{
	st_beep = st;
}


void beepCtrl(void)
{
	//Disp_BeepContrl(uint8_t ms);
	switch(st_beep)
	{
		case 1://normal
		{
			Disp_BeepContrl(300);
			st_beep = 0;
			break;
		}
		case 2://reset
		{
			Disp_BeepContrl(100);
			st_beep = 0;
			break;
		}
		case 3:// warning
		{
			Disp_BeepContrl(50);
			osDelay(100);
			Disp_BeepContrl(50);
			osDelay(100);
			st_beep = 0;
			break;
		}
		default:break;
	}
}

//中断数据接收
void RecToBuf(void)
{
	if(USART1->SR&(1<<5)) 
	{
		ComRx.buf[ComRx.cnt++] = (USART1->DR&(uint8_t)0x00FF);
		//应答消息清除
		if( (ComRx.cnt > 4) && 
				(ComRx.buf[ComRx.cnt - 1] == 0x4b) && 
				(ComRx.buf[ComRx.cnt - 2] == 0x4f) && 
				(ComRx.buf[ComRx.cnt - 4] == 0x03) &&
				(ComRx.buf[ComRx.cnt - 5] == 0xA5) &&
				(ComRx.buf[ComRx.cnt - 6] == 0x5A) )
		{
			ComRx.cnt -= 6;
		}	
	}
}

//推送配置数据
void putCfgDataScreen(void)
{
	Disp_WrInt16(0x1000,g_mA[0]);//V1 Current
	Disp_WrInt16(0x1002,g_mA[1]);//V2 Current
	Disp_WrInt16(0x1004,g_mA[2]);//V3 Current
	Disp_WrInt16(0x1006,g_mA[3]);//V4 Current
	Disp_WrInt16(0x1008,g_mA[4]);//V5 Current
	
	Disp_WrInt16(0x1010,g_chst[0]);//V1 state
	Disp_WrInt16(0x1012,g_chst[1]);//V2 state
	Disp_WrInt16(0x1014,g_chst[2]);//V3 state
	Disp_WrInt16(0x1016,g_chst[3]);//V4 state
	Disp_WrInt16(0x1018,g_chst[4]);//V5 state
	
	Disp_WrInt16(0x1120,getTimeVal() / 3600   );//time val hour
	Disp_WrInt16(0x1122,getTimeVal() / 60 % 60);//time val min
	Disp_WrInt16(0x1124,getTimeVal() % 60     );//time val sec
	
	Disp_WrInt16(0x1022,CfgData.octh[0]);//V1 threshold
	Disp_WrInt16(0x1024,CfgData.octh[1]);//V1 threshold
	Disp_WrInt16(0x1026,CfgData.octh[2]);//V1 threshold
	Disp_WrInt16(0x1028,CfgData.octh[3]);//V1 threshold
	Disp_WrInt16(0x1030,CfgData.octh[4]);//V1 threshold
	
	Disp_WrInt16(0x1100,CfgData.dt % 60     );//cfg sec
	Disp_WrInt16(0x1102,CfgData.dt / 60 % 60);//cfg min
	Disp_WrInt16(0x1104,CfgData.dt / 3600   );//cfg hour
}

//返回数据处理
uint8_t RxDataAnalyze(uint8_t * data)
{
	//	UsConfigSet(0x002B,0x0008);
	// 	5A A5 06 83 11 00 01 00 78 
	if(data[0] == 0x83)
	{
		uint16_t addr 				= (data[1] << 8)|data[2];
		uint16_t dataInt16 		= (data[4] << 8)|data[5];
		int32_t  dataInt32		= dwinChToInt32(&data[4]);
		float 	 dataFloat 		= dwinChToInt32(&data[4]);
		switch(addr)
		{
			case 0x1022:CfgData.octh[0] = dataInt16;CfgData.update = 1;break;
			case 0x1024:CfgData.octh[1] = dataInt16;CfgData.update = 1;break;
			case 0x1026:CfgData.octh[2] = dataInt16;CfgData.update = 1;break;
			case 0x1028:CfgData.octh[3] = dataInt16;CfgData.update = 1;break;
			case 0x1030:CfgData.octh[4] = dataInt16;CfgData.update = 1;break;
			
			case 0x1100:
			{
				CfgData.dt = (CfgData.dt / 60 * 60) + dataInt16;
				CfgData.update = 1;
				break;
			}
			case 0x1102:
			{
				CfgData.dt = (CfgData.dt / 3600 * 3600) + (CfgData.dt % 60) + dataInt16 * 60;
				CfgData.update = 1;
				break;
			}
			case 0x1104:
			{
				CfgData.dt = (CfgData.dt % 3600) + dataInt16 * 3600;
				CfgData.update = 1;
				break;
			}
		}
		return 1;
	}
	return 0;
}

//数据返回检查
int8_t getBackCheck(void)
{
	static int16_t numhist = 0;
	
	if(ComRx.cnt != 0)
	{
		if(numhist != ComRx.cnt)
		{
			numhist = ComRx.cnt;
		}
		else if(numhist == ComRx.cnt)
		{
			if(numhist > 7)
			{
				if( (ComRx.buf[0] == 0x5A)&&
						(ComRx.buf[1] == 0xA5)&&
						((ComRx.buf[2] == 0x06)||(ComRx.buf[2] == 0x08))
					)
				{
					RxDataAnalyze(&ComRx.buf[3]);
					numhist = 0;
					ComRx.cnt = 0;
					return 1;
				}
			}
			numhist = 0;
			ComRx.cnt = 0;
		}
	}
	return 0;
}

void Task02Main(void)
{
	osDelay(1000);
	__HAL_UART_ENABLE_IT(&huart1,UART_IT_RXNE);
	ComRx.cnt = 0;
	for(;;)
	{
		getBackCheck();
		putCfgDataScreen();
		beepCtrl();
		osDelay(100);
	}
}



