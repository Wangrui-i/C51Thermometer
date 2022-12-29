#ifndef _SHT30_H
#define _SHT30_H

#include "IIC.h"
#include "CRC8.h"
#include "string.h"

/// <summary>
/// SHT30 ��ʼ����ǰ��������IIC��ʼ��
/// </summary>
void SHT30_Init();

/// <summary>
/// SHT30 ���ݶ�ȡ�봦��
/// </summary>
/// <returns></returns>
bit SHT30_DataProcess();

/// <summary>
/// SHT30 ԭʼ����(ʵ��ΪSHT_30_RAW_Data[6])
/// </summary>
extern unsigned char SHT30_RAW_Data[7];

/// <summary>
/// SHT30 �¶�
/// </summary>
extern float SHT30_T;

extern unsigned int SHT30_T_16;

/// <summary>
/// SHT30 ʪ��
/// </summary>
extern float SHT30_RH;

extern unsigned int SHT30_RH_16;

#endif
