#include <windef.h>
#include <memory.h>
#include <stdio.h>
#include <string.h>
#include <winapi.h>
#include <systemcall_impl.h>
#include <math.h>

volatile LONG totalCount = 0;
///////////// Thread Main ///////////////////////
void ThreadMain(void* arg)
{
    int count = (int)arg;
    DWORD inc;

    for (int i = 0; i<count; i++)
    {
        inc = InterlockedIncrement((LPLONG)&totalCount);
    }
}

int main(int argc, char** argv)
{
    HANDLE hThreads[2];
    DWORD dwId, dwId2;

    int count = (rand() % 100) + 1;
    hThreads[0] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ThreadMain, (LPVOID)count, 0, &dwId);
    printf("Thread 1 Count : %d\n", count);
    int count2 = (rand() % 100) + 1;
    hThreads[1] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ThreadMain, (LPVOID)count2, 0, &dwId2);
    printf("Thread 2 Count : %d\n", count2);
    printf("Expected totalCount : %d\n", count + count2);

    DWORD result = WaitForMultipleObjects(2, hThreads, TRUE, INFINITE);
    
    printf("total count by child threads = %d\n", totalCount);

    CloseHandle(hThreads[0]);
    CloseHandle(hThreads[1]);

    return 0;
}