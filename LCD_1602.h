#ifndef __LCD_1602_H
#define __LCD_1602_H

/// <summary>
/// 初始化 LCD 1602
/// </summary>
void LCD_1602_Init();

/// <summary>
/// 清屏
/// </summary>
void LCD_1602_Clear();

/// <summary>
/// 显示字符串
/// </summary>
/// <param name="row">行</param>
/// <param name="column">列</param>
/// <param name="str"></param>
void LCD_1602_ShowString(unsigned char row, unsigned char column, const unsigned char* str);

#endif
