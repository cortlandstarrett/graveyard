// doze.cpp: suspends execution for the number of seconds
// specified by the command-line argument
#include <iostream.h>
#include <windows.h>

int main(int argc, char** argv)
{
	if (argc != 2) {  // check for command-line argument
		cout << "USAGE: " << argv[0] << " <seconds>\n";
		return 1;
	}

	Sleep(atoi(argv[1])*1000);

	return 0;
}

