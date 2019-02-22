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

	static ServerDataManager *m_Instance;   // ��ü�� �ϳ� �ۿ� ������Ű�� ���ϰ� �Ϸ��� ������ ����
											// ���н�Ű�� �����ͷ� �ۿ� ���� �Ұ��� + �ٸ��������� ����ϱ� ���� static �ʿ�
											// ���۷���(&)�� ���ٽ� ������ �ּҰ� ����� �޸𸮸� ����, �����ͷ� ���ٽ� ������ ����
public:
	SOCKET NewClientSock;
	SOCKET PreviousClientSock;//vector<UserInfo>::iterator vec_iter; //�ݺ��� ����
	int enterflag = 0;
	string user_IP, user_ID, user_TopicTitle;
	int user_SocketValue;
	string token;
	//SOCKET aa;
	static ServerDataManager *getInstance() //������ ���� �������ִ� �Լ�
	{
		if (m_Instance == NULL) // �����Ͱ� NULL�� ���
		{
			m_Instance = new ServerDataManager(); // ���� �Ҵ� �� �����Ϳ� ����
		}

		return m_Instance; //������ ����
	};

	struct UserInfo
	{
		string m_IP;
		string m_ID;
		int m_SocketValue;
		string m_TopicTitle;
	};

	UserInfo a;
	vector<UserInfo> vecUserInfo; //UserInfo ����ü�� �����ϴ� vector ����

	//void ClientSockInput(SOCKET aa);
	void InputInfo();
	void InsertInfo(int m_socketValue, string m_TopicTItle, int i);
	void DeleteInfo(int m_socketValue, string m_TopicTitle, int i);
	int SearchInfo(string m_IP, string m_ID, int m_socktValue);
	void ClientRenewal(SOCKET ClientSock);
	int FindSocketValue(string m_TopicTitle, string m_userID, int Count, int find_index);
	string FindUserID(string m_TopicTitle, int Count);

	
};

