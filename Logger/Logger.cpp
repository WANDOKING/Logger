// version 1.0.2
#pragma once

#include <WinSock2.h>
#include <iostream>
#include <time.h>
#include <cassert>

#include "Logger.h"

#define FILE_NAME_MAX_LENGTH 128

Logger Logger::mInstance;
FILE* Logger::mLogFile;

void Logger::LogMessage(const char* message)
{
	char dayInfo[FILE_NAME_MAX_LENGTH];
	getCurrentTimeInfo(dayInfo);
	fprintf(mLogFile, "[%s] : %s\n", dayInfo, message);
	fflush(mLogFile);
}

void Logger::LogMessage(const char* message, const char* fileName, int line)
{
	char dayInfo[FILE_NAME_MAX_LENGTH];
	getCurrentTimeInfo(dayInfo);
	fprintf(mLogFile, "[%s][%s line:%4d] : %s\n", dayInfo, fileName, line, message);
	fflush(mLogFile);
}

void Logger::LogMessageWithWSAError(const char* message)
{
	char dayInfo[FILE_NAME_MAX_LENGTH];
	getCurrentTimeInfo(dayInfo);
	fprintf(mLogFile, "[%s] : %s (Error : %d)\n", dayInfo, message, WSAGetLastError());
	fflush(mLogFile);
}

void Logger::LogMessageWithWSAError(const char* message, const char* fileName, int line)
{
	char dayInfo[FILE_NAME_MAX_LENGTH];
	getCurrentTimeInfo(dayInfo);
	fprintf(mLogFile, "[%s][%s line:%4d] : %s (Error : %d)\n", dayInfo, fileName, line, message, WSAGetLastError());
	fflush(mLogFile);
}

Logger::Logger()
{
	// get logFileName
	char dayInfo[FILE_NAME_MAX_LENGTH];
	char logFileName[FILE_NAME_MAX_LENGTH];

	getCurrentTimeInfo(dayInfo);
	sprintf_s(logFileName, FILE_NAME_MAX_LENGTH, "Log_%s.txt", dayInfo);

	if (fopen_s(&mLogFile, logFileName, "w") == EINVAL)
	{
		assert(false);
		RaiseCrash();
	}
}

void Logger::getCurrentTimeInfo(char* buffer)
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
	sprintf_s(buffer, FILE_NAME_MAX_LENGTH, "%04d%02d%02d_%02d%02d%02d", YYYY, MM, DD, hh, mm, ss);
}

Logger::~Logger()
{
	fclose(mLogFile);
}
