#include "DBCollector.h"

DBCollector::DBCollector()
{
}


DBCollector::~DBCollector()
{
}

void DBCollector::DB_finish_with_error(MYSQL *conn) // ������
{

	fprintf(stderr, "%s\n", mysql_error(conn));
	//printf("Ŀ�ǵ� ����: %s\n", query_stat);
	mysql_close(conn);
	exit(1);
}

void DBCollector::DB_mysql_connect(const char *input) //����
{

	if (mysql_real_connect(conn, DB_HOST, DB_USER, DB_PASS, input, 0, NULL, 0) == NULL)
	{
		DB_finish_with_error(conn);
	} printf("���� Ȯ�� \n");
}


bool DBCollector::DB_free()
{
	if (sql_result)
	{
		mysql_free_result(sql_result);
		return true;
	}

	return false;
}

bool DBCollector::DB_mysql_disconnect()
{
	if (conn) 
		mysql_close(conn);

	DB_free();
	return true;
}


void DBCollector::Set_Information() // people ���� �������� + ����ü�� ������ �����ϱ�.
{
	//   �̱��� �ν��Ͻ��� DM�� �����ϱ� ���� ����
	DataManager *mDataManager;
	mDataManager = DataManager::GetInstance();
	//People_DB mPeople;
	//DataManager::GetInstance()->RecvMessage.Birthday;
	// *------------------------���� ������ People ������ ��������----------------------------* //
  	query_stat = mysql_query(conn, "select * from people");  

	if (query_stat != 0)
	{

		DB_finish_with_error(conn);
	}

	sql_result = mysql_store_result(conn);
	

	// *------------------------People ������ ����----------------------------* //
	while ((sql_row = mysql_fetch_row(sql_result)) != NULL) 
	{

		mDataManager->RecvPeople.name = sql_row[0];
		mDataManager->RecvPeople.IP = sql_row[1];
		mDataManager->RecvPeople.Birthday = sql_row[2];
		mDataManager->RecvPeople.Student_N = sql_row[3];
		mDataManager->RecvPeople.Phone_N = sql_row[4];
		mDataManager->RecvPeople.Fine = sql_row[5];
		mDataManager->RecvPeople.Password = sql_row[6];
		mDataManager->people_v.emplace_back(mDataManager->RecvPeople);
		
	}

	/*
	// *------------------------��� Ȯ��----------------------------*
	//for (vector<People>::iterator i = mDataManager->people_v.begin(); i != mDataManager->people_v.end(); i++)
    for (int i = 0; i < mDataManager->people_v.size(); i++)
	{
	    std::cout << mDataManager->people_v[i].name << std::endl;
		std::cout << mDataManager->people_v[i].IP << std::endl;
		std::cout << mDataManager->people_v[i].Birthday << std::endl;
		std::cout << mDataManager->people_v[i].Student_N << std::endl;
		std::cout << mDataManager->people_v[i].Phone_N << std::endl;
		std::cout << mDataManager->people_v[i].Fine << std::endl;
		std::cout << mDataManager->people_v[i].Password << std::endl;
	}// �۵� �׽�Ʈ�� ���߿� ������ ����

	*/
}

void DBCollector::Set_Contents() // CalanderNotice ���� �������� + ����ü�� ������ �����ϱ�.
{

	DataManager *mDataManager;
	mDataManager = DataManager::GetInstance();
	//CalenderNotice mCalenderNotice;

	// *------------------------���� ������ contents ������ ��������----------------------------* //
    query_stat = mysql_query(conn, "select * from contents"); 

	if (query_stat != 0)
	{

		DB_finish_with_error(conn);
	}

	sql_result = mysql_store_result(conn);


	
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

	
	// *------------------------��� Ȯ��----------------------------*
	for (int i = 0; i < mDataManager->people_v.size(); i++)
	{
		std::cout << mDataManager->calendernotice_v[i].Date << std::endl;
		std::cout << mDataManager->calendernotice_v[i].Who << std::endl;
		std::cout << mDataManager->calendernotice_v[i].Contents_Type << std::endl;
		std::cout << mDataManager->calendernotice_v[i].Public_Type << std::endl;
		std::cout << mDataManager->calendernotice_v[i].Main_Contents << std::endl;		
	} // �۵� �׽�Ʈ�� ���߿� ������ ����


}
