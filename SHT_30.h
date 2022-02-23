#ifndef __SHT_30
#define __SHT_30

/// <summary>
/// SHT 30 ��ʼ��
/// </summary>
void SHT_30_Init();

/// <summary>
/// SHT 30 ���ݶ�ȡ�봦��
/// </summary>
/// <returns></returns>
bit SHT_30_DataProcess();

/// <summary>
/// SHT 30 ԭʼ����
/// </summary>
extern unsigned char SHT_30_RAW_Data[6];

/// <summary>
/// SHT 30 �¶�
/// </summary>
extern float SHT_30_T;

/// <summary>
/// SHT 30 ʪ��
/// </summary>
extern float SHT_30_RH;

#endif // !__SHT_30
