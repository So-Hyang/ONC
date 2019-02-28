#include "Connect.h"

/*클래스명 : Connect**********************************************************/
/*수정일자 : 2019_02_07*******************************************************/
/*수정담당자 : 김경선**********************************************************/
/*수정사항 : 서버 소켓 Bind하기************************************************/
SOCKET Connect::Bind()
{
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)			//윈속 초기화
	{
		fputs("WSAStartup() error\n", stderr);				//애러 표시
		exit(1);												//종료
	}

	ServerSock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);	//소켓 생성

	if (ServerSock == INVALID_SOCKET)							//생성된 소켓 확인
	{
		printf("iTCPsendSock is Invalid\n");					//애러 표시
		exit(1);												//종료
	}

	memset(&ServerAddr, 0, sizeof(ServerAddr));				//임의의 소켓주소값 초기화
	ServerAddr.sin_family = AF_INET;							//IPv4 인터넷 프로토롤
	ServerAddr.sin_addr.s_addr = htonl(INADDR_ANY);			//32bit IPV4 주소
	ServerAddr.sin_port = htons(3);						//사용할 포트번호 ex) 60000

	if (bind(ServerSock, (SOCKADDR*)&ServerAddr, sizeof(ServerAddr)) == -1)	//생성한 소켓과 입력한 소켓주소값을 bind 하기
	{
		printf("Bind Failed\n");	//애러 표시
		//exit(1);																//종료
	}	
	else
	{
		printf("Bind Success\n");
	}

	if (listen(ServerSock, 5) == -1)											//listen 상태
	{
		printf("TCP Listen Error\n");											//애러 표시
		//exit(1);																//종료
	}
	else
	{
		printf("Listen Status\n");
	}
	return ServerSock;
}

/*클래스명 : Connect**********************************************************/
/*수정일자 : 2019_02_07*******************************************************/
/*수정담당자 : 김경선**********************************************************/
/*수정사항 : 클라이언트 Accept하기(쓰레드 제거)**********************************/
void Connect::Con(SOCKET ServerSock)
{
	TempStruct.StructServerSocket = ServerSock;
	ConThread = (HANDLE)_beginthreadex(NULL, 0, Accept, (void*)&TempStruct, 0, NULL);										//입력으로 들어온 서버소켓 정보를 ServerSock에 담는다
	//return ServerSock;
}

unsigned WINAPI Connect::Accept(void* arg)
{
	int count = 0;
	SOCKADDR_IN ClientAddr;
	int Addrsize;
	Addrsize = sizeof(ClientAddr);
	Temp ServerSocket = *((Temp*)arg);
	SOCKET ClientSock, ServerSockets;
	ServerSockets = ServerSocket.StructServerSocket;
	string LoadTopicTitle;
	ifstream ReadTopicTitle("C:\\Users\\user\\Desktop\\Topic.txt");
	while (1)
	{

		if ((ClientSock = accept(ServerSockets, (SOCKADDR*)&ClientAddr, &Addrsize)) == -1)
		{
			printf("Accept Fail");
		}		//accept해서 얻은 클라이언트 소켓값을 ClientSock에 저장한다
		else
		{
			string ret = inet_ntoa(ClientAddr.sin_addr);
			cout << "server : got connection from Client :" << ret;
			int a = ServerDataManager::getInstance()->SearchInfo(ret, "", NULL);
			ServerDataManager::getInstance()->InsertInfo(ClientSock, "", a);
			cout << ServerDataManager::getInstance()->vecUserInfo[a].m_SocketValue << endl;
			printf("Connect with Client\n");
			if (ReadTopicTitle.is_open())
			{
				ReadTopicTitle >> LoadTopicTitle;
			}
			//CDataPacket::getInstance()->SenderMessage.AllTopicTitle = LoadTopicTitle;
			int Topiclen = sizeof(CDataPacket::getInstance()->SenderMessage);
			send(CDataPacket::getInstance()->ClientSocket.ClientSock, (char *)&CDataPacket::getInstance()->SenderMessage, Topiclen, 0);

			//	i = ServerDataManager::GetInstance()->SearchInfo(ClientAddr.IP, NULL);	//클라이언트의 IP를 사용하여 몇번째에 위치한 유저인지 파악
			//	ServerDataManager::GetInstance()->InsertInfo(ClientSock, NULL, i);		//ServerDataManager에 있는 InsertInfo함수를 사용하여 클라이언트 소켓값을 저장한다.
		
			
				ServerDataManager::getInstance()->NewClientSock = ServerDataManager::getInstance()->vecUserInfo[a].m_SocketValue;
				
		
			//ServerDataManager::getInstance()->enterflag = 1;
			//return ServerDataManager::getInstance()->ClientSock;
			//return  ServerDataManager::getInstance()->ClientSock;
		}
	}
	
}

 
SOCKET Connect::ConnectWithServer()
{
	WSADATA ClientData;


	if (WSAStartup(MAKEWORD(2, 2), &ClientData) != 0)
	{
		exit(1);
	}
	ClientScoket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (ClientScoket == INVALID_SOCKET)
	{
		exit(1);
	}
	memset(&ClientSock, 0, sizeof(ClientSock));
	ClientSock.sin_family = AF_INET;
	ClientSock.sin_addr.s_addr = inet_addr("192.168.208.78");
	ClientSock.sin_port = htons(3);
	connect(ClientScoket, (struct sockaddr*)&ClientSock, sizeof(ClientSock));

	return ClientScoket;
}

//void Connect::ConnectThread(SOCKET ServerSocket)											//서버의 소켓값 => Bind()함수의 반환값
//{
	//ConThread = (HANDLE)_beginthreadex(NULL, 0, Con, (void*)&ServerSocket, 0, NULL);		//스레드로 Con 함수 발생
//}