#ifndef _UART_H
#define _UART_H

#ifndef _REG52_H
#include "reg52.H"
#endif // !_REG52_H

#ifndef _STRING_H
#include "string.h"
#endif // !_STRING_H

extern void (*UART_Event_RecvdStr)(const unsigned char* str);

/// <summary>
/// ����ͨ�ų�ʼ��
/// <para>ʹ���˶�ʱ��1</para>
/// </summary>
void UART_Init();

/// <summary>
/// ����һ���ֽ�
/// </summary>
/// <param name="dat"></param>
void UART_SendByte(unsigned char dat);

/// <summary>
/// �����ַ���
/// </summary>
/// <param name="str"></param>
void UART_SendString(const unsigned char* str);

#endif
