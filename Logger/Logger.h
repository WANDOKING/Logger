// version 4.0.0
#pragma once

#include <iostream>

/*************************** recommend call this macros instead of Logger::functions ***************************/

#define LOG(Level, Log)			Logger::LogMessage(Level, Log)
#define LOGL(Level, Log)		Logger::LogMessageWithLine((Level), (Log), __FILEW__, __LINE__)
#define LOGF(Level, Log, ...)	Logger::LogFormat((Level), (Log), __VA_ARGS__)
#define LOGFL(Level, Log, ...)	Logger::LogFormatWithLine((Level), (Log), __FILEW__, __LINE__, __VA_ARGS__)

// 라이브 Assert 함수 - 어설션 실패 시 로그를 남기고 크래시
#define LASSERT(Condition, Message) Logger::Assert((Condition), (Message), __FILEW__, __LINE__)

/***************************************************************************************************************/

typedef wchar_t WCHAR;
typedef void* HANDLE;

enum class ELogLevel
{
	Test = 0,
	Debug = 1,
	System = 10,
	Error = 99,
	Assert,
};

class Logger
{
public:
	inline static ELogLevel GetLogLevel(ELogLevel logLevel) { return logLevel; }
	inline static void		SetLogLevel(ELogLevel logLevel) { mLogLevel = logLevel; }
	
	static void LogMessage(ELogLevel logLevel, const WCHAR* message);
	static void LogMessageWithLine(ELogLevel logLevel, const WCHAR* message, const WCHAR* fileName, int line);

	static void LogFormat(ELogLevel logLevel, const WCHAR* formatMessage, ...);
	static void LogFormatWithLine(ELogLevel logLevel, const WCHAR* formatMessage, const WCHAR* fileName, int line, ...);

	inline static void Assert(bool condition, const WCHAR* message)
	{
		if (!condition)
		{
			LogMessage(ELogLevel::Assert, message);
			Crash();
		}
	}
	
	inline static void Assert(bool condition, const WCHAR* message, const WCHAR* fileName, int line)
	{
		if (!condition)
		{
			LogMessageWithLine(ELogLevel::Assert, message, fileName, line);
			Crash();
		}
	}

	// intentional crash
	static void Crash();
private:
	Logger();
	~Logger();

	static void getCurrentTimeInfo(WCHAR* outBuffer);

	static Logger mInstance;
	static HANDLE mhLogFile;
	static ELogLevel mLogLevel;
};