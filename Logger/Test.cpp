#pragma comment(lib, "ws2_32")

#include <cassert>
#include <iostream>
#include <WinSock2.h>
#include <ws2tcpip.h>

#include "Logger.h"

int main(void)
{
	setlocale(LC_ALL, "KOREAN");

	LOG(L"hi");
	LOG(L"OK");

	LOG(L"why are you crying");
	LOG(L"한글 로그");

	LOG_WITH_WSAERROR(L"log with wsaerror");

	{
		int a = 5;
		ASSERT_WITH_MESSAGE(a < 0, L"뭔가 이상하다 Assetion Failed");
	}
}