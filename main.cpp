#pragma once
#include "Connect.h"
#include "Interface.h"
#include "DataPacket.h"
#include "SendRecv.h"
#include "PacketManager.h"

void main()
{
	SOCKET PreviousClent;
	SOCKET NewClient;
	SOCKET SeverSock;
	//SOCKET bufClientSock = -1;
	//ServerDataManager::getInstance()->ClientSock = -1;
	Connect Main_Start;
	SendRecv Recieve;
	PacketManager ReadyPacket;

	printf("                ***********************************************************************************\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
	printf("                ***********************************************************************************\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
	printf("                ***********************************************************************************\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);
	printf("                ***********************************************************************************\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
	printf("                ***********************************************************************************\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
	printf("                ***********************************************************************************\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
	printf("                ***********************************************************************************\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 5);
	printf("                ***********************************************************************************\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
	printf("                ************************* ONC (Only NSL Chatting) SERVER **************************\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	printf("                ********************************** 202.31.137.39 **********************************\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
	printf("                ************************ Made by NSL(Networked System Lab.) ***********************\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
	printf("                ***********************************************************************************\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	printf("                ***********************************************************************************\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);
	printf("                ***********************************************************************************\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
	printf("                ***********************************************************************************\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
	printf("                ***********************************************************************************\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	printf("                ***********************************************************************************\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13);
	printf("                ***********************************************************************************\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
	printf("                ***********************************************************************************\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	SeverSock = Main_Start.Bind();

	ServerDataManager::getInstance()->InputInfo();
	Main_Start.Con(SeverSock);
	while (1)
	{
		if (ServerDataManager::getInstance()->NewClientSock != ServerDataManager::getInstance()->PreviousClientSock)
		{
			Recieve.RecvThread(ServerDataManager::getInstance()->NewClientSock);
			ServerDataManager::getInstance()->PreviousClientSock = ServerDataManager::getInstance()->NewClientSock;
			 
		}
		//if (ServerDataManager::getInstance()->ClientSock != bufClientSock)
		//{
		//	//ServerDataManager::getInstance()->enterflag = 0;
		//	Recieve.RecvThread(ServerDataManager::getInstance()->ClientSock);
		//}
		
		//if (ServerDataManager::getInstance()->ClientSock != bufClientSock)
		//{
		//	Recieve.RecvThread(ServerDataManager::getInstance()->ClientSock);
		//}
			
			/*ClientSock = */
		
		if (CDataPacket::getInstance()->RecvMessage.nType != 0)
		{
			ReadyPacket.PacketAnalysis(CDataPacket::getInstance()->RecvMessage);
		}
		if (CDataPacket::getInstance()->SenderMessage.nType != 0)
		{
			ReadyPacket.PacketCreater(CDataPacket::getInstance()->SenderMessage);
		}
		
		//ServerDataManager::getInstance()->ClientSock = bufClientSock ;

	}

	//사용자가 접속할경우 txt파일에 저장해놓은 TopicTitle전송
	//data.InsertInfo(user_SocketValue, user_IP, find_index);
	//data.FindSocketValue(user_TopicTitle, find_index);
	
}