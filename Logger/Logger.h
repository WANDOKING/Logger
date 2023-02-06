// version 1.0.4
#pragma once

#define LOG(M) Logger::LogMessage((M), __FILE__, __LINE__)
#define LOG_WITH_WSAERROR(M) Logger::LogMessageWithWSAError((M), __FILE__, __LINE__)
#define CRASH() Logger::RaiseCrash()

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