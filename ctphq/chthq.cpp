#include <iostream>
#include "CtphqMdApi.h"
using namespace std;
#pragma comment(lib,"../Api/md/thostmduserapi.lib")


int main()
{
	CThostFtdcMdApi *pUserApi = CThostFtdcMdApi::CreateFtdcMdApi();

	CtphqMdApi sh(pUserApi);

	pUserApi->RegisterSpi(&sh);


	pUserApi->RegisterFront("tcp://180.168.146.187:10010");

	pUserApi->Init();

	pUserApi->Join();

	pUserApi->Release();

	return 0;
}