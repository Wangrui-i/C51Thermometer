#include "REG52.H"
#include "intrins.h"
#include "IIC.h"

sbit SCL = P2 ^ 0;
sbit SDA = P2 ^ 1;

/// <summary>
/// IICר���ӳ�
/// </summary>
void dalay()
{
    _nop_();
    _nop_();
}

/// <summary>
/// ����������ɣ��ȴ�Ӧ��
/// <para>����������һ���ֽڵ�����֮����SDA���ߣ��ȴ��ӻ����źţ�����ӻ���Ӧ��SDA��һֱ���ߣ��ȴ�Լ250us�󷵻�0����ʾ��Ӧ��</para>
/// <para>�����SCL�ߵ�ƽ�ڼ䣬SDA�����豸���ͱ�ʾ���豸Ӧ�𣬴�ʱwhile������Ӧ��λ����������1����ʾӦ��</para>
/// </summary>
/// <returns>
/// <para>0:��Ӧ��</para>
/// <para>1:Ӧ��</para>
/// </returns>
bit wait_ack()
{
    bit ack = 0;
    unsigned char i = 0;

    SCL = 1;
    dalay();

    while (SDA == 1)
    {
        i++;
        if (i >= 250)
        {
            break;
        }
        ack = SDA;
    }

    SCL = 0;   //���ͣ����Ӧ��λ

    return !ack;
}

/// <summary>
/// IIC��ʼ�ź�
/// </summary>
void IIC_Start()
{
    SDA = 1;
    dalay();
    SCL = 1;
    dalay();
    SDA = 0;
    dalay();
    SCL = 0;    //ǯסI2C���ߣ�׼�����ͻ��������
}

/// <summary>
/// IICֹͣ�ź�
/// </summary>
void IIC_Stop()
{
    SDA = 0;
    dalay();
    SCL = 0;
    dalay();
    SCL = 1;
    dalay();
    SDA = 1;
    dalay();
}

/// <summary>
/// IIC��ʼ��
/// </summary>
void IIC_Init()
{
    SCL = 1;
    dalay();
    SDA = 1;
    dalay();
}

/// <summary>
/// ����һ���ֽڣ��Ӹ�λ����λ����
/// <para>������ӻ��������ݣ��ӻ���ʱ�ӵ��½��زɼ�SDA������</para>
/// </summary>
/// <param name="dat"></param>
/// <returns>
/// <para>0:�ӻ���Ӧ�𣬲�Ҫ������������</para>
/// <para>1:�ӻ�Ӧ�𣬼�����������</para>
/// </returns>
bit IIC_Write_Byte(unsigned char dat)
{
    unsigned char i;

    for (i = 0; i < 8; i++)
    {
        SDA = (bit)(dat & 0x80);   //��д��λ
        dalay();
        SCL = 1;
        dalay();
        SCL = 0;          //�½��زɼ�����
        dalay();
        dat = dat << 1;
    }

    SDA = 1;//������Ϻ��ͷ������ߣ����ӻ�Ӧ��
    return wait_ack();//�ȴ�Ӧ��
}

/// <summary>
/// IIC���ֽ�
/// </summary>
/// <param name="ack">
/// <para>��</para>
/// <para>����0->���ټ�����ȡ����</para>
/// <para>����1->������ȡ��һ���ֽ�</para>
/// </param>
/// <returns></returns>
unsigned char IIC_Read_Byte(bit ack)
{
    unsigned char i = 0;
    unsigned char result = 0;

    SDA = 1;      //��ȷ�������ͷ�SDA
    dalay();

    for (i = 0; i < 8; i++)
    {
        SCL = 1;
        result = (result << 1) | SDA;
        dalay();
        SCL = 0;    //���ͣ��ɼ�����
        dalay();
    }

    //����Ӧ��λ
    SDA = !ack;
    SCL = 1;
    dalay();
    SCL = 0;    //���ͣ����Ӧ��λ
    dalay();

    return result;
}
