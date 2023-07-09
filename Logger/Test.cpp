#include "Logger.h"
#include <Windows.h>
#include <process.h>
#include <iostream>

unsigned int WriteThread(void* param)
{
	for (int i = 0; i < 1000; ++i)
	{
		LOGFL(ELogLevel::System, L"I am Thread %u", GetCurrentThreadId());
	}

	return 0;
}

void LogLevelTest()
{
	Logger::SetLogLevel(ELogLevel::System);

	for (int i = 0; i < 10; ++i)
	{
		LOGF(ELogLevel::Debug, L"Debug i = %d", i);
		LOGF(ELogLevel::Error, L"Error i = %d", i);
		LOGF(ELogLevel::System, L"System i = %d", i);
	}
}

void ThreadSafeTest()
{
	const int THREAD_COUNT = 4;
	HANDLE threads[THREAD_COUNT]{};

	for (int i = 0; i < THREAD_COUNT; ++i)
	{
		threads[i] = (HANDLE)_beginthreadex(nullptr, 0, WriteThread, nullptr, 0, nullptr);
	}

	WaitForMultipleObjects(THREAD_COUNT, threads, TRUE, INFINITE);
	wprintf(L"Test Complete\n");
}

int main(void)
{
	ThreadSafeTest();
}