#ifndef __IIC_H
#define __IIC_H

/// <summary>
/// IIC��ʼ��
/// </summary>
void IIC_Init();

/// <summary>
/// ����һ���ֽڣ��Ӹ�λ����λ����
/// <para>������ӻ��������ݣ��ӻ���ʱ�ӵ��½��زɼ�SDA������</para>
/// </summary>
/// <param name="_data"></param>
/// <returns>
/// <para>0:��Ӧ��</para>
/// <para>1:Ӧ��</para>
/// </returns>
bit IIC_Write_byte(unsigned char _data);

/// <summary>
/// �л��豸
/// </summary>
/// <param name="_device_type_id">���豸����id���ɹ�Ӧ�̾�����һ����ͬ���豸��ID����ͬ��</param>
/// <param name="_device_id">���豸id�����ڴ��豸���޸ģ������ͬ�豸���ӵ�ͬһ����ʱ��Ҫ���豸���޸�</param>
/// <returns>
/// <para>0:�豸û��Ӧ�𣬿����л�ʧ��</para>
/// <para>1:�豸�ɹ�Ӧ��</para>
/// </returns>
bit IIC_Switch_Device(unsigned char _device_type_id, unsigned char _device_id);

/// <summary>
/// ��ȡ���豸һ���ֽ�����
/// </summary>
/// <param name="_device_type_id">���豸����id���ɹ�Ӧ�̾�����һ����ͬ���豸��ID����ͬ��</param>
/// <param name="_device_id">���豸id�����ڴ��豸���޸ģ������ͬ�豸���ӵ�ͬһ����ʱ��Ҫ���豸���޸�</param>
/// <returns>data</returns>
unsigned char IIC_Read_Addr_byte(unsigned char _device_type_id, unsigned char _device_id);

#endif
