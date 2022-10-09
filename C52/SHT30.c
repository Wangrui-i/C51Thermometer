#include "SHT30.h"

/// <summary>
/// ��ʪ��ԭʼ����
/// </summary>
unsigned char SHT30_RAW_Data[7];

/// <summary>
/// �¶�
/// </summary>
float SHT30_T;

/// <summary>
/// ʪ��
/// </summary>
float SHT30_RH;

/// <summary>
/// ��ʼ��
/// </summary>
void SHT30_Init()
{
	IIC_Start();
	IIC_Write_Byte(0x88);
	IIC_Write_Byte(0x21);
	IIC_Write_Byte(0x30);
	IIC_Stop();
}

/// <summary>
/// ���ݶ�ȡ�봦��
/// </summary>
/// <returns></returns>
bit SHT30_DataProcess()
{
	unsigned int buffer[2];

	IIC_Start();
	IIC_Write_Byte(0x88);
	IIC_Write_Byte(0xe0);
	IIC_Write_Byte(0x00);
	IIC_Stop();
	IIC_Start();
	IIC_Write_Byte(0x89);

	SHT30_RAW_Data[0] = IIC_Read_Byte(1);
	SHT30_RAW_Data[1] = IIC_Read_Byte(1);
	SHT30_RAW_Data[2] = IIC_Read_Byte(1);
	SHT30_RAW_Data[3] = IIC_Read_Byte(1);
	SHT30_RAW_Data[4] = IIC_Read_Byte(1);
	SHT30_RAW_Data[5] = IIC_Read_Byte(0);
	SHT30_RAW_Data[6] = '\0';
	IIC_Stop();

	if (CRC8_Check(&SHT30_RAW_Data[0], 2, SHT30_RAW_Data[2]) && CRC8_Check(&SHT30_RAW_Data[3], 2, SHT30_RAW_Data[5]))
	{
		buffer[0] = SHT30_RAW_Data[0];
		buffer[0] <<= 8;
		buffer[0] |= SHT30_RAW_Data[1];

		buffer[1] = SHT30_RAW_Data[3];
		buffer[1] <<= 8;
		buffer[1] |= SHT30_RAW_Data[4];

		SHT30_T = 175.0f * (float)buffer[0] / 65535.0f - 45.0f;
		SHT30_RH = 100.0f * buffer[1] / 65535.0f;

		return 1;
	}
	else
	{
		return 0;
	}
}
