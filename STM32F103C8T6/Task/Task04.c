/**
  ******************************************************************************
  * File Name          : Task04.c
  * Description        : Code for freeRTOS Task05 Application
  ******************************************************************************
  * @author  kmakise
  * @version V1.0.0
  * @date    2021-2-4
  * @brief   配置参数数据存储更新
	******************************************************************************
  * @attention
  * <h2><center>&copy; Copyright (c) kmakise
  * All rights reserved.
  *
  *
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"
#include "Task04.h"
#include "crc.h"
#include "string.h"
#include "stdlib.h"
#include "stdio.h"
/*Golbal data space ----------------------------------------------------------*/

#define FLASH_START_ADDR 		0x0800F000
#define FLASH_BUFFER_SIZE 	100
uint8_t datatfbuf[FLASH_BUFFER_SIZE];

CfgDataTypedef CfgData;

void ReadBufFromFlash(void)
{
	uint32_t Robot_Num_Flash_Add = FLASH_START_ADDR; 
	
	for(int i = 0;i < FLASH_BUFFER_SIZE/2;i++)
	{
		uint16_t readdata = *(__IO uint16_t*)( Robot_Num_Flash_Add );
		datatfbuf[i * 2 + 1	] = readdata >> 8;
		datatfbuf[i * 2 		] = readdata & 0xFF;
		Robot_Num_Flash_Add+=2;
	}
}

void WriteBufToFlash(void)
{
	uint32_t Robot_Num_Flash_Add = FLASH_START_ADDR; 

	FLASH_EraseInitTypeDef My_Flash;  //声明 FLASH_EraseInitTypeDef 结构体为 My_Flash
	HAL_FLASH_Unlock();               //解锁Flash
			
	My_Flash.TypeErase = FLASH_TYPEERASE_PAGES;  //标明Flash执行页面只做擦除操作
	My_Flash.PageAddress = Robot_Num_Flash_Add;  //声明要擦除的地址
	My_Flash.NbPages = 1;                        //说明要擦除的页数，此参数必须是Min_Data = 1和Max_Data =(最大页数-初始页的值)之间的值
			
	uint32_t PageError = 0;                    //设置PageError,如果出现错误这个变量会被设置为出错的FLASH地址
	HAL_FLASHEx_Erase(&My_Flash, &PageError);  //调用擦除函数擦除
	
	for(int i = 0;i < FLASH_BUFFER_SIZE/2;i++)
	{
		uint16_t Write_Flash_Data = datatfbuf[i * 2 + 1] << 8 | datatfbuf[i * 2];
		 //对Flash进行烧写，FLASH_TYPEPROGRAM_HALFWORD 声明操作的Flash地址的16位
		HAL_FLASH_Program(FLASH_TYPEPROGRAM_HALFWORD,Robot_Num_Flash_Add, Write_Flash_Data);
		Robot_Num_Flash_Add+=2;
	}
	HAL_FLASH_Lock(); //锁住Flash
}


//载入默认参数配置并写入flash
void DefultParam(void)
{
	CfgData.octh[0] = 3000;
	CfgData.octh[1] = 3000;
	CfgData.octh[2] = 3000;
	CfgData.octh[3] = 3000;
	CfgData.octh[4] = 3000;
	CfgData.dt = 3000;
	CfgData.update = 0;
}
void INT16ToCh(void *p,int16_t Int)
{
	char *pch = p;
	pch[0] = Int>>8;
	pch[1] = Int&0xff;
}

//更新配置并保存到flash
void ConfigUpdate(void)
{
	if(CfgData.update != 0)
	{
		//copy to buf
		uint8_t len = sizeof(CfgData);
		memcpy(datatfbuf,&CfgData,sizeof(CfgData));
		uint16_t SendCrc = CalCRC16(datatfbuf,len);
		INT16ToCh(&datatfbuf[len],SendCrc);
		
		//save to flash
		WriteBufToFlash();
		CfgData.update = 0;
	}
}

//从flash加载配置并校验
void LoadParam(void)
{
	ReadBufFromFlash();
	//校验参数
	if((CalCRC16(datatfbuf,sizeof(CfgData)+2)==0))
	{
		memcpy(&CfgData,datatfbuf,sizeof(CfgData));
	}
	else //失败
	{
		DefultParam();
		CfgData.update = 255;
		ConfigUpdate();
	}
}

void Task04Main(void)
{
	LoadParam();
	for(;;)
	{
		ConfigUpdate();
		osDelay(100);
	}
}



