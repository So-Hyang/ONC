#include "SendRecv.h"

/*클래스명 : SendRecv**********************************************************/
/*수정일자 : 2019_02_07*******************************************************/
/*수정담당자 : 김경선**********************************************************/
/*수정사항 : Send함수 Recv함수 정의************************************************/

void SendRecv::RecvThread(SOCKET cSock)
{

	//Send_Packet ClientSocket;
	CDataPacket::getInstance()->ClientSocket.ClientSock = cSock;
	MSGThread = (HANDLE)_beginthreadex(NULL, 0, Recv, (void*)&CDataPacket::getInstance()->ClientSocket, 0, NULL);			//스레드로 Recv 함수 발생

}

unsigned WINAPI SendRecv::Recv(void* arg)
{
	int i=0;
	PacketManager Analysis;
	SendPacket ClientSocket;
	ClientSocket = *(SendPacket *)arg;						//입력으로 들어온 클라이언트 소켓 배열을 소켓 배열 형태로 저장한다.
	
	while (i=(recv(ClientSocket.ClientSock, (char*)&CDataPacket::getInstance()->RecverMessage, sizeof(CDataPacket::getInstance()->RecverMessage), 0)) != -1)
	{
		memcpy(&CDataPacket::getInstance()->RecvMessage, &CDataPacket::getInstance()->RecverMessage, sizeof(CDataPacket::getInstance()->RecvMessage));
	
		#ifdef CLIENTMODE
			
			Analysis.PacketAnalysis(CDataPacket::getInstance()->RecvMessage);

		#endif

	}
	
	#ifdef SERVERMODE
	
	int a = ServerDataManager::getInstance()->SearchInfo("", "", ClientSocket.ClientSock);
	ServerDataManager::getInstance()->DeleteInfo(ClientSocket.ClientSock, "", a);
	cout << ServerDataManager::getInstance()->vecUserInfo[a].m_SocketValue << endl;

	#endif




	return 0;
}

int SendRecv::Send(DataPacket SenderMessage, int SocketValue)	//메세지, 보내는 클라이언트 소켓값
{
	int len = sizeof(SenderMessage);								//받은 패킷 크기 저장
	return send(SocketValue, (char *)&SenderMessage, len, 0);						//패킷 보내기
}


