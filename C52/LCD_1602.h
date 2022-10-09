#ifndef _LCD_1602_H
#define _LCD_1602_H

#ifndef _IIC_H
#include "IIC.h"
#endif // !_IIC_H

#ifndef _STRING_H
#include "string.h"
#endif // !_STRING_H

/// <summary>
/// ��ʼ�� LCD 1602��ǰ��������IIC��ʼ��
/// </summary>
void LCD_1602_Init();

/// <summary>
/// ����
/// </summary>
void LCD_1602_Clear();

/// <summary>
/// �����
/// </summary>
void LCD_1602_Clear_Row(unsigned char row);

/// <summary>
/// ��ʾ�ַ���
/// </summary>
/// <param name="row">��</param>
/// <param name="column">��</param>
/// <param name="str"></param>
void LCD_1602_ShowString(unsigned char row, unsigned char column, const unsigned char* str);

#endif
