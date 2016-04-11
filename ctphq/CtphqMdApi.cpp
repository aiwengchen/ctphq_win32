#include <iostream>
#include "CtphqMdApi.h"
using namespace std;

//会员代码
TThostFtdcBrokerIDType g_chBrokerID;
//交易用户代码
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

//当客户端与交易托管系统通信连接断开时，该方法被调用
void CtphqMdApi::OnFrontDisconnected(int nReason)
{
	cout << "OnFrontDisconnected--请检查网络！" << endl;
}

void CtphqMdApi::OnHeartBeatWarning(int nTimeLapse)
{
}

void CtphqMdApi::OnRspUserLogin(CThostFtdcRspUserLoginField * pRspUserLogin, CThostFtdcRspInfoField * pRspInfo, int nRequestID, bool bIsLast)
{
	cout << "OnRspUserLogin:" << endl;
	cout << "ErrorCode=" << pRspInfo->ErrorID << " ErrorMsg=" << pRspInfo->ErrorMsg << endl;
	cout << "RequestID= " << nRequestID << "Chain=" << bIsLast << endl;
	//端登失败，客户端徐进行错误处理
	if (pRspInfo->ErrorID != 0)
	{
		cout << "Failed to login,errorcode=" << pRspInfo->ErrorID << "errormsg=" << pRspInfo->ErrorMsg << "requestid=" << nRequestID
			<< "chain=" << bIsLast << endl;
		exit(-1);
	}
	//端登成功
	//订阅行情
	char *Instrumnet[] = { "au1606","ag1606" };
	m_pUserApi->SubscribeMarketData(Instrumnet, 2);
	//退订行情
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
	cout << "出错啦！请检查" << endl;
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
	cout << "合约 " << pDepthMarketData->InstrumentID << "  最新 " << pDepthMarketData->LastPrice << "  成交量 " << pDepthMarketData->Volume
		<< "  买一价 " << pDepthMarketData->BidPrice1 << "卖一价" << pDepthMarketData->AskPrice1 << "  最高 " << pDepthMarketData->HighestPrice
		<< "  最低 " << pDepthMarketData->LowestPrice << "  开盘 " << pDepthMarketData->OpenPrice << "  时间 " << pDepthMarketData->UpdateTime << endl;

}

void CtphqMdApi::OnRtnForQuoteRsp(CThostFtdcForQuoteRspField * pForQuoteRsp)
{
}
