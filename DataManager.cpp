#include "DataManager.h"

/* �̱��� ����ϱ� ���� ������ �����̺�
DataManager::DataManager()
{
}


DataManager::~DataManager()
{
}

*/

bool DataManager::instanceflag = false;
DataManager* DataManager::instance = NULL;

DataManager* DataManager::GetInstance() {
	if (!instance) {
		instance = new DataManager();
		instanceflag = true;
	}
	return instance;
}



