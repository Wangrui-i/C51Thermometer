#ifndef _UART_H
#define _UART_H

#ifndef _REG52_H
#include "reg52.h"
#endif // !_REG52_H

#ifndef _STRING_H
#include "string.h"
#endif // !_STRING_H

extern void (*UART_Event_RecvdChar)(const unsigned char ch);	//���¼��ɴ����жϴ������ж������ţ�4
extern void (*UART_Event_RecvdStr)(const unsigned char* str);	//���¼��ɴ����жϴ������ж������ţ�4

/// <summary>
/// ����ͨ�ų�ʼ��
/// <para>ʹ���˶�ʱ��1���������ɴ��ڲ�����</para>
/// </summary>
void UART_Init();

/// <summary>
/// ����һ���ֽ�
/// </summary>
/// <param name="ch"></param>
void UART_SendChar(unsigned char ch);

/// <summary>
/// �����ַ���
/// </summary>
/// <param name="str"></param>
void UART_SendString(const unsigned char* str);

#endif
