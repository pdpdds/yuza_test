#include "Excpt.h"

int main(int argc, char* argv[])
{
	Exc::SetFrameHandler(true);
	Exc::SetThrowFunction(true);

	try {
		
		throw 100;

	}
	catch (int err)
	{
		int j = err;
	}

	return 0;
}