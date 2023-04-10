#include "Logger.h"

int main(void)
{
	setlocale(LC_ALL, "korean");

	Logger::SetLogLevel(ELogLevel::System);

	for (int i = 0; i < 10; ++i)
	{
		LOGF(ELogLevel::Debug, L"Debug i = %d", i);
		LOGF(ELogLevel::Error, L"Error i = %d", i);
		LOGF(ELogLevel::System, L"System i = %d", i);
	}
}