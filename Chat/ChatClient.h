#ifndef CHATCLIENT_H
#define CHATCLIENT_H

#include <winsock2.h>
#include <iostream>
#pragma comment(lib,"ws2_32.lib")

using namespace std;

class ChatClient
{
public:
	ChatClient();
	void Connect(LPCTSTR addr, int port);
	void SendMessage(LPCTSTR msg);

private:
	SOCKET socketClient;
};


#endif