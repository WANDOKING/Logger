// version 3.0.0
#pragma comment(lib, "pathcch.lib")

#include "Logger.h"

#include <time.h>
#include <Windows.h>
#include <strsafe.h>

#define LOG_MESSAGE_MAX_LENGTH 512
#define DAY_INFO_BUFFER_LENGTH 16

Logger Logger::mInstance;
HANDLE Logger::mhLogFile;
ELogLevel Logger::mLogLevel = ELogLevel::Debug;

// Write log to console macro
#define LOG_TO_CONSOLE(Log) wprintf(Log)

// Write log to log file macro
#define LOG_TO_FILE(Log) do {																					\
	if (::WriteFile(mhLogFile, (Log), (DWORD)(wcslen(Log) * sizeof(WCHAR)), nullptr, nullptr) == FALSE)			\
	{																											\
		wprintf(L"[!] File Logging ERROR - GetLastError() = %d\n", GetLastError());								\
	}																											\
																												\
	::FlushFileBuffers(mhLogFile);																				\
} while (false)																									\

void Logger::LogMessage(ELogLevel logLevel, const WCHAR* message)
{
	if (mLogLevel > logLevel)
	{
		return;
	}

	WCHAR log[LOG_MESSAGE_MAX_LENGTH];
	WCHAR dayInfo[DAY_INFO_BUFFER_LENGTH];
	getCurrentTimeInfo(dayInfo);

	::StringCchPrintfW(log, LOG_MESSAGE_MAX_LENGTH, L"[%s] %s\n", dayInfo, message);
	
	LOG_TO_CONSOLE(log);
	LOG_TO_FILE(log);
}

void Logger::LogMessageWithLine(ELogLevel logLevel, const WCHAR* message, const WCHAR* fileName, int line)
{
	if (mLogLevel > logLevel)
	{
		return;
	}

	WCHAR log[LOG_MESSAGE_MAX_LENGTH];
	WCHAR dayInfo[DAY_INFO_BUFFER_LENGTH];
	getCurrentTimeInfo(dayInfo);

	::StringCchPrintfW(log, LOG_MESSAGE_MAX_LENGTH, L"[%s] [%s line:%4d] %s\n", dayInfo, fileName, line, message);

	LOG_TO_CONSOLE(log);
	LOG_TO_FILE(log);
}

void Logger::LogFormat(ELogLevel logLevel, const WCHAR* formatMessage, ...)
{
	if (mLogLevel > logLevel)
	{
		return;
	}

	WCHAR completedMessage[LOG_MESSAGE_MAX_LENGTH];

	va_list ap;
	va_start(ap, formatMessage);
	{
		::StringCchVPrintfW(completedMessage, LOG_MESSAGE_MAX_LENGTH, formatMessage, ap);
	}
	va_end(ap);

	Logger::LogMessage(logLevel, completedMessage);
}

void Logger::LogFormatWithLine(ELogLevel logLevel, const WCHAR* formatMessage, const WCHAR* fileName, int line, ...)
{
	if (mLogLevel > logLevel)
	{
		return;
	}

	WCHAR completedMessage[LOG_MESSAGE_MAX_LENGTH];

	va_list ap;
	va_start(ap, line);
	{
		::StringCchVPrintfW(completedMessage, LOG_MESSAGE_MAX_LENGTH, formatMessage, ap);
	}
	va_end(ap);

	Logger::LogMessageWithLine(logLevel, completedMessage, fileName, line);
}

void Logger::getCurrentTimeInfo(WCHAR* outBuffer)
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
	::StringCchPrintfW(outBuffer, DAY_INFO_BUFFER_LENGTH, L"%04d%02d%02d_%02d%02d%02d", YYYY, MM, DD, hh, mm, ss);
}

Logger::Logger()
{
	WCHAR fileName[_MAX_PATH * 2];

	// get logFileName
	WCHAR dayInfo[DAY_INFO_BUFFER_LENGTH];
	getCurrentTimeInfo(dayInfo);

	// get process path
	DWORD dwPID = ::GetCurrentProcessId();
	HANDLE hProcess = ::OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, dwPID);
	WCHAR processPath[MAX_PATH];
	if (::GetModuleFileNameW(nullptr, processPath, MAX_PATH) == 0)
	{
		::CloseHandle(hProcess);
		exit(1);
	}
	::CloseHandle(hProcess);

	wsprintfW(fileName, L"%s Log", processPath);
	::CreateDirectoryW(fileName, nullptr); // create directory

	wsprintfW(processPath, L"%s", fileName); // path update (log file directory)
	wsprintfW(fileName, L"%s\\Log_%s.txt", processPath, dayInfo); // log file path

	mhLogFile = CreateFile(fileName, GENERIC_WRITE, FILE_SHARE_READ, nullptr, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);
	if (mhLogFile == INVALID_HANDLE_VALUE)
	{
		printf("CreateFile() Failed %d\n", GetLastError());
		Crash();
	}

	// Write BOM
	unsigned short BOM_UTF_16_LE = 0xFEFF;
	::WriteFile(mhLogFile, &BOM_UTF_16_LE, sizeof(BOM_UTF_16_LE), nullptr, nullptr);
}

Logger::~Logger()
{
	::CloseHandle(mhLogFile);
}

#pragma warning(push)
#pragma warning(disable: 6011)
void Logger::Crash()
{
	*((int*)nullptr) = 0xDEADDEAD;
}
#pragma warning(pop)