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
	void DB_finish_with_error(MYSQL *conn);     // 에러 관리 함수
	void DB_mysql_connect(const char *DBname);  // 연결 함수
	bool DB_mysql_disconnect();                 // 연결 해제 함수
	bool DB_free();                             // 데이터 할당 해제 함수 

	DBConnect();
	~DBConnect();
};

