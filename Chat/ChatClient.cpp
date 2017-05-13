#include "ChatClient.h"
#include "EncodingTool.h"

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
		closesocket(this->socketClient);
		cout << "connect failed!";
	}
	else
	{
		cout << "connect success!";
	}
}

void ChatClient::SendMsg(LPCTSTR msg)
{
	send(this->socketClient, EncodingTool::WideCharToMultiChar(msg), _tcslen(msg), 0);
}