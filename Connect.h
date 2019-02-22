#pragma once
//#include "PacketManager.h" 

#include "ServerDataManager.h"
#include "DataPacket.h"
//#include <windows.h>
#include <ws2tcpip.h>
#include <process.h>
#include <stdio.h>
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <cstring>

#pragma comment(lib, "ws2_32.lib")

using namespace std;

static struct Temp
{
	SOCKET StructServerSocket;
}TempStruct;

class Connect
{
public:
	WSADATA wsaData;
	SOCKET ServerSock;
	SOCKADDR_IN ServerAddr;
	HANDLE ConThread;
	SOCKADDR_IN ClientAddr;
	SOCKET Bind();
	void Con(SOCKET ServerSock);
	static unsigned WINAPI Accept(void* arg);
	SOCKET ConnectWithServer();
	//void ConnectThread(SOCKET ServerSocket);

};
