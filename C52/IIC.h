#ifndef _IIC_H
#define _IIC_H

#ifndef _REG52_H
#include "reg52.h"
#endif // !_REG52_H

#ifndef _INTRINS_H
#include "intrins.h"
#endif // !_INTRINS_H

//#ifndef _STDLIB_H
//#include "stdlib.h"
//#endif // !_STDLIB_H

sbit IIC_SCL = P2 ^ 0;	//IICʱ������
sbit IIC_SDA = P2 ^ 1;	//IIC��������

/// <summary>
/// IIC��ʼ����IIC_SCLΪP2.0��IIC_SDAΪP2.1
/// </summary>
void IIC_Init();

/// <summary>
/// IIC��ʼ�ź�
/// </summary>
void IIC_Start();

/// <summary>
/// IICֹͣ�ź�
/// </summary>
void IIC_Stop();

/// <summary>
/// IICд�ֽ�
/// </summary>
/// <param name="dat"></param>
/// <returns>�ӻ�Ӧ��״̬</returns>
bit IIC_Write_Byte(unsigned char dat);

/// <summary>
/// IIC���ֽ�
/// </summary>
/// <param name="ack">
/// <para>��</para>
/// <para>����0->���ټ�����ȡ����</para>
/// <para>����1->������ȡ��һ���ֽ�</para>
/// </param>
/// <returns></returns>
unsigned char IIC_Read_Byte(bit ack);

#endif
