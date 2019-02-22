#pragma once
//#include "ServerDataManager.h"
//#include "DataPacket.h"
//#include "PacketManager.h"
//#include "DataPacket.h"
//#define BUF_SIZE 200
#include "stdafx.h"
#include "DataPacket.h"
//#include <windows.h>
#include <ws2tcpip.h>
#include <process.h>
#include "ServerDataManager.h"
#include <sstream>
#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

#pragma comment(lib, "ws2_32.lib")

class SendRecv
{
public:
	SOCKET ServerSock, ClientSock;
	SOCKADDR_IN ServerAddr;
	HANDLE MSGThread;
	

	void RecvThread(SOCKET cSock);
	static unsigned WINAPI Recv(void* arg);
	void Send(DataPacket SenderMessage, int SocketValue);
};

//CDataPacket* CDataPacket::c_Instance = NULL;