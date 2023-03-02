#include <Windows.h>
#include "Logger.h"

int main(void)
{
	setlocale(LC_ALL, "korean");

	LOG_WITH_WSAERROR(L"아니 뭔데");
	LOG(L"Not Bad");
	LOG(L"What are you doing man");
	LOG_WITH_WSAERROR(L"아무말이나 하는중");
	LOG_WITH_WSAERROR(L"영어랑 korean이랑도 섞어서 write");
	LOG(L"숫자도192385712398");

	int num = 5;
	WCHAR name[] = L"김도완";
	float floatNum = 1.62f;
	LOGF(L"num = %d, name = %s, floatNum = %f", num, name, floatNum);

	ASSERT_WITH_MESSAGE(1 > 0, L"1 > 0");
	ASSERT_WITH_MESSAGE(2 > 0, L"2 > 0");
	ASSERT_WITH_MESSAGE(3 > 0, L"3 > 0");
	ASSERT_WITH_MESSAGE(4 > 0, L"4 > 0");
	ASSERT_WITH_MESSAGE(5 > 0, L"5 > 0");
}