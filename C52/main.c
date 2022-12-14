#include "main.h"

unsigned char* httpString;
unsigned char* recvdStr;
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

	Timer0_Init();
	Timer0_Event_Elapsed = &Timer0_OnElapsed;
	Timer0_SetInterval(50000);
	Timer0_Start();

	UART_Event_RecvdStr = &UART_OnRecvdStr;
	UART_Init();

	httpHelper_Init("192.168.1.4:8080");

	EA = 1;
	UART_SendString("I123456789");
	while (1)
	{
		if (Timer0_Elapsed_Flag)
		{
			UART_SendString("Flag");
			if (SHT30_DataProcess())
			{
				// ƴ��POST
				// ���͸�����
				UART_SendString("httpString");

				httpString = httpHelper_POST("/api/Thermometer/AddRawData", SHT30_RAW_Data);

				UART_SendString(httpString);
				Timer0_Elapsed_Flag = 0;
			}
		}

		if (UART_RecvdStr_Flag)
		{
			// ���յ����ڷ��ص���Ϣ
			// ûɶ�ã�ֱ�Ӷ�������
			UART_RecvdStr_Flag = 0;
		}
	}
}
