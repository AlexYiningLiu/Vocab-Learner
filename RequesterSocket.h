#pragma once

#include <WS2tcpip.h>
#include <string>
#include <iostream>

#pragma comment(lib, "Ws2_32.lib")

class RequesterSocket
{
public:
	RequesterSocket(int port, std::string ipAddress);
	int connectToServer();

private:
	int port_;
	std::string ipAddress_;
	WSADATA data_;
	WORD ver_;
	SOCKET sock_; 
	sockaddr_in hint_; 
	int connect_result_;
	int wsResult_;
	int initializeWinSock();
	int createSocket();
	void fillHint();
};

