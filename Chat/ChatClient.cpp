#include "ChatClient.h"
#include "EncodingTool.h"
#include "MessageLog.h"
#include <thread>


#define  MAXBUFLEN 256  

ChatClient::ChatClient()
{
}

void ChatClient::Connect(LPCTSTR addr, int port)
{
	WSADATA wsaData;
	SOCKADDR_IN addrServer;// 服务端地址
	WSAStartup(MAKEWORD(2, 2), &wsaData);
	// 新建客户端socket
	this->socketClient = socket(AF_INET, SOCK_STREAM, 0);
	// 定义要连接的服务端地址
	addrServer.sin_addr.S_un.S_addr = inet_addr(EncodingTool::WideCharToMultiChar(addr));
	addrServer.sin_family = AF_INET;
	addrServer.sin_port = htons(port);// 连接端口6000
	// 连接到服务端
	if (connect(this->socketClient, (SOCKADDR*)&addrServer, sizeof(SOCKADDR)) == SOCKET_ERROR)
	{
		MessageLog::AddLog(_T("connect failed!"));
		closesocket(this->socketClient);
	}
	else
	{
		// 开启工作线程
		thread t(&ChatClient::StartRecvFromServer, this);
		MessageLog::AddLog(_T("connect success!"));
	}
}

void ChatClient::StartRecvFromServer()
{
	while (true)
	{
		int numrcv;
		CHAR buffer[MAXBUFLEN];
		numrcv = recv(this->socketClient, buffer, MAXBUFLEN, 0);

	}
}

void ChatClient::SendMsg(LPCTSTR msg)
{
	CHAR* buffers = EncodingTool::UnicodeToUTF8(msg);
	send(this->socketClient, buffers, strlen(buffers), 0);
}