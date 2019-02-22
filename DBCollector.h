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
	MYSQL       *conn = mysql_init(NULL); //2019-02-13 Public���� Private�� ����
	                //2019-02-13 Public���� Private�� ����

public:
	
	int       query_stat;
	void DB_finish_with_error(MYSQL *conn);     // ���� ���� �Լ�
	void DB_mysql_connect(const char *DBname);  // ���� �Լ�
	bool DB_mysql_disconnect();                 // ���� ���� �Լ�
    bool DB_free();                             // ������ �Ҵ� ���� �Լ� 
	void Set_Information();                     // People ���� �������� �� ���� �Լ�
	void Set_Contents();                        // calenderNotice ���� �������� �� ���� �Լ�

	DBCollector();
	~DBCollector();
};
