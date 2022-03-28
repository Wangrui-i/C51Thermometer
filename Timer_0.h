#ifndef _TIMER_0_H
#define _TIMER_0_H
#endif // !_TIMER_0_H

#ifndef _REG52_H
#include "reg52.h"
#endif // !_REG52_H

extern void (*Timer_0_Event_Elapsed)(void);

/// <summary>
/// Timer0��ʼ����Ĭ�ϲ�������ʱ�������ʱ��Ϊ1000ms
/// </summary>
void Timer_0_Init();

/// <summary>
/// ���ü��ʱ��(ms)
/// </summary>
/// <param name="interval">���ʱ��</param>
void Timer_0_SetInterval(unsigned long interval);

/// <summary>
/// ����
/// </summary>
void Timer_0_Start();

/// <summary>
/// ֹͣ
/// </summary>
void Timer_0_Stop();
