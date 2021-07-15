#ifndef __TASK01_H
#define __TASK01_H
#include "main.h"

typedef enum
{
	BLANK = 0,
	CAUTION = 1,
	RUNNING = 2,
	WARITING = 3,
}ChRunSt_T;


extern uint16_t g_mA[5];
extern uint16_t g_chst[5];
extern uint16_t g_state;


void Task01Main(void);

#endif /*__TASK01_H*/
