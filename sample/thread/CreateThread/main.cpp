#include <windef.h>
#include <minwindef.h>
#include <winapi.h>
#include <stdio.h>

DWORD WINAPI MyThreadFunction(LPVOID lpParam)
{
    printf("The parameter: %u\n", *(DWORD*)lpParam);

    return 0;
}

DWORD dwThreadId = 1;
DWORD dwThrdParam = 1;

int main(int argc, char* argv[])
{
    HANDLE hThread = CreateThread(NULL, 0, MyThreadFunction, &dwThrdParam, 0, &dwThreadId);

    printf("The thread ID: %d\n", dwThreadId);

    CloseHandle(hThread);
      
    return 0;
}