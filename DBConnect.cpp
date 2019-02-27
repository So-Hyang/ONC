#include "stdafx.h"
#include "DBConnect.h"


DBConnect::DBConnect()
{
}


DBConnect::~DBConnect()
{
}
void DBConnect::DB_finish_with_error(MYSQL *conn) // 에러문
{
	//fprintf(stderr, "%s\n", mysql_error(conn));
	//printf("커맨드 실패: %s\n", query_stat);
	mysql_close(conn);
	//exit(1);
}

void DBConnect::DB_mysql_connect(const char *input) //연결
{
	
	/*if (sock) {
		DB_mysql_disconnect();
	}*/
	
	mysql_init(&conn);	

	sock = mysql_real_connect(&conn, DB_HOST, DB_USER, DB_PASS, input, 3306,(char *)NULL, 0);
	if (sock==NULL)
	{
		DB_finish_with_error(&conn);
	}

	/*if (mysql_real_connect(conn, DB_HOST, DB_USER, DB_PASS, input, 0, NULL, 0) == NULL)
	{
		DB_finish_with_error(conn);
	}*/
}

bool DBConnect::DB_free()
{
	if (sql_result)
	{
		mysql_free_result(sql_result);
		return true;
	}

	return false;
}

bool DBConnect::DB_mysql_disconnect()
{
	if (sock)
		mysql_close(sock);
	
	DB_free();
	return true;
}