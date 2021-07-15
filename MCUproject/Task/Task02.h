#ifndef __TASK02_H
#define __TASK02_H

#include "main.h"

typedef struct
{
	uint8_t buf[256];
	uint8_t cnt;
}ComBufTypedef;

//通信缓冲区
extern ComBufTypedef ComTx;
extern ComBufTypedef ComRx;

//蜂鸣器状态控制
void setBeepState(uint8_t st);


//中断数据接收
void RecToBuf(void);

void Task02Main(void);

#endif /*__TASK02_H*/
