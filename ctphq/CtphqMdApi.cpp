#include <iostream>
#include "CtphqMdApi.h"
using namespace std;


///���ͻ����뽻�׺�̨������ͨ������ʱ����δ��¼ǰ�����÷��������á�
void CtphqMdApi::OnFrontConnected()
{
	//user login
	CThostFtdcReqUserLoginField  m_reqUserLogin;
	//Broker
	TThostFtdcBrokerIDType  m_chBrokerID = "9999";
	//userID
	TThostFtdcUserIDType  m_UserID = "015809";
	//password
	TThostFtdcPasswordKeyType  m_Password = "12qwasZX";

	strcpy_s(m_reqUserLogin.BrokerID, m_chBrokerID);
	strcpy_s(m_reqUserLogin.UserID, m_UserID);
	strcpy_s(m_reqUserLogin.Password, m_Password);

	m_pUserApi->ReqUserLogin(&m_reqUserLogin, 0);
}

///���ͻ����뽻�׺�̨ͨ�����ӶϿ�ʱ���÷��������á���������������API���Զ��������ӣ��ͻ��˿ɲ�������
///@param nReason ����ԭ��
///        0x1001 �����ʧ��
///        0x1002 ����дʧ��
///        0x2001 ����������ʱ
///        0x2002 ��������ʧ��
///        0x2003 �յ�������
void CtphqMdApi::OnFrontDisconnected(int nReason)
{
}

///������ʱ���档����ʱ��δ�յ�����ʱ���÷��������á�
///@param nTimeLapse �����ϴν��ձ��ĵ�ʱ��
void CtphqMdApi::OnHeartBeatWarning(int nTimeLapse)
{
	nTimeLapse = 5;
}


///��¼������Ӧ
void CtphqMdApi::OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	if (pRspInfo->ErrorID != 0)
	{
		cerr << "Failed to Login!" << endl;
		cerr << "Errorcode= " << pRspInfo->ErrorID << "  Errormsg= " << pRspInfo->ErrorMsg << endl;
		cerr << "RequestID= " << nRequestID << "  chain= " << bIsLast << endl;
		exit(-1);
	}
	else
	{
		cerr << "Login in OK:" <<" TradingDay= " << pRspUserLogin->TradingDay << endl;
	
		///�������顣
		///@param ppInstrumentID ��ԼID
		///@param nCount Ҫ����/�˶�����ĺ�Լ����
		///@remark
		char *pInstrumentID[] = { "au1606","ag1606" };
		int iCount = 2;
		m_pUserApi->SubscribeMarketData(pInstrumentID, iCount);
		
		///�˶����顣
		///@param ppInstrumentID ��ԼID
		///@param nCount Ҫ����/�˶�����ĺ�Լ����
		///@remark
		//m_pUserApi->UnSubscribeMarketData(pInstrumentID, iCount);

	}
}



///�ǳ�������Ӧ
void CtphqMdApi::OnRspUserLogout(CThostFtdcUserLogoutField *pUserLogout, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	cerr << "GoodBye!" << pUserLogout->UserID << endl;
}

///����Ӧ��
void CtphqMdApi::OnRspError(CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	cout << "OnRspError! errorcode=" << pRspInfo->ErrorID << "errormsg=" << pRspInfo->ErrorMsg << "requestid=" << nRequestID
		<< "chain=" << bIsLast << endl;
	cout << "������������" << endl;
}

///��������Ӧ��
void CtphqMdApi::OnRspSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	cerr << "OK " << pSpecificInstrument->InstrumentID << endl;
}

///ȡ����������Ӧ��
void CtphqMdApi::OnRspUnSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	cerr << "OVER " << pSpecificInstrument->InstrumentID << endl;
}

///�������֪ͨ
void CtphqMdApi::OnRtnDepthMarketData(CThostFtdcDepthMarketDataField *pDepthMarketData)
{
	cerr << pDepthMarketData->InstrumentID << "  " << pDepthMarketData->LastPrice << "  " << pDepthMarketData->Volume << "  " << pDepthMarketData->OpenInterest << "  "
		<< pDepthMarketData->BidPrice1 << "  " << pDepthMarketData->AskPrice1 << "  " << pDepthMarketData->OpenPrice << "  " << pDepthMarketData->HighestPrice << "  "
		<< pDepthMarketData->LowestPrice << "  " << pDepthMarketData->TradingDay << "  " << pDepthMarketData->UpdateTime << endl;
}
