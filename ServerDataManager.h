#pragma once
//#include "DataPacket.h"
//#include "afxwin.h"
#include "stdafx.h"

#include <sstream>
#include <iostream>
#include <vector>
#include <string>
#include <ws2tcpip.h>

#pragma comment(lib, "ws2_32.lib")

using namespace std;


class ServerDataManager
{
private:
	ServerDataManager() {};
	~ServerDataManager() {};

	static ServerDataManager *m_Instance;   // 객체를 하나 밖에 생성시키지 못하게 하려고 생성자 은닉
											// 은닉시키면 포인터로 밖에 접근 불가능 + 다른곳에서도 사용하기 위해 static 필요
											// 레퍼런스(&)로 접근시 본인의 주소가 복사된 메모리를 리턴, 포인터로 접근시 본인을 리턴
public:
	SOCKET NewClientSock;
	SOCKET PreviousClientSock;//vector<UserInfo>::iterator vec_iter; //반복자 선언
	int enterflag = 0;
	string user_IP, user_ID, user_TopicTitle;
	int user_SocketValue;
	string token;
	//SOCKET aa;
	static ServerDataManager *getInstance() //포인터 값을 리턴해주는 함수
	{
		if (m_Instance == NULL) // 포인터가 NULL일 경우
		{
			m_Instance = new ServerDataManager(); // 동적 할당 후 포인터에 저장
		}

		return m_Instance; //포인터 리턴
	};

	struct UserInfo
	{
		string m_IP;
		string m_ID;
		int m_SocketValue;
		string m_TopicTitle;
	};

	UserInfo a;
	vector<UserInfo> vecUserInfo; //UserInfo 구조체를 저장하는 vector 선언

	//void ClientSockInput(SOCKET aa);
	void InputInfo();
	void InsertInfo(int m_socketValue, string m_TopicTItle, int i);
	void DeleteInfo(int m_socketValue, string m_TopicTitle, int i);
	int SearchInfo(string m_IP, string m_ID, int m_socktValue);
	void ClientRenewal(SOCKET ClientSock);
	int FindSocketValue(string m_TopicTitle, string m_userID, int Count, int find_index);
	string FindUserID(string m_TopicTitle, int Count);

	
};

