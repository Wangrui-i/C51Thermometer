#include "REG52.H"
#include "intrins.h"
#include "UART.h"
#include "IIC.h"
#include "LCD_1602.h"

//void EventHandler_UART_RecvdStr(unsigned char* str);
//void Handel_UART_Event();
//bit UART_recvingStr();

//char UART_RecvdStr[32];	//���ڽ��յ����ݣ����ݳ���ʱ����������

void EventHandler_UART_RecvdStr(unsigned char* str)
{
	LCD_1602_ShowString(1, 5, str);
}

void main()
{
	char mych[32] = "Hello World!";

	Event_UART_RecvdStr = &EventHandler_UART_RecvdStr;

	UART_Init();
	EA = 1;

	IIC_Init();
	LCD_1602_Init();

	LCD_1602_ShowString(0, 0, mych);

	UART_SendString(mych);

	while (1)
	{
	}
}

///// <summary>
///// ���������ݴ��룬������UART_RecvdStr
///// </summary>
//void Handel_UART_Event()
//{
//	LCD_1602_ShowString(0, 0, UART_RecvdStr);
//}
//
///// <summary>
///// ����ͨ���¼��������ݴ���
///// </summary>
//void UART_Event_Recvd()
//{
//	//�˴���������������
//	UART_recvingStr();
//	_UART_recvdFlag = 1;
//}
//
///// <summary>
///// ����ͨ�ţ������ַ�������
///// </summary>
///// <returns>���ݳ��ȴ��ڵ������鳤��ʱ������1</returns>
//bit UART_recvingStr()
//{
//	char* RecStr = UART_RecvdStr;
//	char num = 0;
//	unsigned char count = 0;
//loop:
//	//todo:��żУ��
//	*RecStr = SBUF;
//	count = 0;
//	RI = 0;
//	if (num < sizeof(UART_RecvdStr) - 1)
//	{
//		num++;
//		RecStr++;
//		while (!RI)
//		{
//			count++;
//
//			//�������ݵȴ��ӳ٣��ȴ�ʱ��̫�ûᵼ��CPU�������ã�̫�̻����"���ݰ����ָ�",Ĭ��count=130
//			if (count > 130)
//			{
//				return 0;
//			}
//		}
//		goto loop;
//	}
//	return 1;
//}
