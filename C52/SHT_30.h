#ifndef _SHT_30_H
#define _SHT_30_H

#ifndef _IIC_H
#include "IIC.h"
#endif // !_IIC_H

#ifndef _CRC_8_H
#include "CRC_8.h"
#endif // !_CRC_8_H

/// <summary>
/// SHT 30 ��ʼ����ǰ��������IIC��ʼ��
/// </summary>
void SHT_30_Init();

/// <summary>
/// SHT 30 ���ݶ�ȡ�봦��
/// </summary>
/// <returns></returns>
bit SHT_30_DataProcess();

/// <summary>
/// SHT 30 ԭʼ����(ʵ��ΪSHT_30_RAW_Data[6])
/// </summary>
extern unsigned char SHT_30_RAW_Data[7];

/// <summary>
/// SHT 30 �¶�
/// </summary>
extern float SHT_30_T;

/// <summary>
/// SHT 30 ʪ��
/// </summary>
extern float SHT_30_RH;

#endif // !_SHT_30_H
