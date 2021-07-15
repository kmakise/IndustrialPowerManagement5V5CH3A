#ifndef __DWIN_H
#define __DWIN_H
#include "main.h"

float    dwinChToFloat(void *p);
uint32_t dwinChToInt32(void *p);

//复位显示屏
void Disp_Rst(void);
//设置要显示的图片
void Disp_SetPic(uint8_t pic);
//读取当前显示的图片
int16_t Disp_ReadPic(void);
//写RTC
void Disp_WrRtc(void);
//写16位整数
void Disp_WrInt16(uint16_t addr,uint16_t data);
//写32位整型
void Disp_WrInt32(uint16_t addr,int32_t ldata);
//写浮点数
void Disp_WrFloat(uint16_t addr,float fdata);
//写字符串
void Disp_WrStr(uint16_t addr,char *p);
//色块填充
void Disp_WrBlock(uint16_t addr,uint16_t x0,uint16_t y0,uint16_t w,uint16_t h,uint16_t color);
//蜂鸣器控制
void Disp_BeepContrl(uint16_t ms);
#endif /*__DWIN_H*/
