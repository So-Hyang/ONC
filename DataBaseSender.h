#pragma once

#include "DBConnect.h"


using namespace std;





typedef struct
{
	/*int nType;
	string TopicTitle;
	char* cUserID;
	char* cMsg;
	char* cDate;
	char* PassWord;
	char* SenderID;
	string Participant;
	bool PubPri;*/



	unsigned int ntype = 0;
	string Topictitle;
	string cUserID;
	string cMsg;
	string cDate;
	string cPassword;
	string cSenderid;
	string Participants;
	string Alltopictitle;
	bool PubPrivate;

}DataPacket;

class DataBaseSender : public DBConnect
{

public:
	DataBaseSender();
	~DataBaseSender();	
	char* query;
	void DB_Data_Send_to_mysql(DataPacket Data);
	

};


