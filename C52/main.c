#include "main.h"

char temp_ch[32];	//��ʱ�洢Ҫ��ʾ���ַ���
unsigned char *recvdStr;
bit Timer0_Elapsed_Flag = 1;	//T0�¼�
bit UART_RecvdStr_Flag = 0;		//���ڽ��յ��ַ���

void Timer0_OnElapsed()
{
	Timer0_Elapsed_Flag = 1;
}

void UART_OnRecvdStr(const unsigned char* str)
{
	recvdStr = str;
	UART_RecvdStr_Flag = 1;
}

void main()
{
	IIC_Init();
	SHT30_Init();
	LCD1602_Init();

	Timer0_Init();
	Timer0_Event_Elapsed = &Timer0_OnElapsed;
	Timer0_SetInterval(5000);
	Timer0_Start();

	UART_Event_RecvdStr = &UART_OnRecvdStr;
	UART_Init();

	EA = 1;

	while (1)
	{
		if (Timer0_Elapsed_Flag)
		{
			if (SHT30_DataProcess())
			{
				//ˢ��LCD1602��ʾ
				sprintf(temp_ch, "T:%.2f RH:%.2f\r\n", SHT30_T, SHT30_RH);
				LCD1602_ShowString(1, 0, temp_ch);

				//��������
				UART_SendString(temp_ch);
				Timer0_Elapsed_Flag = 0;
			}
		}

		if (UART_RecvdStr_Flag)
		{
			//δ�ҵ���ֱ����ʾ������������
			LCD1602_Clear_Row(0);
			LCD1602_ShowString(0, 0, recvdStr);

			//refreshFlag = 0;
			UART_RecvdStr_Flag = 0;
		}
	}
}
