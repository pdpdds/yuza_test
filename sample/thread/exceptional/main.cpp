#include <stdio.h>
#include <GUIConsoleFramework.h>

#include "exceptional.h"
#include <assert.h>

int main_impl(int argc, char** argv)
{

	printf("-> simple try/catch with raise\n");

	volatile int testvar = 0;
	++testvar;
	try {
		printf("inside try\n");
		++testvar;
		throw(42);
		assert(false);
	}
	catch (err) {
		printf("catch: should be run, thrown error code: %d\n", err);
		assert(err == 42);
		++testvar;
	}
	++testvar;
	assert(testvar == 4);

	return 0;
}

int main(int argc, char** argv)
{
	GUIConsoleFramework framework;
	return framework.Run(argc, argv, main_impl);
}