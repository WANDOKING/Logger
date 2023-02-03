// version 1.0.0
#pragma once

#define Log(M) Logger::LogMessage((M), __FILE__, __LINE__)
#define LogWithWSAError(M) Logger::LogMessageWithWSAError((M), __FILE__, __LINE__)
#define Crash() Logger::RaiseCrash()

#pragma warning(push)
#pragma warning(disable: 6011) // raiseCrash 함수의 경고를 무시한다

class Logger
{
public:
	static void LogMessage(const char* message);
	static void LogMessage(const char* message, const char* fileName, int line);
	static void LogMessageWithWSAError(const char* message);
	static void LogMessageWithWSAError(const char* message, const char* fileName, int line);

	// intentional crash
	inline static void RaiseCrash()
	{
		int* nullPointer = 0x00000000;
		*nullPointer = 0;
	}
private:
	Logger();
	~Logger();

	static void getCurrentTimeInfo(char* buffer);

	static Logger mInstance;
	static FILE* mLogFile;
};

#pragma warning(pop)
