#include "DataManager.h"

/* ½Ì±ÛÅæ »ç¿ëÇÏ±â À§ÇÑ »ı¼ºÀÚ ÇÁ¶óÀÌºø
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



