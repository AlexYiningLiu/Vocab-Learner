#pragma once

#include <WS2tcpip.h>
#include <string>
#include <iostream>

#pragma comment(lib, "Ws2_32.lib")

class RequesterSocket
{
public:
	RequesterSocket(int port, std::string ipAddress);
	~RequesterSocket() { closesocket(sock_); WSACleanup(); }
	int connectToServer();
	int queryWord(const std::string word, std::string &def);

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

