#include "Interface.h"
#include "SendRecv.h"
SendRecv Sender, ClientRecv;

GuiClientInterface* GuiClientInterface::i_Instance = NULL;

//아날리시스에 on메세지 함수 실행 해야함, 리시브 스레드안에 유저인포 관리하는거 고려해야함
void GuiClientInterface::OnChatMessage(string TopicTitle, string cUserID, string cMsg)
{
	int nLocation;
	string sSendMSG;
	CString csSendMSG;

	CONCApp *pApp = (CONCApp *)AfxGetApp();
	CMainFrame* pFrame = (CMainFrame*)pApp->GetMainWnd();
	nLocation = pFrame->m_wndOutput.FindChatRoom(TopicTitle);
	sSendMSG = "[" + cUserID + "] : " + cMsg;
	csSendMSG = sSendMSG.c_str();
	pFrame->m_wndOutput.m_wndList[nLocation].AddString(csSendMSG);
	CDataPacket::getInstance()->RecvMessageClear();
}
void GuiClientInterface::OnNoticeMessage(string UserID, string cMsg)
{
	CONCApp *pApp = (CONCApp *)AfxGetApp();
	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
	//CChildFrame *pChild = (CChildFrame *)pFrame->GetActiveFrame();
	CPropertiesWnd *pDetaiView = (CPropertiesWnd *)pFrame->GetActiveView();
	/*
	ALLNoticeInfo NoticeInfos;

	NoticeInfos.Notice_CUserID = UserID;
	NoticeInfos.Notice_cMsg = cMsg;
	pDetaiView->AddNoticeInfo(NoticeInfos);
	*/
	CDataPacket::getInstance()->RecvMessageClear();
}

void GuiClientInterface::OnCalendarMessage(string UserID, string cMsg, string cDate)
{
	//캘린더뷰
	CONCApp *pApp = (CONCApp *)AfxGetApp();
	CMainFrame* pMain = (CMainFrame*)pApp->GetMainWnd();
	CChildFrame *pChild = (CChildFrame *)pMain->GetActiveFrame();
	CONCDoc *pDoc = (CONCDoc *)pApp->pDoc;
	CCalendarView *pCalView = (CCalendarView *)pDoc->GetCalendarView();

	CalenderNotice i_newschedule_CN;

	i_newschedule_CN.Date = cDate;
	i_newschedule_CN.Who = UserID;
	i_newschedule_CN.Main_Contents = cMsg;
	i_newschedule_CN.Public_Type = "Public";
	i_newschedule_CN.Contents_Type = "Calendar";

	pCalView->AddListSchedule(i_newschedule_CN);
	pMain->m_wndProperties.AddListNotice(i_newschedule_CN); //노티스뷰에 데이터 추가함

	CDataPacket::getInstance()->RecvMessageClear();
}

void GuiClientInterface::OnEmergencyAramMessage(string cUserID, string cMsg)
{
	CONCApp *pApp = (CONCApp *)AfxGetApp();
	CMainFrame* pMain = (CMainFrame*)pApp->GetMainWnd();
	CChildFrame *pChild = (CChildFrame *)pMain->GetActiveFrame();
	CONCDoc *pDoc = (CONCDoc *)pApp->pDoc;
	CCalendarView *pCalView = (CCalendarView *)pDoc->GetCalendarView();

	pCalView->emergencymsg = cMsg.c_str();
	pCalView->ChangeColorEmergencyNotice("Red");

	CDataPacket::getInstance()->RecvMessageClear();
}
void GuiClientInterface::OnTopicParticipantMessage(string cUserID, string TopicTitle, string Participants)
{
	CONCApp *pApp = (CONCApp *)AfxGetApp();
	CMainFrame* pFrame = (CMainFrame*)pApp->GetMainWnd();

	pFrame->m_wndClassView.SetTreeData(Participants);
	// GUI가 코딩해야함
	CDataPacket::getInstance()->RecvMessageClear();
}
void GuiClientInterface::OnAllTopicTitleMessage(string AllTopicTitle)
{
	char* cPtr = (char*)AllTopicTitle.c_str();
	int i = 0;

	CONCApp *pApp = (CONCApp *)AfxGetApp();
	CMainFrame* pFrame = (CMainFrame*)pApp->GetMainWnd();
	
	char *ptr = strtok(cPtr, ";");
	while (ptr != NULL)
	{
		string str = ptr;
		pFrame->m_wndOutput.sTitleList[i] = str;
		ptr = strtok(NULL, ";");
		i++;
	}
	
	//pFrame->m_wndOutput.RefreshTab();
	pFrame->m_wndOutput.nChatNum = i;
	pFrame->m_wndOutput.Invalidate();
	CDataPacket::getInstance()->RecvMessageClear();
}
SOCKET GuiClientInterface::ConncetWithServer()
{
	
	ConnectServerSocket = ConnectStart.ConnectWithServer();
	CDataPacket::getInstance()->SenderMessage.nType = 9;
	CDataPacket::getInstance()->SenderMessage.cUserID = "KimSiWan";
	CDataPacket::getInstance()->SenderMessage.cPassWord = "1234";
	
	send(ConnectServerSocket, (char*)&CDataPacket::getInstance()->SenderMessage, sizeof(CDataPacket::getInstance()->SenderMessage), 0);
//	CDataPacket::getInstance()->ClientSocket.ClientSock = ConnectServerSocket;
	ClientRecv.RecvThread(ConnectServerSocket);
	return ConnectServerSocket;
}
void GuiClientInterface::DisConnecttion(SOCKET ServerSock)
{
	closesocket(CDataPacket::getInstance()->ClientSocket.ClientSock);
}



//************************GUI Sener****************************************//



void GuiClientInterface::SendChatMessage(unsigned int nType, string TopicTitle, string cUserID, string cMsg)
{
	CDataPacket::getInstance()->SenderMessage.nType = nType;
	CDataPacket::getInstance()->SenderMessage.TopicTitle = TopicTitle;
	CDataPacket::getInstance()->SenderMessage.cUserID = cUserID;
	CDataPacket::getInstance()->SenderMessage.cMsg = cMsg;
	if (Sender.Send(CDataPacket::getInstance()->SenderMessage, CDataPacket::getInstance()->ClientSocket.ClientSock) != -1)
	{
		CDataPacket::getInstance()->SendMessageClear();
	}
}
void GuiClientInterface::SendNoticeMessage(unsigned int nType, string cUserID, string cMsg, string cDate)
{
	CDataPacket::getInstance()->SenderMessage.nType = nType;
	CDataPacket::getInstance()->SenderMessage.cUserID = cUserID;
	CDataPacket::getInstance()->SenderMessage.cMsg = cMsg;
	CDataPacket::getInstance()->SenderMessage.cDate = cDate;
	if (Sender.Send(CDataPacket::getInstance()->SenderMessage, CDataPacket::getInstance()->ClientSocket.ClientSock) == 1)
	{
		CDataPacket::getInstance()->SendMessageClear();
	}

}
void GuiClientInterface::SendCalendarPublicMessage(unsigned int nType, string cUserID, string cMsg, string cDate, bool PubPrivate)
{
	CDataPacket::getInstance()->SenderMessage.nType = nType;
	CDataPacket::getInstance()->SenderMessage.cUserID = cUserID;
	CDataPacket::getInstance()->SenderMessage.cMsg = cMsg;
	CDataPacket::getInstance()->SenderMessage.cDate = cDate;
	CDataPacket::getInstance()->SenderMessage.PubPrivate = PubPrivate;
	if (Sender.Send(CDataPacket::getInstance()->SenderMessage, CDataPacket::getInstance()->ClientSocket.ClientSock) == 1)
	{
		CDataPacket::getInstance()->SendMessageClear();
	}
}
void GuiClientInterface::SendCalendarPrivateMessage(unsigned int nType, string cUserID, string cMsg, string cDate, bool PubPrivate)
{
	CDataPacket::getInstance()->SenderMessage.nType = nType;
	CDataPacket::getInstance()->SenderMessage.cUserID = cUserID;
	CDataPacket::getInstance()->SenderMessage.cMsg = cMsg;
	CDataPacket::getInstance()->SenderMessage.cDate = cDate;
	CDataPacket::getInstance()->SenderMessage.PubPrivate = PubPrivate;
	if (Sender.Send(CDataPacket::getInstance()->SenderMessage, CDataPacket::getInstance()->ClientSocket.ClientSock) == 1)
	{
		CDataPacket::getInstance()->SendMessageClear();
	}
}
void GuiClientInterface::SendTopicEnterMessage(unsigned int nType, string cUserID, string TopicTitle)
{
	CDataPacket::getInstance()->SenderMessage.nType = nType;
	CDataPacket::getInstance()->SenderMessage.cUserID = cUserID;
	CDataPacket::getInstance()->SenderMessage.TopicTitle = TopicTitle;

	if (Sender.Send(CDataPacket::getInstance()->SenderMessage, CDataPacket::getInstance()->ClientSocket.ClientSock) == 1)
	{
		CDataPacket::getInstance()->SendMessageClear();
	}
}
void GuiClientInterface::SendTopicLeaveMessage(unsigned int nType, string cUserID, string TopicTitle)
{
	CDataPacket::getInstance()->SenderMessage.nType = nType;
	CDataPacket::getInstance()->SenderMessage.cUserID = cUserID;
	CDataPacket::getInstance()->SenderMessage.TopicTitle = TopicTitle;

	if (Sender.Send(CDataPacket::getInstance()->SenderMessage, CDataPacket::getInstance()->ClientSocket.ClientSock) == 1)
	{
		CDataPacket::getInstance()->SendMessageClear();
	}
}
void GuiClientInterface::SendEmergencyAramMessage(unsigned int nType, string cUserID, string cMsg)
{
	CDataPacket::getInstance()->SenderMessage.nType = nType;
	CDataPacket::getInstance()->SenderMessage.cUserID = cUserID;
	CDataPacket::getInstance()->SenderMessage.cMsg = cMsg;

	if (Sender.Send(CDataPacket::getInstance()->SenderMessage, CDataPacket::getInstance()->ClientSocket.ClientSock) == 1)
	{
		CDataPacket::getInstance()->SendMessageClear();
	}
}
void GuiClientInterface::SendTopicParticipantMessage(unsigned int nType, string cUserID, string TopicTitle)
{
	CDataPacket::getInstance()->SenderMessage.nType = nType;
	CDataPacket::getInstance()->SenderMessage.cUserID = cUserID;
	CDataPacket::getInstance()->SenderMessage.TopicTitle = TopicTitle;

	if (Sender.Send(CDataPacket::getInstance()->SenderMessage, CDataPacket::getInstance()->ClientSocket.ClientSock) != -1)
	{
		CDataPacket::getInstance()->SendMessageClear();
	}
}
void GuiClientInterface::SendPassWordMessage(unsigned int nType, string cUserID, string PassWord)
{
	CDataPacket::getInstance()->SenderMessage.nType = nType;
	CDataPacket::getInstance()->SenderMessage.cUserID = cUserID;
	CDataPacket::getInstance()->SenderMessage.cPassWord = PassWord;

	if (Sender.Send(CDataPacket::getInstance()->SenderMessage, CDataPacket::getInstance()->ClientSocket.ClientSock) == 1)
	{
		CDataPacket::getInstance()->SendMessageClear();
	}
}