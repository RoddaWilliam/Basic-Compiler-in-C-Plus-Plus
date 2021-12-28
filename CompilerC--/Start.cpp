// CompilerC--.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <windows.h>
#include <string>
#include "Compiler.cpp"

using namespace std;

int main()
{
	// Check if file name is null in case user didnt give us it.

	Compile("CompileMe", "output");
	return 0;
}
