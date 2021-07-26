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

int RequesterSocket::queryWord(const std::string word, std::string &def)
{
	char buf[4096];
	int sendResult;
	int bytesReceived;
	if (word.size() > 0)
	{
		sendResult = send(sock_, word.c_str(), int(word.size()) + 1, 0);
		if (sendResult != SOCKET_ERROR)
		{
			ZeroMemory(buf, 4096);
			bytesReceived = recv(sock_, buf, 4096, 0);
			if (bytesReceived > 0)
			{
				def = std::string(buf, 0, bytesReceived); 
				//std::cout << "SERVER> " << def << std::endl; 
				if (def == "None")
				{
					return 0;
				}
				return 1; 
			}
			else
			{
				std::cout << "Nothing received from server" << std::endl;
				return 0; 
			}
		}
		else
		{
			std::cout << "Send not successful, Err #" << WSAGetLastError() << std::endl;
			return sendResult;
		}
	}
	else
	{
		std::cout << "Word size must be > 0" << std::endl;
		return SOCKET_ERROR; 
	}
}