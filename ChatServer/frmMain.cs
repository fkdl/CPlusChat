using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Net;
using System.Net.Sockets;
using System.Threading;

namespace 自做网络通讯
{
    public partial class frmMain : Form
    {
        public frmMain()
        {
            InitializeComponent();
            TextBox.CheckForIllegalCrossThreadCalls = false;
        }

        Socket socketwatch = null;
        Thread watchthread = null;

        private void btnServerConn_Click(object sender, EventArgs e)
        {
            socketwatch = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
            IPAddress ipaddress = null;
            try
            {
                ipaddress = IPAddress.Parse(txtIP.Text);
            }
            catch(Exception ex)
            {
                MessageBox.Show("IPv4地址不合法！");
                return;
            }
            int port = -1;
            try
            {
                port = Int32.Parse(txtPort.Text);
            }
            catch(Exception ex)
            {
                MessageBox.Show("端口不是整数！");
                return;
            }
            IPEndPoint endpoint = new IPEndPoint(ipaddress, port);
            //监听绑定一个的节点
            socketwatch.Bind(endpoint);
            //将套接字的监听队列长度限制为20
            socketwatch.Listen(20);
            txtMsg.AppendText("开始监听客户端"+"\r\n");
            watchthread = new Thread(new ThreadStart(loopListen));
            //设置为后台线程
            watchthread.IsBackground = true;
            //启动线程
            watchthread.Start();
        }


        //创建一个负责和客户端通信的套接字 
        Socket socConnection = null;

        private void loopListen()
        {
            while (true)
            {
                //没有收到请求就阻塞了
                socConnection = socketwatch.Accept();
                txtMsg.AppendText("连接客户端成功！\r\n");
                ParameterizedThreadStart pts = new ParameterizedThreadStart(ServerRecMsg);
                Thread th = new Thread(pts);
                th.Start(socConnection);
                th.IsBackground = true;
            }
        }

        private void ServerRecMsg(object socketClientPara)
        {
            Socket socketServer = socketClientPara as Socket;
            while (true)
            {
                //创建一个内存缓冲区 其大小为1024*1024字节  即1M
                byte[] arrServerRecMsg = new byte[1024 * 1024];
                //将接收到的信息存入到内存缓冲区,并返回其字节数组的长度
                int length = socketServer.Receive(arrServerRecMsg);
                //将机器接受到的字节数组转换为人可以读懂的字符串
                string strSRecMsg = Encoding.UTF8.GetString(arrServerRecMsg, 0, length);
                //将发送的字符串信息附加到文本框txtMsg上  
                txtMsg.AppendText(GetCurrentTime() + "\r\n" + "客户端:" + "\r\n" + strSRecMsg + "\r\n");
            }
        }


        //发送信息的方法
        private void SeverSendMsg(string Msg)
        {
            //转化成机器能够理解的字节数组
            byte[] arrSendMsg = Encoding.UTF8.GetBytes(Msg);
            //发送
            socConnection.Send(arrSendMsg);
            txtMsg.AppendText(GetCurrentTime()+"\r\n"+"服务器端："+Msg+"\r\n");
        }
       


        private void btnSend_Click(object sender, EventArgs e)
        {
            if (txtSend.Text=="")
            {
                MessageBox.Show("发送内容不能为空！");
            } 
            else
            {
                SeverSendMsg(txtSend.Text.Trim());
                txtSend.Text = "";
            }
        }


        /// <summary>
        /// 获取当前系统时间的方法
        /// </summary>
        /// <returns>当前时间</returns>
        private DateTime GetCurrentTime()
        {
            DateTime currentTime = new DateTime();
            currentTime = DateTime.Now;
            return currentTime;
        }
    }
}
