#include <yuzaos.h>
#include <iostream>
#include <AutoLock.h>

using namespace AutoLock;


int main(int argc, char* argv[])
{
	
	CLockableMutex cs("test_mutex");
	
	printf("autolock main end\n");
	return 0;
}