#pragma comment(lib, "ws2_32.lib")
#include <WinSock2.h>
#include <iostream>

#pragma warning(disable: 4996)

using namespace std;

int main(int argc, char* argv[])
{
	//WSAStartup, CONNECT WSA LIBRARY
	WSAData wsaData;
	WORD DLLVersion = MAKEWORD(2, 1);
	if (WSAStartup(DLLVersion, &wsaData) != 0)
	{
		cout << "Error! Can't load WSA Library!" << endl;
		exit(1);
	}

	SOCKADDR_IN addr;
	int sizeOfAddr = sizeof(addr);
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	addr.sin_port = htons(1111);
	addr.sin_family = AF_INET;
	 
	SOCKET sListen = socket(AF_INET, SOCK_STREAM, NULL);

	bind(sListen, (SOCKADDR*)&addr, sizeof(addr));

	//SOMAXCONN - max requests to connect
	listen(sListen, SOMAXCONN);

	SOCKET NewConnection;
	NewConnection = accept(sListen, (SOCKADDR*)&addr, &sizeOfAddr);

	if (NewConnection == 0)
	{
		cout << "Connection error!" << endl;
	}
	else
	{
		cout << "Server: Client successfully connected!" << endl;

		//Variable to send message FROM server
		char msg[256] = "Hello. It's my first network program!";
		send(NewConnection, msg, sizeof(msg), NULL);
	}

	system("pause");

	return 0;
}