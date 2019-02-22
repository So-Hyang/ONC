#include "DataBaseSender.h"


//using namespace std;

DataBaseSender::DataBaseSender()
{
}


DataBaseSender::~DataBaseSender()
{
}



void DataBaseSender::DB_mysql_connect(const char *input) //연결
{

	if (mysql_real_connect(conn, DB_HOST, DB_USER, DB_PASS, input, 0, NULL, 0) == NULL)
	{
		fprintf(stderr, "%s\n", mysql_error(conn));
		printf("커맨드 실패: %s\n", query_stat);
		mysql_close(conn);
		exit(1);
	} printf("커맨드 성공: %s\n", query_stat);
}


void DataBaseSender::DB_Data_Send_to_mysql(DataPacket Data)
{  

	char* Contents_Type;
	char* Public_Type;

	memset(&Contents_Type, 0, sizeof(Contents_Type));
	memset(&Public_Type, 0, sizeof(Public_Type));

	switch (Data.nType)
	{
	case 1:
	{

		Contents_Type = "Calender";
		DB_mysql_connect(DB_CalendarNotice);

		if (Data.PubPri == true)
		{
			Public_Type = "Public";
		}
		if (Data.PubPri == false)
		{
			Public_Type = "Private";
		}

		memset(&query, 0, sizeof(query));

		string tmp = "";
		tmp = "INSERT INTO contents (Date, Who, Contents_Type, Public_Type, Main_Contents) VALUES('";
		tmp = tmp + Data.cDate;
		tmp += "', '";
		tmp += Data.cUserID;
		tmp += "', '";
		tmp += Contents_Type;
		tmp += "', '";
		tmp += Public_Type;
		tmp += "', '";
		tmp += Data.cMsg;
		tmp += "')";
		//memcpy(query, tmp.c_str(), strlen(tmp.c_str()));
		query = (char *)tmp.c_str();

		if (mysql_query(conn, query))
		{
			fprintf(stderr, "%s\n", mysql_error(conn));
		}

	}break;


	case 2:
	{
		Contents_Type = "Notice";
		DB_mysql_connect(DB_CalendarNotice);

		if (Data.PubPri == true)
		{
			Public_Type = "Public";
		}
		if (Data.PubPri == false)
		{
			Public_Type = "Private";
		}

		memset(&query, 0, sizeof(query));

		string tmp = "";
		tmp = "INSERT INTO contents (Date, Who, Contents_Type, Public_Type, Main_Contents) VALUES('";
		tmp = tmp + Data.cDate;
		tmp += "', '";
		tmp += Data.cUserID;
		tmp += "', '";
		tmp += Contents_Type;
		tmp += "', '";
		tmp += Public_Type;
		tmp += "', '";
		tmp += Data.cMsg;
		tmp += "')";
		//memcpy(query, tmp.c_str(), strlen(tmp.c_str()));
		query = (char *)tmp.c_str();

		if (mysql_query(conn, query))
		{
			fprintf(stderr, "%s\n", mysql_error(conn));
		}

	}break;


	case 9:
	{
		DB_mysql_connect(DB_People);

		string tmp = "";
		tmp = " UPDATE people Set Password = '";
		tmp += Data.PassWord;
		tmp += "' Where Name = '";
		tmp = tmp + Data.cUserID;
		tmp += "'";

		memset(&query, 0, sizeof(query));
		query = (char *)tmp.c_str();

		if (mysql_query(conn, query))
		{
			fprintf(stderr, "%s\n", mysql_error(conn));
		}

	}break;

	default:
		break;
	}


	
	
}

