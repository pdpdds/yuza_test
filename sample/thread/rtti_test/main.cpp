#include <yuzaos.h>
#include <iostream>
#include <typeinfo>
#include <Excpt.h>

using namespace std;

class Base_Class
{
public:
	virtual void DummyFunc() 
	{
		cout << "Base_Class Call!" << endl;
	}
};

class Derived_Class : public Base_Class 
{ 
public:
	int m_testData; 
	virtual void DummyFunc() override
	{
		cout << "Derived_Class Call!" << endl;
	}
};

int main_impl(int argc, char** argv)
{	
	cout << "Dynamic Cast Test" << endl;

	Exc::SetFrameHandler(true);
	Exc::SetThrowFunction(true);

	try
	{
		cout << "typeid Derived_Class " << typeid(Derived_Class).name() << endl;

		Base_Class* ptr_a = new Derived_Class();
		Base_Class* ptr_b = new Base_Class;
		Derived_Class* ptr_c;

		ptr_c = dynamic_cast<Derived_Class*>(ptr_a);
		if (ptr_c == 0) cout << "Null pointer on first type-cast" << endl;

		ptr_c = dynamic_cast<Derived_Class*>(ptr_b);
		if (ptr_c == 0) cout << "Null pointer on second type-cast" << endl;

		throw(1.5f);
	}
	catch (float ex)
	{
		cout << "Exception Catch " << ex << endl;
	}	

	cout << "main terminated" << endl;

	return 0;
}

int main(int argc, char** argv)
{
	GUIConsoleFramework framework;
	return framework.Run(argc, argv, main_impl);
}