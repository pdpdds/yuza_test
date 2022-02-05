#include <yuzaos.h>
#include <iostream>
#include <typeinfo>

using namespace std;

extern "C" void InstallExceptionHandler();

class BaseClass
{
public:
	virtual void DummyFunc() 
	{
		cout << "Base_Class Call!" << endl;
	}
};

class DerivedClass : public BaseClass 
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

	InstallExceptionHandler();

	try
	{
		cout << "typeid DerivedClass : " << typeid(DerivedClass).name() << endl;

		BaseClass* ptr_a = new DerivedClass();
		BaseClass* ptr_b = new BaseClass;
		DerivedClass* ptr_c;

		ptr_c = dynamic_cast<DerivedClass*>(ptr_a);
		if (ptr_c == 0) cout << "Null pointer on first type-cast" << endl;

		ptr_c = dynamic_cast<DerivedClass*>(ptr_b);
		if (ptr_c == 0) cout << "Null pointer on second type-cast" << endl;

		//throw(1.5f);

		DerivedClass* p = nullptr;
		std::cout << typeid(*p).name() << '\n';
	}
	catch (float ex)
	{
		cout << "Exception Catch " << ex << endl;
	}		
	catch (const std::bad_typeid& e) {
		std::cout << e.what() << '\n';
	}

	cout << "main terminated" << endl;

	return 0;
}

int main(int argc, char** argv)
{	
	GUIConsoleFramework framework;
	return framework.Run(argc, argv, main_impl);
}