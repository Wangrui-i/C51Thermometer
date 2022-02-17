#include "REG52.H"
#include "IIC.h"
#include "LCD_1602.h"

#define _LCD_1602_device_type_id 0x4e
#define _LCD_1602_device_id 0x27

void LCD_1602_Init();
void LCD_1602_Clear();
void LCD_1602_write_command(char _comm);
void LCD_1602_write_data(char _ch);
void LCD_1602_ShowString(unsigned char _row, unsigned char _column, unsigned char* _str);

/// <summary>
/// ��ʼ�� LCD 1602
/// </summary>
void LCD_1602_Init()
{
    IIC_Switch_Device(_LCD_1602_device_type_id, _LCD_1602_device_id);
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
    IIC_Switch_Device(_LCD_1602_device_type_id, _LCD_1602_device_id);
    LCD_1602_write_command(0x01); // ����
}

/// <summary>
/// LCD 1602 дָ��
/// </summary>
/// <param name="_comm">ָ��</param>
void LCD_1602_write_command(char _comm)
{
    char tmp;
    tmp = _comm & 0xF0;  //���������λΪԭʼ״̬����������0x80,0x00�����λ����1������0x80
    tmp |= 0x0C;        //������4λΪָ��ĸ���λ������λΪ (null)1, EN = 1, RS = 0, RW = 0
    
    //tmp ���ս����0x8c
    IIC_Write_byte(tmp);

    tmp &= 0xFB; // Make EN = 0
    IIC_Write_byte(tmp);

    tmp = (_comm & 0x0F) << 4; //��ָ��ĵ���λ �͵���λ�ñ���
    tmp |= 0x0C;              // (null)1, EN = 1, RS = 0, RW = 0
    IIC_Write_byte(tmp);

    tmp &= 0xFB; // Make EN = 0
    IIC_Write_byte(tmp);
}

/// <summary>
/// LCD д�ַ�
/// </summary>
/// <param name="_ch"></param>
void LCD_1602_write_data(char _ch)
{
    char tmp;
    tmp = _ch & 0xF0;
    tmp |= 0x0D; // RS = 0, RW = 0, EN = 1
    IIC_Write_byte(tmp);

    tmp &= 0xFB; // Make EN = 0
    IIC_Write_byte(tmp);

    tmp = (_ch & 0x0F) << 4;
    tmp |= 0x0D; // RS = 0, RW = 0, EN = 1
    IIC_Write_byte(tmp);

    tmp &= 0xFB; // Make EN = 0
    IIC_Write_byte(tmp);
}

/// <summary>
/// ��ʾ�ַ���
/// <para>���Զ�����</para>
/// </summary>
/// <param name="row">��</param>
/// <param name="column">��</param>
/// <param name="_str"></param>
void LCD_1602_ShowString(unsigned char _row, unsigned char _column, unsigned char* _str)
{
    unsigned char _count = 16;
    _count -= _column;

    IIC_Switch_Device(_LCD_1602_device_type_id, _LCD_1602_device_id);

    if (_row == 0)
    {
        LCD_1602_write_command(0x80 | _column);
    }
    if (_row == 1)
    {
        LCD_1602_write_command(0xc0 | _column);
    }
    //����ַ���
    while (*_str)
    {
        //�Զ�����
        if (!_row && !_count)
        {
            LCD_1602_write_command(0xc0 | 0);
        }
        _count--;

        LCD_1602_write_data(*_str++);
    }
}