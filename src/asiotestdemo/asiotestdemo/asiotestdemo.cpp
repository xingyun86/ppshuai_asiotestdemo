// asiotestdemo.cpp : Defines the entry point for the application.
//

#include "asiotestdemo.h"
#include <chat_server.h>

using namespace std;

int main(int argc, char ** argv)
{
	cout << "Hello CMake." << endl;
	chat_server_main(argc, argv);
	return 0;
}
