#include "REG52.H"
#include "IIC.h"
#include "LCD_1602.h"

/// <summary>
/// �л�����ǰ�豸
/// </summary>
/// <returns></returns>
void switch_device()
{
    IIC_Start();
    IIC_Write_Byte(0x4e);
    IIC_Write_Byte(0x27);
}

/// <summary>
/// дָ��
/// </summary>
/// <param name="comm"></param>
void write_command(char comm)
{
    char tmp;
    tmp = comm & 0xF0;  //���������λΪԭʼ״̬����������0x80,0x00�����λ����1������0x80
    tmp |= 0x0C;        //������4λΪָ��ĸ���λ������λΪ (null)1, EN = 1, RS = 0, RW = 0

    //tmp ���ս����0x8c
    IIC_Write_Byte(tmp);

    tmp &= 0xFB; // Make EN = 0
    IIC_Write_Byte(tmp);

    tmp = (comm & 0x0F) << 4; //��ָ��ĵ���λ �͵���λ�ñ���
    tmp |= 0x0C;              // (null)1, EN = 1, RS = 0, RW = 0
    IIC_Write_Byte(tmp);

    tmp &= 0xFB; // Make EN = 0
    IIC_Write_Byte(tmp);
}

/// <summary>
/// д�ַ�
/// </summary>
/// <param name="_ch"></param>
void write_char(char ch)
{
    char tmp;
    tmp = ch & 0xF0;
    tmp |= 0x0D; // RS = 0, RW = 0, EN = 1
    IIC_Write_Byte(tmp);

    tmp &= 0xFB; // Make EN = 0
    IIC_Write_Byte(tmp);

    tmp = (ch & 0x0F) << 4;
    tmp |= 0x0D; // RS = 0, RW = 0, EN = 1
    IIC_Write_Byte(tmp);

    tmp &= 0xFB; // Make EN = 0
    IIC_Write_Byte(tmp);
}

/// <summary>
/// ��ʼ��
/// </summary>
void LCD_1602_Init()
{
    switch_device();
    write_command(0x33); //��8λ����תΪ4λ����
    write_command(0x32); //
    write_command(0x28); // 4λ�����ߣ���ʾ2�У�5*7�����ַ�  �������0x38  ��Ϊ8λ�����ߣ���ʾ2�У�5*7�����ַ�
    write_command(0x0C); // ����ʾ���رչ�꣬����˸
    write_command(0x06); // �趨���뷽ʽ��������λ��
    write_command(0x01); // ����
    IIC_Stop();
}

/// <summary>
/// ����
/// </summary>
void LCD_1602_Clear()
{
    switch_device();
    write_command(0x01); // ����
    IIC_Stop();
}

/// <summary>
/// ��ʾ�ַ���
/// <para>���Զ�����</para>
/// </summary>
/// <param name="row">��</param>
/// <param name="column">��</param>
/// <param name="_str"></param>
void LCD_1602_ShowString(unsigned char row, unsigned char column, const unsigned char* str)
{
    unsigned char count = 16;
    count -= column;

    switch_device();

    if (row == 0)
    {
        write_command(0x80 | column);
    }
    if (row == 1)
    {
        write_command(0xc0 | column);
    }
    //����ַ���
    while (*str)
    {
        //�Զ�����
        if (!row && !count)
        {
            write_command(0xc0 | 0);
        }
        count--;

        write_char(*str++);
    }

    IIC_Stop();
}
