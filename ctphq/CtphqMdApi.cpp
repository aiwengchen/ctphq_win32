#include <iostream>
#include "CtphqMdApi.h"
using namespace std;

//��Ա����
TThostFtdcBrokerIDType g_chBrokerID;
//�����û�����
TThostFtdcUserIDType g_chUserID;

void CtphqMdApi::OnFrontConnected()
{
	CThostFtdcReqUserLoginField reqUserLogin;
	//get BrokerID
	cout << "BrokerID:";
	cin >> g_chBrokerID;
	strcpy_s(reqUserLogin.BrokerID, g_chBrokerID);

	//get userid
	cout << "UserID:";
	cin >> g_chUserID;
	strcpy_s(reqUserLogin.UserID, g_chUserID);

	//get password
	cout << "password:";
	cin >> reqUserLogin.Password;
	
	m_pUserApi->ReqUserLogin(&reqUserLogin, 0);

}

//���ͻ����뽻���й�ϵͳͨ�����ӶϿ�ʱ���÷���������
void CtphqMdApi::OnFrontDisconnected(int nReason)
{
	cout << "OnFrontDisconnected--�������磡" << endl;
}

void CtphqMdApi::OnHeartBeatWarning(int nTimeLapse)
{
}

void CtphqMdApi::OnRspUserLogin(CThostFtdcRspUserLoginField * pRspUserLogin, CThostFtdcRspInfoField * pRspInfo, int nRequestID, bool bIsLast)
{
	cout << "OnRspUserLogin:" << endl;
	cout << "ErrorCode=" << pRspInfo->ErrorID << " ErrorMsg=" << pRspInfo->ErrorMsg << endl;
	cout << "RequestID= " << nRequestID << "Chain=" << bIsLast << endl;
	//�˵�ʧ�ܣ��ͻ�������д�����
	if (pRspInfo->ErrorID != 0)
	{
		cout << "Failed to login,errorcode=" << pRspInfo->ErrorID << "errormsg=" << pRspInfo->ErrorMsg << "requestid=" << nRequestID
			<< "chain=" << bIsLast << endl;
		exit(-1);
	}
	//�˵ǳɹ�
	//��������
	char *Instrumnet[] = { "au1606","ag1606" };
	m_pUserApi->SubscribeMarketData(Instrumnet, 2);
	//�˶�����
	m_pUserApi->UnSubscribeMarketData(Instrumnet, 2);
}

void CtphqMdApi::OnRspUserLogout(CThostFtdcUserLogoutField * pUserLogout, CThostFtdcRspInfoField * pRspInfo, int nRequestID, bool bIsLast)
{
	cout << "goodbye.";
}

void CtphqMdApi::OnRspError(CThostFtdcRspInfoField * pRspInfo, int nRequestID, bool bIsLast)
{
	cout << "OnRspError! errorcode=" << pRspInfo->ErrorID << "errormsg=" << pRspInfo->ErrorMsg << "requestid=" << nRequestID
		<< "chain=" << bIsLast << endl;
	cout << "������������" << endl;
}

void CtphqMdApi::OnRspSubMarketData(CThostFtdcSpecificInstrumentField * pSpecificInstrument, CThostFtdcRspInfoField * pRspInfo, int nRequestID, bool bIsLast)
{
}

void CtphqMdApi::OnRspUnSubMarketData(CThostFtdcSpecificInstrumentField * pSpecificInstrument, CThostFtdcRspInfoField * pRspInfo, int nRequestID, bool bIsLast)
{
}

void CtphqMdApi::OnRspSubForQuoteRsp(CThostFtdcSpecificInstrumentField * pSpecificInstrument, CThostFtdcRspInfoField * pRspInfo, int nRequestID, bool bIsLast)
{
}

void CtphqMdApi::OnRspUnSubForQuoteRsp(CThostFtdcSpecificInstrumentField * pSpecificInstrument, CThostFtdcRspInfoField * pRspInfo, int nRequestID, bool bIsLast)
{
}

void CtphqMdApi::OnRtnDepthMarketData(CThostFtdcDepthMarketDataField * pDepthMarketData)
{
	cout << "��Լ " << pDepthMarketData->InstrumentID << "  ���� " << pDepthMarketData->LastPrice << "  �ɽ��� " << pDepthMarketData->Volume
		<< "  ��һ�� " << pDepthMarketData->BidPrice1 << "��һ��" << pDepthMarketData->AskPrice1 << "  ��� " << pDepthMarketData->HighestPrice
		<< "  ��� " << pDepthMarketData->LowestPrice << "  ���� " << pDepthMarketData->OpenPrice << "  ʱ�� " << pDepthMarketData->UpdateTime << endl;

}

void CtphqMdApi::OnRtnForQuoteRsp(CThostFtdcForQuoteRspField * pForQuoteRsp)
{
}
