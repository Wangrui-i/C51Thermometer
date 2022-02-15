#include "STC89C5xRC.h"
#include "IIC.h"

sbit SCL = P2 ^ 0;
sbit SDA = P2 ^ 1;

void IIC_dalay();
void IIC_start();
void IIC_stop();
void IIC_Init();
void IIC_send_ack(bit _ack);
bit IIC_get_ack();
bit IIC_Write_byte(unsigned char _data);
bit IIC_Switch_Device(unsigned char _type_id, unsigned char _device_id);
unsigned char IIC_read_byte();
unsigned char IIC_Read_Addr_byte(unsigned char _device_type_id, unsigned char _device_id);

/// <summary>
/// IICר���ӳ�
/// </summary>
void IIC_dalay()
{
    _nop_();
    _nop_();
}

/// <summary>
/// ��ʼ�źţ�ʱ�Ӹߣ����ݸ߱��
/// </summary>
void IIC_start()
{
    SDA = 1;
    IIC_dalay();
    SCL = 1;
    IIC_dalay();
    SDA = 0;
    IIC_dalay();
    SCL = 0;    //ǯסI2C���ߣ�׼�����ͻ��������
}

/// <summary>
/// ֹͣ�ź�
/// </summary>
void IIC_stop()
{
    SDA = 0;
    IIC_dalay();
    SCL = 0;
    IIC_dalay();
    SCL = 1;
    IIC_dalay();
    SDA = 1;
    IIC_dalay();
}

/// <summary>
/// IIC��ʼ��
/// </summary>
void IIC_Init()
{
    SCL = 1;
    IIC_dalay();
    SDA = 1;
    IIC_dalay();
}

/// <summary>
/// ��ȡ������ɺ󣬷���Ӧ��λ
/// </summary>
/// <param name="_ack">
/// <para>��</para>
/// <para>����0->��Ӧ�𣬸��ߴӻ��Ҳ��ټ����������ݣ��ӻ�ֹͣ��������</para>
/// <para>����1->Ӧ�𣬸��ߴӻ���Ҫ������ȡ��һ���ֽڣ��ӻ��յ�����źź������������</para>
/// </param>
void IIC_send_ack(bit _ack)
{
    SDA = !_ack;
    SCL = 1;
    IIC_dalay();
    SCL = 0;    //���ͣ����Ӧ��λ
    IIC_dalay();
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
bit IIC_get_ack()
{
    bit ack = 0;
    unsigned char i = 0;

    SCL = 1;
    IIC_dalay();

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
/// ����һ���ֽڣ��Ӹ�λ����λ����
/// <para>������ӻ��������ݣ��ӻ���ʱ�ӵ��½��زɼ�SDA������</para>
/// </summary>
/// <param name="_data"></param>
/// <returns>
/// <para>0:��Ӧ��</para>
/// <para>1:Ӧ��</para>
/// </returns>
bit IIC_Write_byte(unsigned char _data)
{
    unsigned char i;

    for (i = 0; i < 8; i++)
    {
        SDA = (bit)(_data & 0x80);   //��д��λ
        IIC_dalay();
        SCL = 1;
        IIC_dalay();
        SCL = 0;          //�½��زɼ�����
        IIC_dalay();
        _data = _data << 1;
    }

    SDA = 1;//������Ϻ��ͷ������ߣ����ӻ�Ӧ��
    return IIC_get_ack();//�ȴ�Ӧ��
}

/// <summary>
/// �л��豸
/// </summary>
/// <param name="_type_id">���豸����id���ɹ�Ӧ�̾�����һ����ͬ���豸��ID����ͬ��</param>
/// <param name="_device_id">���豸id�����ڴ��豸���޸ģ������ͬ�豸���ӵ�ͬһ����ʱ��Ҫ���豸���޸�</param>
/// <returns>
/// <para>0:�豸û��Ӧ�𣬿����л�ʧ��</para>
/// <para>1:�豸�ɹ�Ӧ��</para>
/// </returns>
bit IIC_Switch_Device(unsigned char _type_id, unsigned char _device_id)
{
    bit result = 0;
    IIC_stop();
    IIC_start();

    result = IIC_Write_byte(_type_id) && IIC_Write_byte(_device_id);

    return result;
}

//todo:��ȡ����δ��֤

/// <summary>
/// ��ȡ����
/// </summary>
/// <returns>data</returns>
unsigned char IIC_read_byte()
{
    unsigned char i = 0;
    unsigned char result = 0;

    SDA = 1;      //��ȷ�������ͷ�SDA
    IIC_dalay();

    for (i = 0; i < 8; i++)
    {
        SCL = 1;
        result = (result << 1) | SDA;
        IIC_dalay();
        SCL = 0;    //���ͣ��ɼ�����
        IIC_dalay();
    }

    return result;
}

/// <summary>
/// ��ȡ���豸һ���ֽ�����
/// </summary>
/// <param name="_device_type_id">���豸����id���ɹ�Ӧ�̾�����һ����ͬ���豸��ID����ͬ��</param>
/// <param name="_device_id">���豸id�����ڴ��豸���޸ģ������ͬ�豸���ӵ�ͬһ����ʱ��Ҫ���豸���޸�</param>
/// <returns>data</returns>
unsigned char IIC_Read_Addr_byte(unsigned char _device_type_id, unsigned char _device_id)
{
    unsigned char result;

    IIC_start();
    IIC_Write_byte(_device_type_id);//�����豸��ַ+д�ź�
    IIC_Write_byte(_device_id);    //���ʹ洢����Ԫ
    IIC_start();            //�����������IIC

    IIC_Write_byte(_device_type_id + 1);//�����豸��ַ+���ź�
    result = IIC_read_byte();//��������
    IIC_send_ack(0);//���ͷ�Ӧ���źţ�ֹͣ��ȡ����
    IIC_stop();

    return result;
}