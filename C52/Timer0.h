#ifndef _TIMER0_H
#define _TIMER0_H

#include "reg52.h"

extern void (*Timer0_Event_Elapsed)(void);

/// <summary>
/// Timer0��ʼ����Ĭ�ϲ�������ʱ�������ʱ��Ϊ1000ms
/// </summary>
void Timer0_Init();

/// <summary>
/// ���ü��ʱ��(ms)
/// </summary>
/// <param name="interval">���ʱ��</param>
void Timer0_SetInterval(unsigned long interval);

/// <summary>
/// ����
/// </summary>
void Timer0_Start();

/// <summary>
/// ֹͣ
/// </summary>
void Timer0_Stop();

#endif