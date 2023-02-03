#pragma comment(lib, "ws2_32")

#include <cassert>
#include <iostream>
#include <WinSock2.h>
#include <ws2tcpip.h>

#include "Logger.h"

BOOL PrintDomainToIps(const WCHAR* domain)
{
	ADDRINFOW* addrInfo;
	if (GetAddrInfo(domain, L"0", nullptr, &addrInfo) != 0)
	{
		LOG_WITH_WSAERROR("GetAddrInfo() error!");
		CRASH();
	}

	ADDRINFOW* traversal = addrInfo;
	while (traversal != nullptr)
	{
		SOCKADDR_IN* sockAddr = (SOCKADDR_IN*)traversal->ai_addr;

		WCHAR buffer[16] = { 0 };
		if (InetNtop(AF_INET, &sockAddr->sin_addr, buffer, 16) == nullptr)
		{
			LOG_WITH_WSAERROR("InetNtop() error!");
			CRASH();
		}

		std::wcout << buffer << '\n';

		traversal = traversal->ai_next;
	}

	FreeAddrInfo(addrInfo);

	return TRUE;
}

int main(void)
{
	WSADATA wsaData;

	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
	{
		LOG_WITH_WSAERROR("WSAStartup() error!");
		CRASH();
	}

	PrintDomainToIps(L"gosoasgle.com");

	WSACleanup();
}