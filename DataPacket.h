#pragma once
//#include <stdafx.h>
//#include <stdio.h>			//standard input output -> printf 같은거 쓸때? 기본적인 함수들이 포함됨
//#include <iostream>			//cin -> 키보드 입력을 받아오기 위해 사용하는 변수			//getline(cin, sbuf);-> cin으로 문자열 받아와서 sbuf에 저장
//#include <ws2tcpip.h>		//주소 구조체가 정의되어있음. IP, Port등을 저장하는 구조체	//WSADATA, SOCKADDR_IN 등...
//#include <string>			//string 쓰려면 선언
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

	static CDataPacket *getInstance() //포인터 값을 리턴해주는 함수
	{
		if (c_Instance == NULL) // 포인터가 NULL일 경우
		{
			c_Instance = new CDataPacket(); // 동적 할당 후 포인터에 저장
		}

		return c_Instance; //포인터 리턴
	};

	void SendMessageClear();
	void RecvMessageClear();
};