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



static struct SendPacket
{
	SOCKET ClientSock;
} ClientSocket;

static struct DataPacket
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
	static DataPacket RecverMessage, RecvMessage, SenderMessage;
	static SendPacket ClientSocket, ServerSocket;

	static CDataPacket *getInstance() //������ ���� �������ִ� �Լ�
	{
		if (c_Instance == NULL) // �����Ͱ� NULL�� ���
		{
			c_Instance = new CDataPacket(); // ���� �Ҵ� �� �����Ϳ� ����
		}

		return c_Instance; //������ ����
	};

	void SendMessageClear()
	{
		this->SenderMessage.nType = 0;
		this->SenderMessage.TopicTitle = "";
		this->SenderMessage.cUserID = "";
		this->SenderMessage.cMsg = "";
		this->SenderMessage.cDate = "";
		this->SenderMessage.cPassWord = "";
		this->SenderMessage.cSenderID = "";
		this->SenderMessage.Participants = "";
		this->SenderMessage.AllTopicTitle = "";
		this->SenderMessage.PubPrivate = false;
	};
	void RecvMessageClear()
	{
		this->RecverMessage.nType = 0;
		this->RecverMessage.TopicTitle = "";
		this->RecverMessage.cUserID = "";
		this->RecverMessage.cMsg = "";
		this->RecverMessage.cDate = "";
		this->RecverMessage.cPassWord = "";
		this->RecverMessage.cSenderID = "";
		this->RecverMessage.Participants = "";
		this->RecverMessage.AllTopicTitle = "";
		this->RecverMessage.PubPrivate = false;


		this->RecvMessage.nType = 0;
		this->RecvMessage.TopicTitle = "";
		this->RecvMessage.cUserID = "";
		this->RecvMessage.cMsg = "";
		this->RecvMessage.cDate = "";
		this->RecvMessage.cPassWord = "";
		this->RecvMessage.cSenderID = "";
		this->RecvMessage.Participants = "";
		this->RecvMessage.AllTopicTitle = "";
		this->RecvMessage.PubPrivate = false;
	};
};