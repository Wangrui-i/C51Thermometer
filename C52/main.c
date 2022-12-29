#include "main.h"

unsigned char* recvdStr;
bit Timer0_Elapsed_Flag = 1;	//T0�¼�
bit UART_RecvdStr_Flag = 0;		//���ڽ��յ��ַ���
unsigned char tmp_content[24];
unsigned char tmp_contentLengthStr[20];
unsigned short contentLength;

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

	SHT30_Init(IIC_Start, IIC_Stop, IIC_Read_Byte, IIC_Write_Byte);

	Timer0_Init();
	Timer0_Event_Elapsed = Timer0_OnElapsed;
	Timer0_SetInterval(5000);
	Timer0_Start();

	UART_Event_RecvdStr = UART_OnRecvdStr;
	UART_Init();

	EA = 1;

	while (1)
	{
		if (Timer0_Elapsed_Flag)
		{
			if (SHT30_DataProcess())
			{
				// ƴ��POST
				// ���͸�����
				UART_SendString("POST /api/Thermometer/AddRawData HTTP/1.1\r\n");
				UART_SendString("Host:192.168.2.10:8080\r\n");
				UART_SendString("Content-Type:application/json\r\n");

				//ƴ���غ�
				sprintf(tmp_content, "{\"T\":%u,\"RH\":%u}\r\n", SHT30_T_uint16, SHT30_RH_uint16);

				//ƴ���غɳ���
				contentLength = strlen(tmp_content) - 2;
				sprintf(tmp_contentLengthStr, "Content-Length:%d\r\n\r\n", contentLength);
				UART_SendString(tmp_contentLengthStr);

				UART_SendString(tmp_content);
				Timer0_Elapsed_Flag = 0;
			}
		}

		if (UART_RecvdStr_Flag)
		{
			UART_RecvdStr_Flag = 0;
		}
	}
}
