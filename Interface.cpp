#include "Interface.h"
//�Ƴ����ý��� on�޼��� �Լ� ���� �ؾ���, ���ú� ������ȿ� �������� �����ϴ°� ����ؾ���
void GuiClientInterface::OnChatMessage(string TopicTitle, string cUserID, string cMsg)
{
	//GUI�� �ڵ��ؾ���
}
void GuiClientInterface::OnNoticeMessage(string UserID, string cMsg)
{
	// GUI�� �ڵ��ؾ���
}
void GuiClientInterface::OnCalendarMessage(string UserID, string cMsg, string cDate)
{
	// GUI�� �ڵ��ؾ���
}
void GuiClientInterface::OnEmergencyAramMessage(string cUserID, string cMsg)
{
	//GUI�� �ڵ��ؾ���
}
void GuiClientInterface::OnTopicParticipantMessage(string cUserID, string TopicTitle, string Participants)
{
	// GUI�� �ڵ��ؾ���
}
void GuiClientInterface::OnAllTopicTitleMessage(string AllTopicTitle)
{
	// GUI�� �ڵ��ؾ���
}
void GuiClientInterface::ConncetWithServer()
{
	
	ConnectServerSocket = ConnectStart.ConnectWithServer();
	ClientRecv.RecvThread(ConnectServerSocket);  //���ú� �����忡�� ���� �ְ��°� �����??????????
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