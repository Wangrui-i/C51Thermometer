#ifndef __UART_H
#define __UART_H

/*Define UART parity mode*/
#define NONE_PARITY     0   //None parity
#define ODD_PARITY      1   //Odd parity,��У��
#define EVEN_PARITY     2   //Even parity,żУ��
#define MARK_PARITY     3   //Mark parity,1У��
#define SPACE_PARITY    4   //Space parity,0У��

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

#endif
