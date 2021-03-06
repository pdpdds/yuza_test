#include <windef.h>
#include <minwindef.h>
#include <winapi.h>
#include <stdio.h>

#define MAX_THREADS  2
CRITICAL_SECTION cs;

DWORD CS_TotalCount = 0;
DWORD TotalCount = 0;

void IncreaseCount()
{
	TotalCount++;
	EnterCriticalSection(&cs);

	CS_TotalCount++;
	LeaveCriticalSection(&cs);
}

unsigned int __stdcall ThreadProc(LPVOID lpParam)
{
	for (DWORD i = 0; i < 1000; i++)
	{
		IncreaseCount();
	}

	return 0;
}

int main(int argc, char* argv[])
{
	DWORD dwThreadId[MAX_THREADS];
	HANDLE hThread[MAX_THREADS];

	InitializeCriticalSection(&cs);
	
	for (DWORD i = 0; i < MAX_THREADS; i++)
	{
		hThread[i] = (HANDLE)_beginthreadex(NULL, 0, ThreadProc, NULL, CREATE_SUSPENDED, (unsigned*)&dwThreadId[i]);
		if (hThread[i] == NULL)
		{
			printf("Thread creation fault!! %d\n", hThread[i]);
			return -1;
		}
	}

	//for (DWORD i = 0; i < MAX_THREADS; i++)
		//ResumeThread(hThread[i]);

	printf("waitfor\n");
	WaitForMultipleObjects(MAX_THREADS, hThread, TRUE, INFINITE);

	for (DWORD i = 0; i < MAX_THREADS; i++)
		CloseHandle(hThread[i]);

	printf("   Critical_section total count : %d\n", CS_TotalCount);
	printf("   non critical_section total count : %d\n   ", TotalCount);

	DeleteCriticalSection(&cs);

	return 0;
}