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
/// <param name="_data"></param>
void UART_SendData(unsigned char _data);

/// <summary>
/// �����ַ���
/// </summary>
/// <param name="_str"></param>
void UART_SendString(char* _str);

extern void (*Event_UART_RecvdStr)(unsigned char* str);

#endif
