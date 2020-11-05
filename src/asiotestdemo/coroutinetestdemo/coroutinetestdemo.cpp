// coroutinetestdemo.cpp : Defines the entry point for the application.
//

#include "coroutinetestdemo.h"
#include <coroutinetestdemo_imp.h>
int main(int argc, char ** argv)
{
	std::cout << "Hello CMake." << std::endl;
	coroutine_test_main();
	return 0;
}
