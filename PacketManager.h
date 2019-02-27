#pragma once

#include "stdafx.h"
#include "DataPacket.h"
#include "ServerDataManager.h"
#include "Interface.h"
//#include "afxwin.h"
//#include <afx.h>
#include <string>

#ifdef SERVERMODE
#include "SendRecv.h"
#endif

using namespace std;

class PacketManager
{
public: 
	
	void PacketCreater(DataPacket SenderMessage);
	DataPacket PacketAnalysis(DataPacket RecvMessage);
	
	
	
private:
	GuiClientInterface Interface;
	int PacketCreaterType = 0;
	string alltopic = "NSL";
//	GuiClientInterface InterfaceAnalysis;

#ifdef SERVERMODE
	SendRecv Sender;
	void CalendarPublicPacketCreater(DataPacket SenderMessage);
	void CalendarPrivatePacketCreater(DataPacket SenderMessage);
	void NoicePacketCreater(DataPacket SenderMessage);
	void TopicEnterPacketCreater(DataPacket SenderMessage);
	void TopicLeavePacketCreater(DataPacket SenderMessage);
	void TopicParticipantPacketCreater(DataPacket SenderMessage);
	void EmergencyPacketCreater(DataPacket SenderMessage);
	void PassWordPacketCreater(DataPacket SenderMessage);
	void ChattingPacketCreater(DataPacket SenderMessage);
#endif

#ifdef CLIENTMODE
	
#endif

	DataPacket CalendarPublicPacketAnalysis(DataPacket RecvMessage);
	DataPacket CalendarPrivatePacketAnalysis(DataPacket RecvMessage);
	DataPacket NoicePacketAnalysis(DataPacket RecvMessage);
	DataPacket ChattingPacketAnalysis(DataPacket RecvMessage);
	DataPacket TopicEnterPacketAnalysis(DataPacket RecvMessage);
	DataPacket TopicLeavePacketAnalysis(DataPacket RecvMessage);
	DataPacket TopicParticipantPacketAnalysis(DataPacket RecvMessage);
	DataPacket EmergencyPacketAnalysis(DataPacket RecvMessage);
	DataPacket PassWordPacketAnalysis(DataPacket RecvMessage);
	

};
