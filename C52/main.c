#include "main.h"

char temp_ch[32];	//��ʱ�洢Ҫ��ʾ���ַ���
unsigned char *recvdStr;
bit Timer_0_Elapsed_Flag = 0;	//T0�¼�
bit UART_RecvdStr_Flag = 0;		//���ڽ��յ��ַ���
//bit refreshFlag = 1;

void Timer_0_OnElapsed()
{
	Timer_0_Elapsed_Flag = 1;
}

void UART_OnRecvdStr(const unsigned char* str)
{
	recvdStr = str;
	UART_RecvdStr_Flag = 1;
}

void main()
{
	IIC_Init();
	SHT_30_Init();
	LCD_1602_Init();

	Timer_0_Init();
	Timer_0_Event_Elapsed = &Timer_0_OnElapsed;
	Timer_0_SetInterval(5000);
	Timer_0_Start();

	UART_Event_RecvdStr = &UART_OnRecvdStr;
	UART_Init();

	EA = 1;

	while (1)
	{
		if (Timer_0_Elapsed_Flag)
		{
			if (SHT_30_DataProcess())
			{
				//if (refreshFlag)
				//{
				//	LCD_1602_Clear_Row(0);
				//	refreshFlag = 0;
				//}
				//else
				//{
				//	refreshFlag = 1;
				//}

				//ˢ��LCD1602��ʾ
				sprintf(temp_ch, "T:%.2f RH:%.2f ", SHT_30_T, SHT_30_RH);
				LCD_1602_ShowString(1, 0, temp_ch);

				//��������
				UART_SendString(SHT_30_RAW_Data);
				Timer_0_Elapsed_Flag = 0;
			}
		}

		if (UART_RecvdStr_Flag)
		{
			//�������
			//SI:SetInterval ���ü��ʱ�䣬unsigned long(4�ֽ�)
			
			
			//δ�ҵ���ֱ����ʾ������������
			//LCD_1602_Clear_Row(0);
			LCD_1602_Clear();
			LCD_1602_ShowString(0, 0, recvdStr);

			//refreshFlag = 0;
			UART_RecvdStr_Flag = 0;
		}
	}
}
