#include <yuzaos.h>
#include <iostream>
#include <typeinfo>

using namespace std;

extern "C" void InstallExceptionHandler();


#define BUFSIZE 2000000


int main_impl(int argc, char** argv)
{	
	cout << "Check Stack" << endl;	

	InstallExceptionHandler();

	char buf[BUFSIZE];

	buf[BUFSIZE-1] = 0;

	
	cout << "main terminated" << endl;

	return 0;
}

int main(int argc, char** argv)
{	
	GUIConsoleFramework framework;
	return framework.Run(argc, argv, main_impl);
}