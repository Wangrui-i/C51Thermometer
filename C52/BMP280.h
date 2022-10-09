#ifndef _BMP280_H
#define _BMP280_H

#ifndef _IIC_H
#include "IIC.h"
#endif // !_IIC_H

/// <summary>
/// BMP 280 ��ʼ����ǰ��������IIC��ʼ��
/// </summary>
void BMP280_Init();

/// <summary>
/// BMP 280 ���ݶ�ȡ�봦��
/// </summary>
/// <returns></returns>
bit BMP280_DataProcess();

#endif // !_BMP280_H