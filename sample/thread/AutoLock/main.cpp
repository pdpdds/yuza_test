#include <yuzaos.h>
#include <iostream>
#include <AutoLock.h>
#include <Excpt.h>

using namespace AutoLock;


int main(int argc, char* argv[])
{
	Exc::SetFrameHandler(true);
	Exc::SetThrowFunction(true);

	CLockableMutex cs("test_mutex");
	
	printf("autolock main end\n");
	return 0;
}