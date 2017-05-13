#include "ChatClient.h"

ChatClient::ChatClient()
{
}

void ChatClient::Connect(LPCTSTR addr, int port)
{
	WSADATA wsaData;
	SOCKADDR_IN addrServer;// ����˵�ַ
	WSAStartup(MAKEWORD(2, 2), &wsaData);
	// �½��ͻ���socket
	this->socketClient = socket(AF_INET, SOCK_STREAM, 0);
	// ����Ҫ���ӵķ���˵�ַ
	addrServer.sin_addr.S_un.S_addr = inet_addr(addr);
	addrServer.sin_family = AF_INET;
	addrServer.sin_port = htons(port);// ���Ӷ˿�6000
	// ���ӵ������
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

void ChatClient::SendMessage(LPCTSTR msg)
{
	send(this->socketClient, msg, strlen(msg), 0);
}