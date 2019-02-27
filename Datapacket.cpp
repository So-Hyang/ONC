#include "DataPacket.h"

CDataPacket* CDataPacket::c_Instance = NULL;

void CDataPacket::SendMessageClear()
{
	this->SenderMessage.nType = 0;
	this->SenderMessage.TopicTitle = "";
	this->SenderMessage.cUserID = "";
	this->SenderMessage.cMsg = "";
	this->SenderMessage.cDate = "";
	this->SenderMessage.cPassWord = "";
	this->SenderMessage.cSenderID = "";
	this->SenderMessage.Participants = "";
	this->SenderMessage.AllTopicTitle = "";
	this->SenderMessage.PubPrivate = false;
};
void CDataPacket::RecvMessageClear()
{
	this->RecverMessage.nType = 0;
	this->RecverMessage.TopicTitle = "";
	this->RecverMessage.cUserID = "";
	this->RecverMessage.cMsg = "";
	this->RecverMessage.cDate = "";
	this->RecverMessage.cPassWord = "";
	this->RecverMessage.cSenderID = "";
	this->RecverMessage.Participants = "";
	this->RecverMessage.AllTopicTitle = "";
	this->RecverMessage.PubPrivate = false;


	this->RecvMessage.nType = 0;
	this->RecvMessage.TopicTitle = "";
	this->RecvMessage.cUserID = "";
	this->RecvMessage.cMsg = "";
	this->RecvMessage.cDate = "";
	this->RecvMessage.cPassWord = "";
	this->RecvMessage.cSenderID = "";
	this->RecvMessage.Participants = "";
	this->RecvMessage.AllTopicTitle = "";
	this->RecvMessage.PubPrivate = false;
};