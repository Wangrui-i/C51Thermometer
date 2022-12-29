#ifndef _UART_H
#define _UART_H

#include "reg52.H"
#include "string.h"

//extern void (*UART_Event_RecvdChar)(const unsigned char ch);
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
