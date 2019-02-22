#include "ServerDataManager.h"


/*Ŭ������ : ServerDataManager****************************************************/
/*�������� : 2019_02_13*******************************************************/
/*��������� : �ڼ�ȭ**********************************************************/
/*�������� : input���� TopicTitle �Է� �� �ش� user�� ID ���****************************/
//public
//ServerDataManager* ServerDataManager::getInstance;

ServerDataManager* ServerDataManager::m_Instance = NULL;

void ServerDataManager::InputInfo()
{
	string finish;

	{
		while (finish != "����")
		{
			cout << "�������� ���Ḧ �Է��ϼ���: " << endl;
			cin >> finish;
			//DM���� x -> ������ Ű���尪 ��ü
			cout << "ID���� �Է��ϼ���: " << endl;
			cin >> user_ID;
			a.m_ID = user_ID;
			cout << "IP���� �Է��ϼ���: " << endl;
			cin >> user_IP;
			a.m_IP = user_IP;
			//cout << "Socket���� �Է��ϼ���: " << endl;
			//cin >> user_SocketValue;
			a.m_SocketValue = NULL;
			a.m_TopicTitle = "NSL;�ѱ���;DDS;";


			vecUserInfo.push_back(a);
		}
	}

	return;
}

/*�������� : Ű���� ������ ������ �޾ƿ��� -> input���� ������ �޾ƿ���****************************/

int ServerDataManager::SearchInfo(string m_IP, string m_ID, int m_socketValue)
{
	//cin >> user_ID; //Ű���� �� ����
	
	int find_index = -1;
	user_ID = m_ID;
	user_IP = m_IP;
	user_SocketValue = m_socketValue;

	if (user_ID != "")
	{
		for (int i = 0; i < vecUserInfo.size(); i++)
		{
			if (user_ID == vecUserInfo[i].m_ID)
			{
				printf("%d", i);
				find_index = i;
			}
		}
	}
	if (user_IP != "")
	{
		for (int i = 0; i < vecUserInfo.size(); i++)
		{
			if (user_IP == vecUserInfo[i].m_IP)
			{
				printf("%d", i);
				find_index = i;
			}
		}

	}
	if (user_SocketValue != NULL)
	{
		for (int i = 0; i < vecUserInfo.size(); i++)
		{
			if (user_SocketValue == vecUserInfo[i].m_SocketValue)
			{
				printf("%d", i);
				find_index = i;
			}
		}
	}

	return find_index;
}

//void ServerDataManager::ClientSockInput(SOCKET aa)
//{
//	ClientSock = aa;
//}

void ServerDataManager::InsertInfo(int m_socketValue, string m_TopicTItle, int find_index)
{
	string Add_TopciTitle;
	user_SocketValue = m_socketValue;
	m_TopicTItle = user_TopicTitle;
	//cin >> user_SocketValue;

		if (user_SocketValue != NULL)
		{
			vecUserInfo.at(find_index).m_SocketValue = user_SocketValue;
			printf("%d", vecUserInfo[find_index].m_SocketValue);
		}

	//cin >> user_TopicTitle; 
	
		else if (user_TopicTitle != "") // TopicTitlte�� NULL ���� �ƴ϶��
		{
			Add_TopciTitle = vecUserInfo[find_index].m_TopicTitle + user_TopicTitle; 
			vecUserInfo.at(find_index).m_TopicTitle = Add_TopciTitle; 
			cout << vecUserInfo.at(find_index).m_TopicTitle << endl;
		
		}
	return;
}

void ServerDataManager::DeleteInfo(int m_socketValue, string m_TopicTitle, int find_index)
{
	string newTitle;
	string split = ";";
	user_SocketValue = m_socketValue;
	m_TopicTitle = user_TopicTitle;
	//cin >> user_TopicTitle;

	if (user_SocketValue != NULL)
	{
		vecUserInfo.at(find_index).m_SocketValue = NULL;
		printf("%d", vecUserInfo[find_index].m_SocketValue);
	}

	else if (user_TopicTitle != "")
	{
		istringstream DeleteTopicTitle(vecUserInfo[find_index].m_TopicTitle);
		while (getline(DeleteTopicTitle, token, ';'))  // �����ݷ��� �������� DeleteTopicTitle�� ������ TopicTitle �и��Ͽ� token�� ����
		{
			if (user_TopicTitle.compare(token) != 0)  // input���� ���� user_TopicTitle�� token�� ���� ������ 
				newTitle += (token + split); // newTitle�� token�� �����ݷ� ��ӿ��� �����ֱ�
		}
		vecUserInfo.at(find_index).m_TopicTitle = newTitle; //�ش� ��ġ�� TopicTitle�� newTitle������ �ٲ��ֱ�
		printf("%s", newTitle);
	}

	return;
}

int ServerDataManager::FindSocketValue(string m_TopicTitle, string m_userID, int Count, int find_index)
{
	 user_TopicTitle = m_TopicTitle;
	user_ID = m_userID ;
	//cin >> user_TopicTitle;
	if (user_TopicTitle != "")
	{//for (int count = 0; count<vecUserInfo.size(); count++)
		if (Count < vecUserInfo.size())
		{
			istringstream iss(vecUserInfo[Count].m_TopicTitle);
			//while (getline(iss, token, ';'))
			//{
				//if (user_TopicTitle.compare(token) == 0)
				//{
				//	printf("�ش� ���ȿ� �ִ� ���ϰ� : %d\n", vecUserInfo.at(Count).m_SocketValue);
				//}
			//}

			return vecUserInfo.at(Count).m_SocketValue;
		}
		else if (Count > vecUserInfo.size())
		{
			return -1;
		}
	}
	else if (user_ID != "")
	{
		return vecUserInfo.at(find_index).m_SocketValue;
	}


}




string ServerDataManager::FindUserID(string m_TopicTitle, int Count)
{
	//cin >> user_TopicTitle;
	m_TopicTitle = user_TopicTitle;
	string wrongvalue;
	if (Count <= vecUserInfo.size())
	{
		istringstream iss(vecUserInfo[Count].m_TopicTitle);
		while (getline(iss, token, ';')) 
		{
			if (user_TopicTitle.compare(token) == 0)
			{
				printf("�ش� ���ȿ� �ִ� ���ϰ� : %d\n", vecUserInfo.at(Count).m_ID);
			}
		}

		return vecUserInfo.at(Count).m_ID;
	}

	else if (Count > vecUserInfo.size())
	{
		return wrongvalue = "find fail";
	}

}
