// version 1.0.3
#pragma once

#define LOG(M) Logger::LogMessage((M), __FILE__, __LINE__)
#define LOG_WITH_WSAERROR(M) Logger::LogMessageWithWSAError((M), __FILE__, __LINE__)
#define CRASH() Logger::RaiseCrash()

#pragma warning(push)
#pragma warning(disable: 6011) // raiseCrash 함수의 경고를 무시한다

class Logger
{
public:
	static void LogMessage(const WCHAR* message);
	static void LogMessage(const WCHAR* message, const char* fileName, int line);
	static void LogMessageWithWSAError(const WCHAR* message);
	static void LogMessageWithWSAError(const WCHAR* message, const char* fileName, int line);

	// intentional crash
	static void RaiseCrash();
private:
	Logger();
	~Logger();

	static void getCurrentTimeInfo(WCHAR* buffer);

	static Logger mInstance;
	static FILE* mLogFile;
};

#pragma warning(pop)
