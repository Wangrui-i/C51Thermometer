#ifndef __LCD_1602_H
#define __LCD_1602_H

/// <summary>
/// ��ʼ�� LCD 1602��ǰ��������IIC��ʼ��
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
void LCD_1602_ShowString(unsigned char row, unsigned char column, const unsigned char* str);

#endif
