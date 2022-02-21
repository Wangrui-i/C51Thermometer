#include "REG52.H"
#include "IIC.h"
#include "LCD_1602.h"

void LCD_1602_write_command(char comm);
void LCD_1602_write_data(char ch);

/// <summary>
/// �л�����ǰ�豸
/// </summary>
/// <returns></returns>
void switch_device()
{
    //IIC_Stop();
    IIC_Start();
    IIC_Write_byte(0x4e);
    IIC_Write_byte(0x27);
}

/// <summary>
/// ��ʼ�� LCD 1602
/// </summary>
void LCD_1602_Init()
{
    switch_device();
    LCD_1602_write_command(0x33); //��8λ����תΪ4λ����
    LCD_1602_write_command(0x32); //
    LCD_1602_write_command(0x28); // 4λ�����ߣ���ʾ2�У�5*7�����ַ�  �������0x38  ��Ϊ8λ�����ߣ���ʾ2�У�5*7�����ַ�
    LCD_1602_write_command(0x0C); // ����ʾ���رչ�꣬����˸
    LCD_1602_write_command(0x06); // �趨���뷽ʽ��������λ��
    LCD_1602_write_command(0x01); // ����
    IIC_Stop();
}

/// <summary>
/// ����
/// </summary>
void LCD_1602_Clear()
{
    switch_device();
    LCD_1602_write_command(0x01); // ����
    IIC_Stop();
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
/// <param name="_ch"></param>
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
/// <para>���Զ�����</para>
/// </summary>
/// <param name="row">��</param>
/// <param name="column">��</param>
/// <param name="_str"></param>
void LCD_1602_ShowString(unsigned char row, unsigned char column, unsigned  char* str)
{
    unsigned char count = 16;
    count -= column;

    switch_device();

    if (row == 0)
    {
        LCD_1602_write_command(0x80 | column);
    }
    if (row == 1)
    {
        LCD_1602_write_command(0xc0 | column);
    }
    //����ַ���
    while (*str)
    {
        //�Զ�����
        if (!row && !count)
        {
            LCD_1602_write_command(0xc0 | 0);
        }
        count--;

        LCD_1602_write_data(*str++);
    }

    IIC_Stop();
}
