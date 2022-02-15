#include "STC89C5xRC.h"
#include "IIC.h"
#include "LCD_1602.h"

#define _LCD_1602_type_id 0x4e
#define _LCD_1602_device_id 0x27

void LCD_1602_Init();
void LCD_1602_Clear();
void LCD_1602_write_command(char comm);
void LCD_1602_write_data(char ch);
void LCD_1602_ShowString(unsigned char x, unsigned char y, unsigned char* str);

/// <summary>
/// ��ʼ�� LCD 1602
/// </summary>
void LCD_1602_Init()
{
    IIC_Switch_Device(_LCD_1602_type_id, _LCD_1602_device_id);
    LCD_1602_write_command(0x33); //��8λ����תΪ4λ����
    LCD_1602_write_command(0x32); //
    LCD_1602_write_command(0x28); // 4λ�����ߣ���ʾ2�У�5*7�����ַ�  �������0x38  ��Ϊ8λ�����ߣ���ʾ2�У�5*7�����ַ�
    LCD_1602_write_command(0x0C); // ����ʾ���رչ�꣬����˸
    LCD_1602_write_command(0x06); // �趨���뷽ʽ��������λ��
    LCD_1602_write_command(0x01); // ����
}

/// <summary>
/// ����
/// </summary>
void LCD_1602_Clear()
{
    IIC_Switch_Device(_LCD_1602_type_id, _LCD_1602_device_id);
    LCD_1602_write_command(0x01); // ����
}

/// <summary>
/// LCD 1602 дָ��
/// </summary>
/// <param name="comm">ָ��</param>
void LCD_1602_write_command(char comm)
{
    char tmp;
    tmp = comm & 0xF0;  //���������λΪԭʼ״̬����������0x80,0x00�����λ����1������0x80
    tmp |= 0x0C;        //������4λΪָ��ĸ���λ������λΪ (null)1, EN = 1, RS = 0, RW = 0
    
    //tmp ���ս����0x8c
    IIC_Write_byte(tmp);

    tmp &= 0xFB; // Make EN = 0
    IIC_Write_byte(tmp);

    tmp = (comm & 0x0F) << 4; //��ָ��ĵ���λ �͵���λ�ñ���
    tmp |= 0x0C;              // (null)1, EN = 1, RS = 0, RW = 0
    IIC_Write_byte(tmp);

    tmp &= 0xFB; // Make EN = 0
    IIC_Write_byte(tmp);
}

/// <summary>
/// LCD д�ַ�
/// </summary>
/// <param name="ch"></param>
void LCD_1602_write_data(char ch)
{
    char tmp;
    tmp = ch & 0xF0;
    tmp |= 0x0D; // RS = 0, RW = 0, EN = 1
    IIC_Write_byte(tmp);

    tmp &= 0xFB; // Make EN = 0
    IIC_Write_byte(tmp);

    tmp = (ch & 0x0F) << 4;
    tmp |= 0x0D; // RS = 0, RW = 0, EN = 1
    IIC_Write_byte(tmp);

    tmp &= 0xFB; // Make EN = 0
    IIC_Write_byte(tmp);
}

/// <summary>
/// ��ʾ�ַ���
/// </summary>
/// <param name="x">��</param>
/// <param name="y">��</param>
/// <param name="str"></param>
void LCD_1602_ShowString(unsigned char x, unsigned char y, unsigned char* str)
{
    IIC_Switch_Device(_LCD_1602_type_id, _LCD_1602_device_id);

    if (x == 0)
    {
        LCD_1602_write_command(0x80 | y);
    }
    if (x == 1)
    {
        LCD_1602_write_command(0xc0 | y);
    }
    //����ַ���
    while (*str != '\0')
    {
        LCD_1602_write_data(*str);
        str++;
    }
}