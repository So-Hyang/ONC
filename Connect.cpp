#include "Connect.h"

/*Ŭ������ : Connect**********************************************************/
/*�������� : 2019_02_07*******************************************************/
/*��������� : ��漱**********************************************************/
/*�������� : ���� ���� Bind�ϱ�************************************************/
SOCKET Connect::Bind()
{
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)			//���� �ʱ�ȭ
	{
		fputs("WSAStartup() error\n", stderr);				//�ַ� ǥ��
		exit(1);												//����
	}

	ServerSock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);	//���� ����

	if (ServerSock == INVALID_SOCKET)							//������ ���� Ȯ��
	{
		printf("iTCPsendSock is Invalid\n");					//�ַ� ǥ��
		exit(1);												//����
	}

	memset(&ServerAddr, 0, sizeof(ServerAddr));				//������ �����ּҰ� �ʱ�ȭ
	ServerAddr.sin_family = AF_INET;							//IPv4 ���ͳ� �������
	ServerAddr.sin_addr.s_addr = htonl(INADDR_ANY);			//32bit IPV4 �ּ�
	ServerAddr.sin_port = htons(3);						//����� ��Ʈ��ȣ ex) 60000

	if (bind(ServerSock, (SOCKADDR*)&ServerAddr, sizeof(ServerAddr)) == -1)	//������ ���ϰ� �Է��� �����ּҰ��� bind �ϱ�
	{
		printf("Bind Failed\n");	//�ַ� ǥ��
		//exit(1);																//����
	}	
	else
	{
		printf("Bind Success\n");
	}

	if (listen(ServerSock, 5) == -1)											//listen ����
	{
		printf("TCP Listen Error\n");											//�ַ� ǥ��
		//exit(1);																//����
	}
	else
	{
		printf("Listen Status\n");
	}
	return ServerSock;
}

/*Ŭ������ : Connect**********************************************************/
/*�������� : 2019_02_07*******************************************************/
/*��������� : ��漱**********************************************************/
/*�������� : Ŭ���̾�Ʈ Accept�ϱ�(������ ����)**********************************/
void Connect::Con(SOCKET ServerSock)
{
	TempStruct.StructServerSocket = ServerSock;
	ConThread = (HANDLE)_beginthreadex(NULL, 0, Accept, (void*)&TempStruct, 0, NULL);										//�Է����� ���� �������� ������ ServerSock�� ��´�
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
		}		//accept�ؼ� ���� Ŭ���̾�Ʈ ���ϰ��� ClientSock�� �����Ѵ�
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

			//	i = ServerDataManager::GetInstance()->SearchInfo(ClientAddr.IP, NULL);	//Ŭ���̾�Ʈ�� IP�� ����Ͽ� ���°�� ��ġ�� �������� �ľ�
			//	ServerDataManager::GetInstance()->InsertInfo(ClientSock, NULL, i);		//ServerDataManager�� �ִ� InsertInfo�Լ��� ����Ͽ� Ŭ���̾�Ʈ ���ϰ��� �����Ѵ�.
		
			
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

//void Connect::ConnectThread(SOCKET ServerSocket)											//������ ���ϰ� => Bind()�Լ��� ��ȯ��
//{
	//ConThread = (HANDLE)_beginthreadex(NULL, 0, Con, (void*)&ServerSocket, 0, NULL);		//������� Con �Լ� �߻�
//}