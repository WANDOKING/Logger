#pragma comment(lib, "ws2_32")

#include "Logger.h"

int main(void)
{
	Logger::LogF(L"hello my name is %s", L"Minsu");

	LOG_WITH_WSAERROR(L"OK good");

	LOG_WITH_WSAERROR(L"Not Bad");
}