#include "DataManager.h"
#include <afxsock.h>


/* ½Ì±ÛÅæ »ç¿ëÇÏ±â À§ÇÑ »ı¼ºÀÚ ÇÁ¶óÀÌºø
DataManager::DataManager()
{
}


DataManager::~DataManager()
{
}

*/

bool DataManager::instanceflag = false;
DataManager* DataManager::instance = NULL;

DataManager* DataManager::GetInstance() {
	if (!instance) {
		instance = new DataManager();
		instanceflag = true;
	}
	return instance;
}

bool DataManager::FindMyInfo()
{
	int count;
	string sUserIP;
	sUserIP = GetIpAddress();

	for (count = 0; count<people_v.size(); count++)
	{
		if (sUserIP.compare(people_v[count].IP) == 0)
		{
			myinfo.IP = people_v[count].IP;
			myinfo.Name = people_v[count].Name;
			myinfo.Password = people_v[count].Password;
			myinfo.Birthday = people_v[count].Birthday;
			myinfo.Fine = people_v[count].Fine;
			myinfo.Phone_N = people_v[count].Phone_N;
			myinfo.Student_N = people_v[count].Student_N;
			return TRUE;
		}
	}
}

string DataManager::GetIpAddress()
{
	WORD wVersionRequested;
	WSADATA wsaData;
	char name[255];
	PHOSTENT hostinfo;
	string strIpAddress;
	wVersionRequested = MAKEWORD(2, 0);

	if (WSAStartup(wVersionRequested, &wsaData) == 0)
	{
		if (gethostname(name, sizeof(name)) == 0)
		{
			if ((hostinfo = gethostbyname(name)) != NULL)
				strIpAddress = inet_ntoa(*(struct in_addr *)*hostinfo->h_addr_list);
		}
		WSACleanup();
	}
	return strIpAddress;
}

