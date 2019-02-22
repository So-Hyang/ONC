#pragma once
//#include "Connect.h"
#include "stdafx.h"
#include "SendRecv.h"
#include "Connect.h"
#include "DataPacket.h"

#include <string>
//#include <windows.h>
#include <ws2tcpip.h>

#pragma comment(lib, "ws2_32.lib")

using namespace std;

class GuiClientInterface
{
public :
	static CDataPacket *i_Instance;
	static CDataPacket *getInstance() //������ ���� �������ִ� �Լ�
	{
		if (i_Instance == NULL) // �����Ͱ� NULL�� ���
		{
			i_Instance = new CDataPacket(); // ���� �Ҵ� �� �����Ϳ� ����
		}

		return i_Instance; //������ ����
	};
	SOCKET ConnectServerSocket;
	SendRecv ClientRecv;
	Connect ConnectStart;
	SendRecv Sender;
	void OnChatMessage(   string TopicTitle, string cUserID, string cMsg);
	void OnNoticeMessage(   string UserID, string cMsg);
	void OnCalendarMessage( string UserID, string cMsg, string cDate);
	void OnEmergencyAramMessage( string cUserID, string cMsg);
	void OnTopicParticipantMessage( string cUserID, string TopicTitle, string Participants);
	void OnAllTopicTitleMessage(string AllTopicTitle);
	void SendChatMessage(unsigned int nType, string TopicTitle, string cUserID, string cMsg);
	void SendNoticeMessage(unsigned int nType, string cUserID, string cMsg, string cDate);
	void SendCalendarPublicMessage(unsigned int nType, string cUserID, string cMsg, string cDate, bool PubPrivate);
	void SendCalendarPrivateMessage(unsigned int nType, string cUserID, string cMsg, string cDate, bool PubPrivate);
	void SendTopicEnterMessage(unsigned int nType, string cUserID, string TopicTitle);
	void SendTopicLeaveMessage(unsigned int nType, string cUserID, string TopicTitle);
	void SendEmergencyAramMessage(unsigned int nType, string cUserID, string cMsg);
	void SendTopicParticipantMessage(unsigned int nType, string cUserID, string TopicTitle);
	void ConncetWithServer();
	void DisConnecttion(SOCKET ServerSock);
};