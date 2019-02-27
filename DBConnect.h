#pragma once

#include <mysql.h>

#include<iostream>
#include <string.h>
#include <vector>
#include "string"


#pragma comment(lib,"libmySQL.lib")
#define DB_HOST "202.31.137.61"
#define DB_USER "root"
#define DB_PASS "1234"
#define DB_People "nsl_information"
#define DB_CalendarNotice "calendarnotice"

#define CHOP(x) x[strlen(x) - 1] = ' '
using namespace std;
 class DBConnect

{


public:
	MYSQL_RES   *sql_result;
	MYSQL_ROW   sql_row;
	MYSQL       conn; /*= mysql_init(NULL);*/
	MYSQL       *sock;


	int  query_stat;
	void DB_finish_with_error(MYSQL *conn);     // ���� ���� �Լ�
	void DB_mysql_connect(const char *DBname);  // ���� �Լ�
	bool DB_mysql_disconnect();                 // ���� ���� �Լ�
	bool DB_free();                             // ������ �Ҵ� ���� �Լ� 

	DBConnect();
	~DBConnect();
};

