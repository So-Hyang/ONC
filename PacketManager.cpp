#include "PacketManager.h"

/*클래스명 : PacketManager****************************************************/
/*수정일자 : 2019_02_07*******************************************************/
/*수정담당자 : 김경선**********************************************************/
/*수정사항 : SendRecv클래스의 Recv된 메세지 가져오기****************************/

//public
//ServerDataManager* ServerDataManager::getInstance;



DataPacket PacketManager::PacketAnalysis(DataPacket RecvMessage)
{

	switch (RecvMessage.nType)
	{

		case CalendarPublicPacket: 

			#ifdef SERVERMODE
				CalendarPublicPacketAnalysis(RecvMessage);
			#endif

			#ifdef CLIENTMODE
				Interface.OnCalendarMessage(RecvMessage.cUserID, RecvMessage.cMsg, RecvMessage.cDate);
			#endif

			RecvMessage.nType = 0;
			break;
		case CalendarPrivatePacket: 

			#ifdef SERVERMODE
				CalendarPrivatePacketAnalysis(RecvMessage);
			#endif

			RecvMessage.nType = 0;
			break;
		case NoicePacket: 

			#ifdef SERVERMODE
				NoicePacketAnalysis(RecvMessage);
			#endif	

			#ifdef CLIENTMODE
				Interface.OnNoticeMessage(RecvMessage.cUserID, RecvMessage.cMsg);
			#endif

			RecvMessage.nType = 0;
			break;
		case ChattingPacket: 

			#ifdef SERVERMODE
				ChattingPacketAnalysis(RecvMessage);
			#endif

			#ifdef CLIENTMODE
				Interface.OnChatMessage(RecvMessage.TopicTitle, RecvMessage.cUserID, RecvMessage.cMsg);
			#endif

			RecvMessage.nType = 0;
			break;
		case TopicEnterPacket:

			#ifdef SERVERMODE
				TopicEnterPacketAnalysis(RecvMessage);
			#endif	

			RecvMessage.nType = 0;
			break;
		case TopicLeavePacket: 

			#ifdef SERVERMODE
				TopicLeavePacketAnalysis(RecvMessage);
			#endif	

			RecvMessage.nType = 0;
			break;
		case TopicParticipantPacket: 

			#ifdef SERVERMODE
				TopicParticipantPacketAnalysis(RecvMessage);
			#endif	

			#ifdef CLIENTMODE
				Interface.OnTopicParticipantMessage(RecvMessage.cUserID, RecvMessage.TopicTitle, RecvMessage.Participants);
			#endif

			RecvMessage.nType = 0;
			break;
		case EmergencyPacket: 

			#ifdef SERVERMODE
				EmergencyPacketAnalysis(RecvMessage);
			#endif

			#ifdef CLIENTMODE
				Interface.OnEmergencyAramMessage(RecvMessage.cUserID,RecvMessage.cMsg);
			#endif

			RecvMessage.nType = 0;
			break;
		case PasswordPacket:

			#ifdef SERVERMODE
				PassWordPacketAnalysis(RecvMessage);
			#endif	

			RecvMessage.nType = 0;
			break;
		case  AllTopicTitlePAcket:

			#ifdef CLIENTMODE
				Interface.OnAllTopicTitleMessage(RecvMessage.AllTopicTitle);
			#endif
				RecvMessage.nType = 0;
				break;
	}
	return CDataPacket::getInstance()->SenderMessage;
//#ifdef SERVERMODE
	
//#endif
}
/****************************************************************************/
/*수정일자 : 2019_02_07*******************************************************/
/*수정담당자 : 김경선**********************************************************/
/*수정사항 : *****************************************************************/
//private


DataPacket PacketManager::CalendarPublicPacketAnalysis(DataPacket RecvMessage)
{
	CDataPacket::getInstance()->SenderMessage.nType = RecvMessage.nType;//
	RecvMessage.TopicTitle = "";
	CDataPacket::getInstance()->SenderMessage.cUserID = RecvMessage.cUserID;//
	CDataPacket::getInstance()->SenderMessage.cMsg = RecvMessage.cMsg;//
	CDataPacket::getInstance()->SenderMessage.cDate = RecvMessage.cDate;//
	RecvMessage.cPassWord = "";
	RecvMessage.cSenderID = "";
	RecvMessage.Participants = "";
	RecvMessage.AllTopicTitle = "";
	RecvMessage.PubPrivate = true;
	
	return CDataPacket::getInstance()->SenderMessage;
	
}

DataPacket PacketManager::CalendarPrivatePacketAnalysis(DataPacket RecvMessage)
{
	CDataPacket::getInstance()->SenderMessage.nType = RecvMessage.nType;//
	RecvMessage.TopicTitle = "";
	CDataPacket::getInstance()->SenderMessage.cUserID = RecvMessage.cUserID;//
	CDataPacket::getInstance()->SenderMessage.cMsg=RecvMessage.cMsg;//
	CDataPacket::getInstance()->SenderMessage.cDate=RecvMessage.cDate;//
	RecvMessage.cPassWord = "";
	RecvMessage.cSenderID = "";
	RecvMessage.Participants = "";
	RecvMessage.AllTopicTitle = "";
	RecvMessage.PubPrivate = false;
	return CDataPacket::getInstance()->SenderMessage;

}
DataPacket PacketManager::NoicePacketAnalysis(DataPacket RecvMessage)
{
	CDataPacket::getInstance()->SenderMessage.nType = RecvMessage.nType; //
	RecvMessage.TopicTitle = "";
	CDataPacket::getInstance()->SenderMessage.cUserID = RecvMessage.cUserID ;//
	CDataPacket::getInstance()->SenderMessage.cMsg = RecvMessage.cMsg ;//
	RecvMessage.cDate;//
	RecvMessage.cPassWord = "";
	RecvMessage.cSenderID = "";
	RecvMessage.Participants = "";
	RecvMessage.AllTopicTitle = "";
	RecvMessage.PubPrivate = false;
	return CDataPacket::getInstance()->SenderMessage;
}
DataPacket PacketManager::ChattingPacketAnalysis(DataPacket RecvMessage)
{
	CDataPacket::getInstance()->SenderMessage.nType=RecvMessage.nType;//
	CDataPacket::getInstance()->SenderMessage.TopicTitle = RecvMessage.TopicTitle;
	CDataPacket::getInstance()->SenderMessage.cUserID=RecvMessage.cUserID;//
	CDataPacket::getInstance()->SenderMessage.cMsg=RecvMessage.cMsg;//
	RecvMessage.cDate = "";//
	RecvMessage.cPassWord = "";
	RecvMessage.cSenderID = "";
	RecvMessage.Participants = "";
	RecvMessage.AllTopicTitle = "";
	RecvMessage.PubPrivate = false;
	return CDataPacket::getInstance()->SenderMessage;

}
DataPacket PacketManager::TopicEnterPacketAnalysis(DataPacket RecvMessage)
{
	CDataPacket::getInstance()->SenderMessage.nType=RecvMessage.nType;//
	CDataPacket::getInstance()->SenderMessage.TopicTitle=RecvMessage.TopicTitle;
	CDataPacket::getInstance()->SenderMessage.cUserID=RecvMessage.cUserID ;//
	CDataPacket::getInstance()->SenderMessage.cMsg=RecvMessage.cMsg ;//
	RecvMessage.cDate = "";//
	RecvMessage.cPassWord = "";
	RecvMessage.cSenderID = "";
	RecvMessage.Participants = "";
	RecvMessage.AllTopicTitle = "";
	RecvMessage.PubPrivate = false;
	return CDataPacket::getInstance()->SenderMessage;

}
DataPacket PacketManager::TopicLeavePacketAnalysis(DataPacket RecvMessage)
{
	CDataPacket::getInstance()->SenderMessage.nType = RecvMessage.nType ;//
	CDataPacket::getInstance()->SenderMessage.TopicTitle = RecvMessage.TopicTitle;
	CDataPacket::getInstance()->SenderMessage.cUserID=RecvMessage.cUserID ;//
	CDataPacket::getInstance()->SenderMessage.cMsg = RecvMessage.cMsg ;//
	RecvMessage.cDate = "";//
	RecvMessage.cPassWord = "";
	RecvMessage.cSenderID = "";
	RecvMessage.Participants = "";
	RecvMessage.AllTopicTitle = "";
	RecvMessage.PubPrivate = false;
	return CDataPacket::getInstance()->SenderMessage;

}
DataPacket PacketManager::TopicParticipantPacketAnalysis(DataPacket RecvMessage)
{
	CDataPacket::getInstance()->SenderMessage.nType=RecvMessage.nType;//
	CDataPacket::getInstance()->SenderMessage.TopicTitle = RecvMessage.TopicTitle;
	CDataPacket::getInstance()->SenderMessage.cUserID = RecvMessage.cUserID ;//
	RecvMessage.cMsg = "";//
	RecvMessage.cDate = "";//
	RecvMessage.cPassWord = "";
	RecvMessage.cSenderID = "";
	CDataPacket::getInstance()->SenderMessage.Participants=RecvMessage.Participants;
	RecvMessage.AllTopicTitle = "";
	RecvMessage.PubPrivate = false;
	return CDataPacket::getInstance()->SenderMessage;

}
DataPacket PacketManager::EmergencyPacketAnalysis(DataPacket RecvMessage)
{
	CDataPacket::getInstance()->SenderMessage.nType=RecvMessage.nType;//
	RecvMessage.TopicTitle = "";
	CDataPacket::getInstance()->SenderMessage.cUserID=RecvMessage.cUserID;//
	CDataPacket::getInstance()->SenderMessage.cMsg=RecvMessage.cMsg;//
	RecvMessage.cDate = "";//
	RecvMessage.cPassWord = "";
	RecvMessage.cSenderID = "";
	RecvMessage.Participants = "";
	RecvMessage.AllTopicTitle = "";
	RecvMessage.PubPrivate = false;
	return CDataPacket::getInstance()->SenderMessage;
}
DataPacket PacketManager::PassWordPacketAnalysis(DataPacket RecvMessage)
{
	CDataPacket::getInstance()->SenderMessage.nType=RecvMessage.nType;//
	RecvMessage.TopicTitle = "";
	CDataPacket::getInstance()->SenderMessage.cUserID=RecvMessage.cUserID;//
	RecvMessage.cMsg = "";//
	RecvMessage.cDate = "";//
	RecvMessage.cPassWord = "";
	RecvMessage.cSenderID = "";
	CDataPacket::getInstance()->SenderMessage.cPassWord = RecvMessage.cSenderID;
	RecvMessage.Participants = "";
	RecvMessage.AllTopicTitle = "";
	RecvMessage.PubPrivate = false;
	return CDataPacket::getInstance()->SenderMessage;
}






/****************************************************************************/
/*수정일자 : 2019_02_07*******************************************************/
/*수정담당자 : 김경선**********************************************************/
/*수정사항 : *****************************************************************/

#ifdef SERVERMODE
void PacketManager::PacketCreater(DataPacket SenderMessage)
{

	switch (SenderMessage.nType)
	{
		case CalendarPublicPacket: 

			#ifdef SERVERMODE
				CalendarPublicPacketCreater(SenderMessage);
			#endif

			SenderMessage.nType = 0;
			SenderMessage.TopicTitle = "";
			SenderMessage.cUserID = "";
			SenderMessage.cMsg = "";
			SenderMessage.cDate = "";
			SenderMessage.cPassWord = "";
			SenderMessage.cSenderID = "";
			SenderMessage.Participants = "";
			SenderMessage.AllTopicTitle = "";
			SenderMessage.PubPrivate = false;
			break;
		case CalendarPrivatePacket:

			#ifdef SERVERMODE
				CalendarPrivatePacketCreater(SenderMessage);
			#endif

			SenderMessage.nType = 0;
			SenderMessage.TopicTitle = "";
			SenderMessage.cUserID = "";
			SenderMessage.cMsg = "";
			SenderMessage.cDate = "";
			SenderMessage.cPassWord = "";
			SenderMessage.cSenderID = "";
			SenderMessage.Participants = "";
			SenderMessage.AllTopicTitle = "";
			SenderMessage.PubPrivate = false;
			break;
		case NoicePacket: 

			#ifdef SERVERMODE
				NoicePacketCreater(SenderMessage);
			#endif		

			SenderMessage.nType = 0;
			SenderMessage.TopicTitle = "";
			SenderMessage.cUserID = "";
			SenderMessage.cMsg = "";
			SenderMessage.cDate = "";
			SenderMessage.cPassWord = "";
			SenderMessage.cSenderID = "";
			SenderMessage.Participants = "";
			SenderMessage.AllTopicTitle = "";
			SenderMessage.PubPrivate = false;
			break;
		case ChattingPacket: 

			#ifdef SERVERMODE
				ChattingPacketCreater(SenderMessage);
			#endif	

			SenderMessage.nType = 0;
			SenderMessage.TopicTitle = "";
			SenderMessage.cUserID = "";
			SenderMessage.cMsg = "";
			SenderMessage.cDate = "";
			SenderMessage.cPassWord = "";
			SenderMessage.cSenderID = "";
			SenderMessage.Participants = "";
			SenderMessage.AllTopicTitle = "";
			SenderMessage.PubPrivate = false;
			break;
		case TopicEnterPacket: 

			#ifdef SERVERMODE
				TopicEnterPacketCreater(SenderMessage);
			#endif	

			SenderMessage.nType = 0;
			SenderMessage.TopicTitle = "";
			SenderMessage.cUserID = "";
			SenderMessage.cMsg = "";
			SenderMessage.cDate = "";
			SenderMessage.cPassWord = "";
			SenderMessage.cSenderID = "";
			SenderMessage.Participants = "";
			SenderMessage.AllTopicTitle = "";
			SenderMessage.PubPrivate = false;
			break;
		case TopicLeavePacket: 

			#ifdef SERVERMODE
				TopicLeavePacketCreater(SenderMessage);
			#endif

			SenderMessage.nType = 0;
			SenderMessage.TopicTitle = "";
			SenderMessage.cUserID = "";
			SenderMessage.cMsg = "";
			SenderMessage.cDate = "";
			SenderMessage.cPassWord = "";
			SenderMessage.cSenderID = "";
			SenderMessage.Participants = "";
			SenderMessage.AllTopicTitle = "";
			SenderMessage.PubPrivate = false;
			break;
		case TopicParticipantPacket: 

			#ifdef SERVERMODE
				TopicParticipantPacketCreater(SenderMessage);
			#endif	

			SenderMessage.nType = 0;
			SenderMessage.TopicTitle = "";
			SenderMessage.cUserID = "";
			SenderMessage.cMsg = "";
			SenderMessage.cDate = "";
			SenderMessage.cPassWord = "";
			SenderMessage.cSenderID = "";
			SenderMessage.Participants = "";
			SenderMessage.AllTopicTitle = "";
			SenderMessage.PubPrivate = false;
			break;
		case EmergencyPacket: 
			
			#ifdef SERVERMODE
				EmergencyPacketCreater(SenderMessage);
			#endif
			SenderMessage.nType = 0;
			SenderMessage.TopicTitle = "";
			SenderMessage.cUserID = "";
			SenderMessage.cMsg = "";
			SenderMessage.cDate = "";
			SenderMessage.cPassWord = "";
			SenderMessage.cSenderID = "";
			SenderMessage.Participants = "";
			SenderMessage.AllTopicTitle = "";
			SenderMessage.PubPrivate = false;
			break;
		case PasswordPacket:
			
			#ifdef SERVERMODE
				PassWordPacketCreater(SenderMessage);
			#endif		

			SenderMessage.nType = 0;
			SenderMessage.TopicTitle = "";
			SenderMessage.cUserID = "";
			SenderMessage.cMsg = "";
			SenderMessage.cDate = "";
			SenderMessage.cPassWord = "";
			SenderMessage.cSenderID = "";
			SenderMessage.Participants = "";
			SenderMessage.AllTopicTitle = "";
			SenderMessage.PubPrivate = false;
			break;
	}

	return;

}




/****************************************************************************/
/*수정일자 : 2019_02_07*******************************************************/
/*수정담당자 : 김경선**********************************************************/
/*수정사항 : *****************************************************************/
//private


void PacketManager::CalendarPublicPacketCreater(DataPacket SenderMessage)
{

	int count = 0;
	int SingletonReturn=0;
	while (SingletonReturn != -1)
	{
		SingletonReturn = ServerDataManager::getInstance()->FindSocketValue(alltopic, NULL, count, NULL);
		Sender.Send(SenderMessage, SingletonReturn);
		count++;
	}
}

void PacketManager::CalendarPrivatePacketCreater(DataPacket SenderMessage)
{
	int count = 0;
	int SingletonReturn = 0;
	while (SingletonReturn != -1)
	{
		SingletonReturn = ServerDataManager::getInstance()->FindSocketValue(alltopic, NULL, count, NULL);
		Sender.Send(SenderMessage, SingletonReturn);
		count++;
	}
}

void PacketManager::NoicePacketCreater(DataPacket SenderMessage)
{
	int count = 0;
	int SingletonReturn = 0;
	while (SingletonReturn != -1)
	{
		SingletonReturn = ServerDataManager::getInstance()->FindSocketValue(alltopic, "", count, NULL);
		Sender.Send(SenderMessage, SingletonReturn);
		count++;
	}

}

void PacketManager::ChattingPacketCreater(DataPacket SenderMessages)
{
	int count = 0;
	int SingletonReturn = 0;
	while (SingletonReturn != -1)
	{
		SingletonReturn = ServerDataManager::getInstance()->FindSocketValue(SenderMessages.TopicTitle, NULL, count, NULL);
		Sender.Send(SenderMessages, SingletonReturn);
		count++;
	}
	
}

void PacketManager::TopicEnterPacketCreater(DataPacket SenderMessage)
{
	int UserNum;
	//Analysis가 대입한 목적지 소켓값 SendMessage.ReciverSocketValue값 대입
	//소켓 수 측정
	// 해당 소켓으로 Send
	UserNum =ServerDataManager::getInstance()->SearchInfo("", SenderMessage.cUserID, NULL);
	ServerDataManager::getInstance()->InsertInfo(NULL, SenderMessage.TopicTitle, UserNum);
	
}
void PacketManager::TopicLeavePacketCreater(DataPacket SenderMessage)
{
	int UserNum;
	//Analysis가 대입한 목적지 소켓값 SendMessage.ReciverSocketValue값 대입
	//소켓 수 측정
	// 해당 소켓수 만큼 목적지로 Send
	UserNum = ServerDataManager::getInstance()->SearchInfo("", SenderMessage.cUserID, NULL);
	ServerDataManager::getInstance()->DeleteInfo(NULL, SenderMessage.TopicTitle, UserNum);
	
}
void PacketManager::TopicParticipantPacketCreater(DataPacket SenderMessage)
{
	SOCKET SenderScok;
	int UserLocation;
	int SenderSocketValue;
	string TopicParticipant;
	string seperate = ";";
	string all;
	int count = 0;
	
	string SingletonReturn = "";
	
	while (SingletonReturn != "find fail")
	{
		SingletonReturn = ServerDataManager::getInstance()->FindUserID(SenderMessage.TopicTitle, count);
		all = SingletonReturn + seperate;
		TopicParticipant += all;
		count++;
	}
	count = 0;
	UserLocation = ServerDataManager::getInstance()->SearchInfo("", SenderMessage.cUserID, NULL);
	SenderScok= ServerDataManager::getInstance()->FindSocketValue("", SenderMessage.cUserID, NULL, UserLocation);
	SenderMessage.Participants = TopicParticipant;
//	a = ServerDataManager::getInstance()->SearchInfo(NULL, SenderMessage.cUserID);
	//SenderSocketValue = ServerDataManager::getInstance()->FindSocketValue(NULL, SenderMessage.cUserID, NULL, a);

	Sender.Send(SenderMessage, SenderScok);

}
void PacketManager::EmergencyPacketCreater(DataPacket SenderMessage)
{
	//Analysis가 대입한 목적지 소켓값 SendMessage.ReciverSocketValue값 대입
	//소켓 수 측정
	// 해당 소켓으로 Send
	int count = 0;
	int SingletonReturn = 0;
	while (SingletonReturn != -1)
	{
		SingletonReturn = ServerDataManager::getInstance()->FindSocketValue(alltopic, NULL, count, NULL);
		Sender.Send(SenderMessage, SingletonReturn);
		count++;
	}
	
}
void PacketManager::PassWordPacketCreater(DataPacket SenderMessage)
{
	//Analysis가 대입한 목적지 소켓값 SendMessage.ReciverSocketValue값 대입
	//소켓 수 측정
	// 해당 소켓으로 Send
	// DB와 상의
	//DB 센더 해야함
	
}

#endif

