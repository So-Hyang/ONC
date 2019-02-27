#pragma once


#include "DBConnect.h"
#include "DataManager.h"


class DBCollector : public DBConnect
{
	
public:
	
	void Set_Information();                     // People 정보 가져오기 및 저장 함수
	void Set_Contents();                        // calenderNotice 정보 가져오기 및 저장 함수
	DBCollector();
	~DBCollector();
};
