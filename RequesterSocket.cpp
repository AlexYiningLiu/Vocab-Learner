#include "RequesterSocket.h"

RequesterSocket::RequesterSocket(int port, std::string ipAddress) 
{
	ipAddress_ = ipAddress;
	port_ = port;
	if (initializeWinSock() != 0)
	{
		if (createSocket() != 0)
		{
			fillHint();
		}
	}
}

int RequesterSocket::initializeWinSock() 
{
	ver_ = MAKEWORD(2, 2);
	wsResult_ = WSAStartup(ver_, &data_);
	if (wsResult_ != 0) 
	{
		std::cerr << "Can't start winsock, Err #" << wsResult_ << std::endl;
		return 0; 
	}
	else 
	{
		return 1; 
	}
}

int RequesterSocket::createSocket()
{
	sock_ = socket(AF_INET, SOCK_STREAM, 0);
	if (sock_ == INVALID_SOCKET)
	{
		std::cerr << "Can't create socket, Err #" << WSAGetLastError() << std::endl; 
		WSACleanup();
		return 0;
	}
	else
	{
		return 1; 
	}
}

void RequesterSocket::fillHint()
{
	hint_.sin_family = AF_INET;
	hint_.sin_port = htons(port_); 
	inet_pton(AF_INET, ipAddress_.c_str(), &hint_.sin_addr);
}

int RequesterSocket::connectToServer()
{
	connect_result_ = connect(sock_, (sockaddr*)&hint_, sizeof(hint_));
	if (connect_result_ == SOCKET_ERROR)
	{
		std::cerr << "Can't connect to server, Err #" << WSAGetLastError() << std::endl; 
		closesocket(sock_);
		WSACleanup();
		return 0;
	}
	else
	{
		return 1; 
	}
}