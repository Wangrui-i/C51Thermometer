#include "REG52.H"
#include "intrins.h"
#include "UART.h"
#include "ASCII.h"

/*Define UART parity mode*/
#define NONE_PARITY     0   //None parity
#define ODD_PARITY      1   //Odd parity,��У��
#define EVEN_PARITY     2   //Even parity,żУ��
#define MARK_PARITY     3   //Mark parity,1У��
#define SPACE_PARITY    4   //Space parity,0У��

#define FOSC 11059200L      //System frequency
#define BAUD 9600           //UART baudrate

#define PARITYBIT NONE_PARITY   //Testing even parity

unsigned char recvdStr[32];

void (*Event_UART_RecvdStr)(unsigned char* str);

/// <summary>
/// ����ͨ�ų�ʼ��
/// <para>ʹ���˶�ʱ��1</para>
/// </summary>
void UART_Init()
{
#if (PARITYBIT == NONE_PARITY)
	SCON = 0x50;            //8-bit variable UART
#elif (PARITYBIT == ODD_PARITY) || (PARITYBIT == EVEN_PARITY) || (PARITYBIT == MARK_PARITY)
	SCON = 0xda;            //9-bit variable UART, parity bit initial to 1
#elif (PARITYBIT == SPACE_PARITY)
	SCON = 0xd2;            //9-bit variable UART, parity bit initial to 0
#endif

	TMOD = 0x20;            //Set Timer1 as 8-bit auto reload mode
	TH1 = TL1 = -(FOSC / 12 / 32 / BAUD); //Set auto-reload vaule
	TR1 = 1;                //Timer1 start run
	ES = 1;                 //Enable UART interrupt
}

/// <summary>
/// ����һ���ֽ�
/// </summary>
/// <param name="data"></param>
void UART_SendData(unsigned char _data)
{
	ACC = _data;              //Calculate the even parity bit P (PSW.0)
#if (PARITYBIT != NONE_PARITY)
	if (P)                  //Set the parity bit according to P
	{
#if (PARITYBIT == ODD_PARITY)
		TB8 = 0;            //Set parity bit to 0
#elif (PARITYBIT == EVEN_PARITY)
		TB8 = 1;            //Set parity bit to 1
#endif
	}
	else
	{
#if (PARITYBIT == ODD_PARITY)
		TB8 = 1;            //Set parity bit to 1
#elif (PARITYBIT == EVEN_PARITY)
		TB8 = 0;            //Set parity bit to 0
#endif
	}
#endif
	SBUF = ACC;             //Send data to UART buffer
	while (!TI);
	TI = 0;
}

/// <summary>
/// �����ַ���
/// </summary>
/// <param name="_str"></param>
void UART_SendString(char* str)
{
	while (*str)              //Check the end of the string
	{
		UART_SendData(*str++);     //Send current char and increment string ptr
	}
}

/// <summary>
/// ����ͨ�ţ������ַ�������
/// </summary>
/// <returns>���ݳ��ȴ��ڵ������鳤��ʱ������1</returns>
bit UART_recvingStr()
{
	unsigned char i = 0;
	unsigned char count = 0;
loop:
	//todo:��żУ��
	recvdStr[i] = SBUF;
	count = 0;
	RI = 0;
	if (i < sizeof(recvdStr) - 1)
	{
		i++;
		while (!RI)
		{
			count++;
			//�������ݵȴ��ӳ٣��ȴ�ʱ��̫�ûᵼ��CPU�������ã�̫�̻����"���ݰ����ָ�",Ĭ��count=130
			if (count > 130)
			{
				recvdStr[i] = NUL;
				return 0;
			}
		}
		goto loop;
	}
	return 1;
}

/// <summary>
/// �����жϷ���
/// </summary>
void UART_ISR() interrupt 4
{
	if (RI)
	{
		UART_recvingStr();
		(*Event_UART_RecvdStr)(recvdStr);
	}
}
