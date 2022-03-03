﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using Cowboy.Sockets;
using ThermometerServer.Utils;

namespace ThermometerServer
{
    /// <summary>
    /// MainWindow.xaml 的交互逻辑
    /// </summary>
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            InitializeComponent();
            Global.tcpServer.ClientConnected += TcpServer_ClientConnected;
            Global.tcpServer.ClientDisconnected += TcpServer_ClientDisconnected;
            Global.tcpServer.ClientDataReceived += TcpServer_ClientDataReceived;
        }

        private void TcpServer_ClientConnected(object sender, TcpClientConnectedEventArgs e)
        {
            this.Dispatcher.Invoke(new Action(() =>
            logText.Text += "TCP Connect:" + e.Session + "\n"));
        }

        private void TcpServer_ClientDisconnected(object sender, TcpClientDisconnectedEventArgs e)
        {
            this.Dispatcher.Invoke(new Action(() =>
            logText.Text += "TCP Disconnect:" + e.Session + "\n"));
        }

        private void TcpServer_ClientDataReceived(object sender, TcpClientDataReceivedEventArgs e)
        {
            this.Dispatcher.Invoke(new Action(() =>
            {
                //处理数据
                byte[] b1 = { e.Data[e.DataOffset], e.Data[e.DataOffset + 1] };
                byte[] b2 = { e.Data[e.DataOffset + 3], e.Data[e.DataOffset + 4] };

                if (Utils.CRC_8.CRC_8_Check(b1, 2, e.Data[e.DataOffset + 2]) && Utils.CRC_8.CRC_8_Check(b2, 2, e.Data[e.DataOffset + 5]))
                {
                    UInt16[] buffer = new UInt16[2];
                    buffer[0] = e.Data[e.DataOffset];
                    buffer[0] <<= 8;
                    buffer[0] |= e.Data[e.DataOffset + 1];

                    buffer[1] = e.Data[e.DataOffset + 3];
                    buffer[1] <<= 8;
                    buffer[1] |= e.Data[e.DataOffset + 4];

                    float SHT_30_T = 175.0f * (float)buffer[0] / 65535.0f - 45.0f;
                    float SHT_30_RH = 100.0f * buffer[1] / 65535.0f;

                    //string text = Encoding.ASCII.GetString(e.Data, e.DataOffset, e.DataLength);

                    logText.Text += $"T:{SHT_30_T} RH:{SHT_30_RH} \n";
                }

            }));
        }


        private void btnControl_Click(object sender, RoutedEventArgs e)
        {
            if (Global.tcpServer.IsListening)
            {
                Global.tcpServer.Shutdown();
                btnControl.Content = "开始服务";
            }
            else
            {
                Global.tcpServer.Listen();
                btnControl.Content = "停止服务";
            }
        }
    }
}
