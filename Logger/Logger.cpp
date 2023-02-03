// version 1.0.3
#pragma once

#include <WinSock2.h>
#include <iostream>
#include <time.h>
#include <cassert>

#include "Logger.h"

#define FILE_NAME_MAX_LENGTH 128

Logger Logger::mInstance;
FILE* Logger::mLogFile;

void Logger::LogMessage(const WCHAR* message)
{
	WCHAR dayInfo[FILE_NAME_MAX_LENGTH];
	getCurrentTimeInfo(dayInfo);
	fwprintf(mLogFile, L"[%s] : %s\n", dayInfo, message);
	fflush(mLogFile);
}

void Logger::LogMessage(const WCHAR* message, const char* fileName, int line)
{
	WCHAR dayInfo[FILE_NAME_MAX_LENGTH];
	getCurrentTimeInfo(dayInfo);

	WCHAR wFileName[FILE_NAME_MAX_LENGTH];
	MultiByteToWideChar(CP_ACP, MB_COMPOSITE, fileName, -1, wFileName, FILE_NAME_MAX_LENGTH);
	
	fwprintf(mLogFile, L"[%s][%s line:%4d] : %s\n", dayInfo, wFileName, line, message);
	fflush(mLogFile);
}

void Logger::LogMessageWithWSAError(const WCHAR* message)
{
	WCHAR dayInfo[FILE_NAME_MAX_LENGTH];
	getCurrentTimeInfo(dayInfo);

	fwprintf(mLogFile, L"[%s] : %s (Error : %d)\n", dayInfo, message, WSAGetLastError());
	fflush(mLogFile);
}

void Logger::LogMessageWithWSAError(const WCHAR* message, const char* fileName, int line)
{
	WCHAR dayInfo[FILE_NAME_MAX_LENGTH];
	getCurrentTimeInfo(dayInfo);

	WCHAR wFileName[FILE_NAME_MAX_LENGTH];
	MultiByteToWideChar(CP_ACP, MB_COMPOSITE, fileName, -1, wFileName, FILE_NAME_MAX_LENGTH);

	fwprintf(mLogFile, L"[%s][%s line:%4d] : %s (Error : %d)\n", dayInfo, wFileName, line, message, WSAGetLastError());
	fflush(mLogFile);
}

Logger::Logger()
{
	// get logFileName
	WCHAR dayInfo[FILE_NAME_MAX_LENGTH];
	WCHAR logFileName[FILE_NAME_MAX_LENGTH];

	getCurrentTimeInfo(dayInfo);
	wsprintf(logFileName, L"Log_%s.txt", dayInfo);

	if (_wfopen_s(&mLogFile, logFileName, L"w") == EINVAL)
	{
		assert(false);
		RaiseCrash();
	}
}

void Logger::getCurrentTimeInfo(WCHAR* buffer)
{
	time_t startTime = time(nullptr);
	tm localTime;
	localtime_s(&localTime, &startTime);

	int YYYY = localTime.tm_year + 1900;
	int MM = localTime.tm_mon + 1;
	int DD = localTime.tm_mday;
	int hh = localTime.tm_hour;
	int mm = localTime.tm_min;
	int ss = localTime.tm_sec;
	wsprintf(buffer, L"%04d%02d%02d_%02d%02d%02d", YYYY, MM, DD, hh, mm, ss);
}

Logger::~Logger()
{
	fclose(mLogFile);
}

void Logger::RaiseCrash()
{
	int* nullPointer = 0x00000000;
	*nullPointer = 0;
}