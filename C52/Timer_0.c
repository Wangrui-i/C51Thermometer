#include "Timer_0.h"

void (*Timer_0_Event_Elapsed)(void);

unsigned long _Timer_0_Counter;
unsigned long _Timer_0_Interval;

/// <summary>
/// Timer0��ʼ����Ĭ�ϲ�������ʱ�������ʱ��Ϊ1000ms
/// </summary>
void Timer_0_Init()
{
	//1ms
	TMOD |= 0x01;
	TH0 = 0xF8;
	TL0 = 0xCD;
	_Timer_0_Counter = 0;
	_Timer_0_Interval = 1000;
}

/// <summary>
/// ���ü��ʱ��
/// </summary>
/// <param name="interval">���ʱ��(ms)</param>
void Timer_0_SetInterval(unsigned long interval)
{
	_Timer_0_Interval = interval;
}

/// <summary>
/// ����
/// </summary>
void Timer_0_Start()
{
	ET0 = 1;
	TR0 = 1;
}

/// <summary>
/// ֹͣ
/// </summary>
void Timer_0_Stop()
{
	ET0 = 0;
	TR0 = 0;
}

void Timer_0_Interrupt() interrupt 1
{
	TH0 = 0xF8;
	TL0 = 0xCD;
	//add your code here!
	_Timer_0_Counter++;
	if (_Timer_0_Counter >= _Timer_0_Interval)
	{
		_Timer_0_Counter = 0;
		(*Timer_0_Event_Elapsed)();
	}
}