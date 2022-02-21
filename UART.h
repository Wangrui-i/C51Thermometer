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
/// <param name="data"></param>
void UART_SendData(unsigned char _data);

/// <summary>
/// �����ַ���
/// </summary>
/// <param name="str"></param>
void UART_SendString(char* str);

extern void (*Event_UART_RecvdStr)(unsigned char* str);

#endif
