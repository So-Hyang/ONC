#pragma once
#include <mysql.h>
#include <string.h>
#include <vector>
#pragma comment(lib,"libmySQL.lib")
#define DB_HOST "202.31.137.61"
#define DB_USER "root"
#define DB_PASS "1234"
#define DB_People "nsl_information"
#define DB_CalendarNotice "calendarnotice"

using namespace std;

typedef struct
{
	int nType;
	string TopicTitle;
	char* cUserID;
	char* cMsg;
	char* cDate;
	char* PassWord;
	char* SenderID;
	string Participant;
	bool PubPri;

}DataPacket;

class DataBaseSender
{

public:
	DataBaseSender();
	~DataBaseSender();
	MYSQL *conn = mysql_init(NULL);
	int query_stat;
	char* query;
	void DB_Data_Send_to_mysql(DataPacket Data);
	void DB_mysql_connect(const char *DBname);

};


