#include "DBCollector.h"


DBCollector::DBCollector()
{
}


DBCollector::~DBCollector()
{
}




void DBCollector::Set_Information() // people ���� �������� + ����ü�� ������ �����ϱ�.
{
	DB_mysql_connect(DB_People);
	DataManager *mDataManager;	//   �̱��� �ν��Ͻ��� DM�� �����ϱ� ���� ����
	mDataManager = DataManager::GetInstance();

	// *------------------------���� ������ People ������ ��������----------------------------* //
  	query_stat = mysql_query(&conn, "select * from people");  

	if (query_stat != 0)
	{

		DB_finish_with_error(&conn);
	}

	sql_result = mysql_store_result(&conn);
	

	// *------------------------People ������ ����----------------------------* //
	while ((sql_row = mysql_fetch_row(sql_result)) != NULL) 
	{

		mDataManager->RecvPeople.Name = sql_row[0];
		mDataManager->RecvPeople.IP = sql_row[1];
		mDataManager->RecvPeople.Birthday = sql_row[2];
		mDataManager->RecvPeople.Student_N = sql_row[3];
		mDataManager->RecvPeople.Phone_N = sql_row[4];
		mDataManager->RecvPeople.Fine = sql_row[5];
		mDataManager->RecvPeople.Password = sql_row[6];
		mDataManager->people_v.emplace_back(mDataManager->RecvPeople);
		
	}
	//Set_Contents();
	//DB_mysql_disconnect(); //�ӽ� 
}

void DBCollector::Set_Contents() // CalanderNotice ���� �������� + ����ü�� ������ �����ϱ�.
{
	//DB_mysql_disconnect();
	DB_mysql_connect(DB_CalendarNotice);
	DataManager *mDataManager;
	mDataManager = DataManager::GetInstance();
	

	// *------------------------���� ������ contents ������ ��������----------------------------* //
    query_stat = mysql_query(&conn, "select * from contents"); 

	if (query_stat != 0)
	{

		DB_finish_with_error(&conn);
	}

	sql_result = mysql_store_result(&conn);


	
	// *------------------------calendernotice ������ ����----------------------------* //
	while ((sql_row = mysql_fetch_row(sql_result)) != NULL)
	{

		mDataManager->RecvContents.Date = sql_row[0];
		mDataManager->RecvContents.Who = sql_row[1];
		mDataManager->RecvContents.Contents_Type = sql_row[2];
		mDataManager->RecvContents.Public_Type = sql_row[3];
		mDataManager->RecvContents.Main_Contents = sql_row[4];
		mDataManager->calendernotice_v.emplace_back(mDataManager->RecvContents);

	}



}
