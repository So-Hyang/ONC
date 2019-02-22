#include "ServerDataManager.h"


/*클래스명 : ServerDataManager****************************************************/
/*수정일자 : 2019_02_13*******************************************************/
/*수정담당자 : 박성화**********************************************************/
/*수정사항 : input으로 TopicTitle 입력 시 해당 user의 ID 출력****************************/
//public
//ServerDataManager* ServerDataManager::getInstance;

ServerDataManager* ServerDataManager::m_Instance = NULL;

void ServerDataManager::InputInfo()
{
	string finish;

	{
		while (finish != "종료")
		{
			cout << "끝내려면 종료를 입력하세요: " << endl;
			cin >> finish;
			//DM구현 x -> 데이터 키보드값 대체
			cout << "ID값을 입력하세요: " << endl;
			cin >> user_ID;
			a.m_ID = user_ID;
			cout << "IP값을 입력하세요: " << endl;
			cin >> user_IP;
			a.m_IP = user_IP;
			//cout << "Socket값을 입력하세요: " << endl;
			//cin >> user_SocketValue;
			a.m_SocketValue = NULL;
			a.m_TopicTitle = "NSL;한국인;DDS;";


			vecUserInfo.push_back(a);
		}
	}

	return;
}

/*수정사항 : 키보드 값으로 데이터 받아오기 -> input으로 데이터 받아오기****************************/

int ServerDataManager::SearchInfo(string m_IP, string m_ID, int m_socketValue)
{
	//cin >> user_ID; //키보드 값 실험
	
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
	
		else if (user_TopicTitle != "") // TopicTitlte이 NULL 값이 아니라면
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
		while (getline(DeleteTopicTitle, token, ';'))  // 세미콜론을 기준으로 DeleteTopicTitle에 복사한 TopicTitle 분리하여 token에 저장
		{
			if (user_TopicTitle.compare(token) != 0)  // input으로 들어온 user_TopicTitle과 token이 같지 않으면 
				newTitle += (token + split); // newTitle에 token과 세미콜론 계속에서 더해주기
		}
		vecUserInfo.at(find_index).m_TopicTitle = newTitle; //해당 위치의 TopicTitle에 newTitle값으로 바꿔주기
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
				//	printf("해당 토픽에 있는 소켓값 : %d\n", vecUserInfo.at(Count).m_SocketValue);
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
				printf("해당 토픽에 있는 소켓값 : %d\n", vecUserInfo.at(Count).m_ID);
			}
		}

		return vecUserInfo.at(Count).m_ID;
	}

	else if (Count > vecUserInfo.size())
	{
		return wrongvalue = "find fail";
	}

}
