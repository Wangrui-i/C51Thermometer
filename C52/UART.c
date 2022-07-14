#include "UART.h"

void (*UART_Event_RecvdStr)(const unsigned char* str);

/// <summary>
/// ����ͨ�ų�ʼ�� �����ʣ�115200
/// <para>ʹ���˶�ʱ��1</para>
/// </summary>
void UART_Init()
{
	TMOD = 0x20;
	SCON = 0x50;
	TH1 = 0xFF;
	TL1 = TH1;
	PCON = 0x80;
	//EA = 1;
	ES = 1;
	TR1 = 1;
}

/// <summary>
/// ����һ���ֽ�
/// </summary>
/// <param name="dat"></param>
void UART_SendByte(unsigned char dat)
{
	SBUF = dat;             //Send data to UART buffer
	while (!TI);
	TI = 0;
}

/// <summary>
/// �����ַ���
/// </summary>
/// <param name="str"></param>
void UART_SendString(const unsigned char* str)
{
	unsigned char i;
	for (i = 0; i < strlen(str); i++)
	{
		UART_SendByte(str[i]);
	}
}

/// <summary>
/// �����ַ���
/// </summary>
/// <returns></returns>
const unsigned char* recvingStr()
{
	unsigned char recvdStr[64];
	unsigned char i = 0;
	unsigned char count = 0;
loop:
	recvdStr[i] = SBUF;
	count = 0;
	RI = 0;
	if (i < sizeof(recvdStr) - 1)
	{
		i++;
		while (!RI)
		{
			count++;
			//�������ݵȴ��ӳ٣��ȴ�ʱ��̫�ûᵼ��CPU�������ã�̫�̻����"���ݰ����ָ�", Ĭ��count = 130
			if (count > 130)
			{
				recvdStr[i] = '\0';
				return recvdStr;
			}
		}
		goto loop;
	}
	return recvdStr;
}

/// <summary>
/// �����жϷ���
/// </summary>
void UART_ISR() interrupt 4
{
	if (RI)
	{
		//�����ַ��������¼�
		(*UART_Event_RecvdStr)(recvingStr());
	}
}
