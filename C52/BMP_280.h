#pragma once
#include "IIC.h"

/// <summary>
/// BMP 280 ��ʼ����ǰ��������IIC��ʼ��
/// </summary>
void BMP_280_Init();

/// <summary>
/// BMP 280 ���ݶ�ȡ�봦��
/// </summary>
/// <returns></returns>
bit BMP_280_DataProcess();