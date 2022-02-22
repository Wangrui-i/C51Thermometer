#ifndef __UART_H
#define __UART_H

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
void UART_SendString(const char* str);

extern void (*Event_UART_RecvdStr)(const unsigned char* str);

#endif
