#include "SendRecv.h"

/*Ŭ������ : SendRecv**********************************************************/
/*�������� : 2019_02_07*******************************************************/
/*��������� : ��漱**********************************************************/
/*�������� : Send�Լ� Recv�Լ� ����************************************************/


CDataPacket* CDataPacket::c_Instance = NULL;

DataPacket CDataPacket::RecverMessage;
DataPacket CDataPacket::RecvMessage;
DataPacket CDataPacket::SenderMessage;
SendPacket CDataPacket::ClientSocket;


void SendRecv::RecvThread(SOCKET cSock)
{
	//Send_Packet ClientSocket;
	CDataPacket::getInstance()->ClientSocket.ClientSock = cSock;
	MSGThread = (HANDLE)_beginthreadex(NULL, 0, Recv, (void*)&CDataPacket::getInstance()->ClientSocket, 0, NULL);			//������� Recv �Լ� �߻�

}

unsigned WINAPI SendRecv::Recv(void* arg)
{
	ClientSocket = *(SendPacket *)arg;						//�Է����� ���� Ŭ���̾�Ʈ ���� �迭�� ���� �迭 ���·� �����Ѵ�.
	
	while ((recv(ClientSocket.ClientSock, (char*)&CDataPacket::getInstance()->RecverMessage, sizeof(CDataPacket::getInstance()->RecverMessage), 0)) != -1)
	{
		memcpy(&CDataPacket::getInstance()->RecvMessage, &CDataPacket::getInstance()->RecverMessage, sizeof(CDataPacket::getInstance()->RecvMessage));
		cout << CDataPacket::getInstance()->RecvMessage.cMsg << endl;
	}
	
	#ifdef SERVERMODE
	
	int a = ServerDataManager::getInstance()->SearchInfo("", "", ClientSocket.ClientSock);
	ServerDataManager::getInstance()->DeleteInfo(ClientSocket.ClientSock, "", a);
	cout << ServerDataManager::getInstance()->vecUserInfo[a].m_SocketValue << endl;

	#endif

	return 0;
}

void SendRecv::Send(DataPacket SenderMessage, int SocketValue)	//�޼���, ������ Ŭ���̾�Ʈ ���ϰ�
{
	int len = sizeof(SenderMessage);								//���� ��Ŷ ũ�� ����
	send(SocketValue, (char *)&SenderMessage, len, 0);						//��Ŷ ������
}


