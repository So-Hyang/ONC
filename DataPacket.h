#pragma once
//#include <stdafx.h>
//#include <stdio.h>			//standard input output -> printf ������ ����? �⺻���� �Լ����� ���Ե�
//#include <iostream>			//cin -> Ű���� �Է��� �޾ƿ��� ���� ����ϴ� ����			//getline(cin, sbuf);-> cin���� ���ڿ� �޾ƿͼ� sbuf�� ����
//#include <ws2tcpip.h>		//�ּ� ����ü�� ���ǵǾ�����. IP, Port���� �����ϴ� ����ü	//WSADATA, SOCKADDR_IN ��...
//#include <string>			//string ������ ����
//#include <windows.h>
//#include <process.h>
//#pragma comment(lib, "ws2_32.lib")
//#include <vector>
//#include <algorithm>
//#include <sstream>
//using namespace std;

#include <string>
#include <ws2tcpip.h>
//#include <windows.h>

using namespace std;

#define NAME_SIZE 50
#define BUF_SIZE 300
#define MAX_CLENT 3

#define CalendarPublicPacket 1
#define CalendarPrivatePacket 2
#define NoicePacket 3
#define ChattingPacket 4
#define TopicEnterPacket 5
#define TopicLeavePacket 6
#define TopicParticipantPacket 7
#define EmergencyPacket 8
#define PasswordPacket 9
#define AllTopicTitlePAcket 10

//#define SERVERMODE
#define CLIENTMODE



struct SendPacket
{
	SOCKET ClientSock;
};

struct DataPacket
{
	unsigned int nType;
	
	string TopicTitle;
	string cUserID;
	string cMsg;
	string cDate;
	string cPassWord;
	string cSenderID;
	string Participants;
	string AllTopicTitle;
	bool PubPrivate= false;
};

class CDataPacket
{
private : 
	static CDataPacket *c_Instance;
public:
	DataPacket RecverMessage, RecvMessage, SenderMessage;
	SendPacket ClientSocket, ServerSocket;

	static CDataPacket *getInstance() //������ ���� �������ִ� �Լ�
	{
		if (c_Instance == NULL) // �����Ͱ� NULL�� ���
		{
			c_Instance = new CDataPacket(); // ���� �Ҵ� �� �����Ϳ� ����
		}

		return c_Instance; //������ ����
	};

	void SendMessageClear();
	void RecvMessageClear();
};