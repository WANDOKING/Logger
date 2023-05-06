// version 3.0.0
#pragma once

#include <iostream>

typedef wchar_t WCHAR;
typedef void* HANDLE;

/************ recommend call this macros instead of Logger::functions ************/
#define LOG(Level, Log) Logger::LogMessage(Level, Log)
#define LOG_WITH_LINE(Level, Log) Logger::LogMessage((Level), (Log), __FILEW__, __LINE__)
#define LOGF Logger::LogF

#define ASSERT_LIVE(Condition, Message) Logger::Assert((Condition), (Message), __FILEW__, __LINE__)
/*********************************************************************************/

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
	inline static void SetLogLevel(ELogLevel logLevel) { mLogLevel = logLevel; }

	static void LogMessage(ELogLevel logLevel, const WCHAR* message);
	static void LogMessage(ELogLevel logLevel, const WCHAR* message, const WCHAR* fileName, int line);
	static void LogF(ELogLevel logLevel, const WCHAR* formatMessage, ...);

	inline static void Assert(bool condition, const WCHAR* message)
	{
		if (!condition)
		{
			LogMessage(ELogLevel::Assert, message);
			RaiseCrash();
		}
	}

	inline static void Assert(bool condition, const WCHAR* message, const WCHAR* fileName, int line)
	{
		if (!condition)
		{
			LogMessage(ELogLevel::Assert, message, fileName, line);
			RaiseCrash();
		}
	}

	// intentional crash
	static void RaiseCrash();
private:
	Logger();
	~Logger();

	static void getCurrentTimeInfo(WCHAR* outBuffer);

	static Logger mInstance;
	static HANDLE mhLogFile;
	static ELogLevel mLogLevel;
};