#include <iostream>
#include "CtphqMdApi.h"
using namespace std;
#pragma comment(lib,"../Api/md/thostmduserapi.lib")


int main()
{
	CThostFtdcMdApi *pUserApi = CThostFtdcMdApi::CreateFtdcMdApi("",false,false);

	CtphqMdApi pSpi(pUserApi);

	pUserApi->RegisterSpi(&pSpi);


	pUserApi->RegisterFront("tcp://180.168.146.187:10010");

	pUserApi->Init();

	pUserApi->Join();

	return 0;
}