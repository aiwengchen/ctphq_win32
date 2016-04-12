#include <iostream>
#include "CtphqMdApi.h"
using namespace std;


///当客户端与交易后台建立起通信连接时（还未登录前），该方法被调用。
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

///当客户端与交易后台通信连接断开时，该方法被调用。当发生这个情况后，API会自动重新连接，客户端可不做处理。
///@param nReason 错误原因
///        0x1001 网络读失败
///        0x1002 网络写失败
///        0x2001 接收心跳超时
///        0x2002 发送心跳失败
///        0x2003 收到错误报文
void CtphqMdApi::OnFrontDisconnected(int nReason)
{
}

///心跳超时警告。当长时间未收到报文时，该方法被调用。
///@param nTimeLapse 距离上次接收报文的时间
void CtphqMdApi::OnHeartBeatWarning(int nTimeLapse)
{
	nTimeLapse = 5;
}


///登录请求响应
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
	
		///订阅行情。
		///@param ppInstrumentID 合约ID
		///@param nCount 要订阅/退订行情的合约个数
		///@remark
		char *pInstrumentID[] = { "au1606","ag1606" };
		int iCount = 2;
		m_pUserApi->SubscribeMarketData(pInstrumentID, iCount);
		
		///退订行情。
		///@param ppInstrumentID 合约ID
		///@param nCount 要订阅/退订行情的合约个数
		///@remark
		//m_pUserApi->UnSubscribeMarketData(pInstrumentID, iCount);

	}
}



///登出请求响应
void CtphqMdApi::OnRspUserLogout(CThostFtdcUserLogoutField *pUserLogout, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	cerr << "GoodBye!" << pUserLogout->UserID << endl;
}

///错误应答
void CtphqMdApi::OnRspError(CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	cout << "OnRspError! errorcode=" << pRspInfo->ErrorID << "errormsg=" << pRspInfo->ErrorMsg << "requestid=" << nRequestID
		<< "chain=" << bIsLast << endl;
	cout << "出错啦！请检查" << endl;
}

///订阅行情应答
void CtphqMdApi::OnRspSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	cerr << "OK " << pSpecificInstrument->InstrumentID << endl;
}

///取消订阅行情应答
void CtphqMdApi::OnRspUnSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	cerr << "OVER " << pSpecificInstrument->InstrumentID << endl;
}

///深度行情通知
void CtphqMdApi::OnRtnDepthMarketData(CThostFtdcDepthMarketDataField *pDepthMarketData)
{
	cerr << pDepthMarketData->InstrumentID << "  " << pDepthMarketData->LastPrice << "  " << pDepthMarketData->Volume << "  " << pDepthMarketData->OpenInterest << "  "
		<< pDepthMarketData->BidPrice1 << "  " << pDepthMarketData->AskPrice1 << "  " << pDepthMarketData->OpenPrice << "  " << pDepthMarketData->HighestPrice << "  "
		<< pDepthMarketData->LowestPrice << "  " << pDepthMarketData->TradingDay << "  " << pDepthMarketData->UpdateTime << endl;
}
