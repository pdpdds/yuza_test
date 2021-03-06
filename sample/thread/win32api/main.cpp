#include <minwindef.h>
#include <minwinconst.h>
#include <memory.h>
#include <stdio.h>
#include <string.h>
#include <winapi.h>
#include <systemcall_impl.h>
#include "GUIConsoleFramework.h"

int main_impl(int argc, char** argv)
{
	if (argc < 2)
		return 0;

	HANDLE hFile = 0;
	DWORD readCount = 0;
	BOOL result = 0;
	char buf[MAX_PATH];

	hFile = CreateFile(argv[1], GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	if (hFile == INVALID_HANDLE_VALUE)
	{
		printf("File %s Open Error (%d) : %s\n", Syscall_GetLastError(), argv[1]);
		return 1;
	}

	while (1)
	{
		memset((void*)buf, 0, MAX_PATH);
		result = ReadFile(hFile, buf, MAX_PATH - 1, &readCount, NULL);

		if (result == 0 || readCount == 0)
		{
			break;
		}
		printf("%s\n", buf);
	}

	CloseHandle(hFile);

	SYSTEMTIME timeInfo;
	GetSystemTime(&timeInfo);

	printf("Time %d/%d/%d %d:%d:%d\n", timeInfo.wYear, timeInfo.wMonth, timeInfo.wDay, timeInfo.wHour, timeInfo.wMinute, timeInfo.wSecond);

	return 0;
}

int main(int argc, char** argv)
{
	GUIConsoleFramework framework;
	framework.Run(argc, argv, main_impl);
}