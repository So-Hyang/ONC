#pragma once

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

#ifdef CLIENTMODE
#include "PacketManager.h"
#endif

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
	int Send(DataPacket SenderMessage, int SocketValue);
};

//CDataPacket* CDataPacket::c_Instance = NULL;