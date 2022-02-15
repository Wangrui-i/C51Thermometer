#ifndef __LCD_1602_H
#define __LCD_1602_H

#include "STC89C5xRC.h"
#include "intrins.h"

/// <summary>
/// ��ʼ�� LCD 1602
/// </summary>
void LCD_1602_Init();

/// <summary>
/// ����
/// </summary>
void LCD_1602_Clear();

/// <summary>
/// ��ʾ�ַ���
/// </summary>
/// <param name="row">��</param>
/// <param name="column">��</param>
/// <param name="str"></param>
void LCD_1602_ShowString(unsigned char row, unsigned char column, unsigned char* str);

#endif
