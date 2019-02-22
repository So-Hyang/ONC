#include "Interface.h"
//아날리시스에 on메세지 함수 실행 해야함, 리시브 스레드안에 유저인포 관리하는거 고려해야함
void GuiClientInterface::OnChatMessage(string TopicTitle, string cUserID, string cMsg)
{
	//GUI가 코딩해야함
}
void GuiClientInterface::OnNoticeMessage(string UserID, string cMsg)
{
	// GUI가 코딩해야함
}
void GuiClientInterface::OnCalendarMessage(string UserID, string cMsg, string cDate)
{
	// GUI가 코딩해야함
}
void GuiClientInterface::OnEmergencyAramMessage(string cUserID, string cMsg)
{
	//GUI가 코딩해야함
}
void GuiClientInterface::OnTopicParticipantMessage(string cUserID, string TopicTitle, string Participants)
{
	// GUI가 코딩해야함
}
void GuiClientInterface::OnAllTopicTitleMessage(string AllTopicTitle)
{
	// GUI가 코딩해야함
}
void GuiClientInterface::ConncetWithServer()
{
	
	ConnectServerSocket = ConnectStart.ConnectWithServer();
	ClientRecv.RecvThread(ConnectServerSocket);  //리시브 스레드에서 벡터 넣고빼는거 어떡하지??????????
}
void GuiClientInterface::DisConnecttion(SOCKET ServerSock)
{
	closesocket(ConnectServerSocket);
}



//************************GUI Sener****************************************//



void GuiClientInterface::SendChatMessage(unsigned int nType, string TopicTitle, string cUserID, string cMsg)
{
	CDataPacket::getInstance()->SenderMessage.nType = nType;
	CDataPacket::getInstance()->SenderMessage.TopicTitle = TopicTitle;
	CDataPacket::getInstance()->SenderMessage.cUserID = cUserID;
	CDataPacket::getInstance()->SenderMessage.cMsg = cMsg;
	Sender.Send(CDataPacket::getInstance()->SenderMessage, CDataPacket::getInstance()->ClientSocket.ClientSock);
}
void GuiClientInterface::SendNoticeMessage(unsigned int nType, string cUserID, string cMsg, string cDate)
{
	CDataPacket::getInstance()->SenderMessage.nType = nType;
	CDataPacket::getInstance()->SenderMessage.cUserID = cUserID;
	CDataPacket::getInstance()->SenderMessage.cMsg = cMsg;
	CDataPacket::getInstance()->SenderMessage.cDate = cDate;
	Sender.Send(CDataPacket::getInstance()->SenderMessage, CDataPacket::getInstance()->ClientSocket.ClientSock);

}
void GuiClientInterface::SendCalendarPublicMessage(unsigned int nType, string cUserID, string cMsg, string cDate, bool PubPrivate)
{
	CDataPacket::getInstance()->SenderMessage.nType = nType;
	CDataPacket::getInstance()->SenderMessage.cUserID = cUserID;
	CDataPacket::getInstance()->SenderMessage.cMsg = cMsg;
	CDataPacket::getInstance()->SenderMessage.cDate = cDate;
	CDataPacket::getInstance()->SenderMessage.PubPrivate = PubPrivate;
	Sender.Send(CDataPacket::getInstance()->SenderMessage, CDataPacket::getInstance()->ClientSocket.ClientSock);
}
void GuiClientInterface::SendCalendarPrivateMessage(unsigned int nType, string cUserID, string cMsg, string cDate, bool PubPrivate)
{
	CDataPacket::getInstance()->SenderMessage.nType = nType;
	CDataPacket::getInstance()->SenderMessage.cUserID = cUserID;
	CDataPacket::getInstance()->SenderMessage.cMsg = cMsg;
	CDataPacket::getInstance()->SenderMessage.cDate = cDate;
	CDataPacket::getInstance()->SenderMessage.PubPrivate = PubPrivate;
	Sender.Send(CDataPacket::getInstance()->SenderMessage, CDataPacket::getInstance()->ClientSocket.ClientSock);
}
void GuiClientInterface::SendTopicEnterMessage(unsigned int nType, string cUserID, string TopicTitle)
{
	CDataPacket::getInstance()->SenderMessage.nType = nType;
	CDataPacket::getInstance()->SenderMessage.cUserID = cUserID;
	CDataPacket::getInstance()->SenderMessage.TopicTitle = TopicTitle;

	Sender.Send(CDataPacket::getInstance()->SenderMessage, CDataPacket::getInstance()->ClientSocket.ClientSock);
}
void GuiClientInterface::SendTopicLeaveMessage(unsigned int nType, string cUserID, string TopicTitle)
{
	CDataPacket::getInstance()->SenderMessage.nType = nType;
	CDataPacket::getInstance()->SenderMessage.cUserID = cUserID;
	CDataPacket::getInstance()->SenderMessage.TopicTitle = TopicTitle;

	Sender.Send(CDataPacket::getInstance()->SenderMessage, CDataPacket::getInstance()->ClientSocket.ClientSock);
}
void GuiClientInterface::SendEmergencyAramMessage(unsigned int nType, string cUserID, string cMsg)
{
	CDataPacket::getInstance()->SenderMessage.nType = nType;
	CDataPacket::getInstance()->SenderMessage.cUserID = cUserID;
	CDataPacket::getInstance()->SenderMessage.cMsg = cMsg;

	Sender.Send(CDataPacket::getInstance()->SenderMessage, CDataPacket::getInstance()->ClientSocket.ClientSock);
}
void GuiClientInterface::SendTopicParticipantMessage(unsigned int nType, string cUserID, string TopicTitle)
{
	CDataPacket::getInstance()->SenderMessage.nType = nType;
	CDataPacket::getInstance()->SenderMessage.cUserID = cUserID;
	CDataPacket::getInstance()->SenderMessage.TopicTitle = TopicTitle;

	Sender.Send(CDataPacket::getInstance()->SenderMessage, CDataPacket::getInstance()->ClientSocket.ClientSock);
}