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
/// <param name="x">��</param>
/// <param name="y">��</param>
/// <param name="str"></param>
void LCD_1602_ShowString(unsigned char x, unsigned char y, unsigned char* str);

#endif
