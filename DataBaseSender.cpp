#include "DataBaseSender.h"




DataBaseSender::DataBaseSender()
{
}


DataBaseSender::~DataBaseSender()
{
}





void DataBaseSender::DB_Data_Send_to_mysql(DataPacket Data) // 함수 수정 02-27 김시완 // 
{  

	char* Contents_Type;
	char* Public_Type;

	memset(&Contents_Type, 0, sizeof(Contents_Type));
	memset(&Public_Type, 0, sizeof(Public_Type));

	switch (Data.ntype)
	{
	case 1:
	{

		Contents_Type = "Calender";
		DB_mysql_connect(DB_CalendarNotice);

		if (Data.PubPrivate == true)
		{
			Public_Type = "Public";
		}
		if (Data.PubPrivate == false)
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

		if (mysql_query(&conn, query))
		{
			fprintf(stderr, "%s\n", mysql_error(&conn));
		}
		DB_mysql_disconnect(); //02-27 추가 김시완

	}break;


	case 2:
	{
		Contents_Type = "Notice";
		DB_mysql_connect(DB_CalendarNotice);

		if ((Data.PubPrivate == true )||(Data.PubPrivate == false) ) //02-27 수정 김시완
		{
			Public_Type = "Public";
		}
		/*if (Data.PubPri == false)
		{
			Public_Type = "Private";
		}*/

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

		if (mysql_query(&conn, query))
		{
			fprintf(stderr, "%s\n", mysql_error(&conn));
		}
		DB_mysql_disconnect();// 02-27 추가 김시완
	}break;


	case 9:
	{
		DB_mysql_connect(DB_People);

		string tmp = "";
		tmp = " UPDATE people Set Password = '";
		tmp += Data.cPassword;
		tmp += "' Where Name = '";
		tmp = tmp + Data.cUserID;
		tmp += "'";

		memset(&query, 0, sizeof(query));
		query = (char *)tmp.c_str();

		if (mysql_query(&conn, query))
		{
			fprintf(stderr, "%s\n", mysql_error(&conn));
		}
		DB_mysql_disconnect();// 02-27 추가 김시완
	}break;

	default:
		break;
	}


	
	
}

