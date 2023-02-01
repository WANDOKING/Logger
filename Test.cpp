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
		LogWithWSAError("GetAddrInfo() error!");
		Crash();
	}

	ADDRINFOW* traversal = addrInfo;
	while (traversal != nullptr)
	{
		SOCKADDR_IN* sockAddr = (SOCKADDR_IN*)traversal->ai_addr;

		WCHAR buffer[16] = { 0 };
		if (InetNtop(AF_INET, &sockAddr->sin_addr, buffer, 16) == nullptr)
		{
			LogWithWSAError("InetNtop() error!");
			Crash();
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
		LogWithWSAError("WSAStartup() error!");
		Crash();
	}

	PrintDomainToIps(L"gosoasgle.com");

	WSACleanup();
}