#include "REG52.H"
#include "IIC.h"
#include "SHT_30.h"
#include "CRC_8.h"

/// <summary>
/// ��ʪ��ԭʼ����
/// </summary>
unsigned int SHT_30_raw_data[2];

/// <summary>
/// �¶�
/// </summary>
float SHT_30_T;

/// <summary>
/// ʪ��
/// </summary>
float SHT_30_RH;

/// <summary>
/// ��ʼ��
/// </summary>
void SHT_30_Init()
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
bit SHT_30_DataProcess()
{
	unsigned char buffer[6];

	IIC_Start();
	IIC_Write_Byte(0x88);
	IIC_Write_Byte(0xe0);
	IIC_Write_Byte(0x00);
	IIC_Stop();
	IIC_Start();
	IIC_Write_Byte(0x89);

	buffer[0] = IIC_Read_Byte(1);
	buffer[1] = IIC_Read_Byte(1);
	buffer[2] = IIC_Read_Byte(1);
	buffer[3] = IIC_Read_Byte(1);
	buffer[4] = IIC_Read_Byte(1);
	buffer[5] = IIC_Read_Byte(0);
	IIC_Stop();

	if (CRC_8_Check(&buffer[0], 2, buffer[2]) && CRC_8_Check(&buffer[3], 2, buffer[5]))
	{
		SHT_30_raw_data[0] = buffer[0];
		SHT_30_raw_data[0] <<= 8;
		SHT_30_raw_data[0] |= buffer[1];

		SHT_30_raw_data[1] = buffer[3];
		SHT_30_raw_data[1] <<= 8;
		SHT_30_raw_data[1] |= buffer[4];

		SHT_30_T = -45 + 175 * (1.0 * SHT_30_raw_data[0] / 65535);
		SHT_30_RH = 100 * (1.0 * SHT_30_raw_data[1] / 65535);

		return 1;
	}
	else
	{
		return 0;
	}
}
