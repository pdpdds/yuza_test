#include <yuzaos.h>

extern "C" void InstallExceptionHandler();

int main(int argc, char* argv[])
{
	InstallExceptionHandler();

	try {		
		throw 100;
	}
	catch (int err)
	{
		printf("int value : %d\n", err);
	}

	return 0;
}