#pragma once


#include "DBConnect.h"
#include "DataManager.h"


class DBCollector : public DBConnect
{
	
public:
	
	void Set_Information();                     // People ���� �������� �� ���� �Լ�
	void Set_Contents();                        // calenderNotice ���� �������� �� ���� �Լ�
	DBCollector();
	~DBCollector();
};
