#pragma once

#include <mysql.h>
#include<iostream>
#include <string.h>
#include <vector>
#include "string"
//#include "stdafx.h"

#include "DataManager.h"

#pragma comment(lib,"libmySQL.lib")
#define DB_HOST "127.0.0.1"
#define DB_USER "root"
#define DB_PASS "1234"
#define DB_People "nsl_information"
#define DB_CalendarNotice "calendarnotice"

#define CHOP(x) x[strlen(x) - 1] = ' '
using namespace std;

class DBCollector
{
private:

	
	MYSQL_RES   *sql_result;
	MYSQL_ROW   sql_row;
	MYSQL       *conn = mysql_init(NULL); //2019-02-13 Public에서 Private로 수정
	                //2019-02-13 Public에서 Private로 수정

public:
	
	int       query_stat;
	void DB_finish_with_error(MYSQL *conn);     // 에러 관리 함수
	void DB_mysql_connect(const char *DBname);  // 연결 함수
	bool DB_mysql_disconnect();                 // 연결 해제 함수
    bool DB_free();                             // 데이터 할당 해제 함수 
	void Set_Information();                     // People 정보 가져오기 및 저장 함수
	void Set_Contents();                        // calenderNotice 정보 가져오기 및 저장 함수

	DBCollector();
	~DBCollector();
};
