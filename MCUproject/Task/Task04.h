#ifndef __TASK04_H
#define __TASK04_H

#include "stm32f1xx_hal.h"

typedef struct
{
	uint16_t octh[5];
	uint32_t dt;
	uint16_t update;
	
}CfgDataTypedef;

extern CfgDataTypedef CfgData;

void Task04Main(void);

#endif /*__TASK05_H*/

