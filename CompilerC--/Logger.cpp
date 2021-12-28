#include <iostream>
#include <fstream>
#include <windows.h>
#include <string>

using namespace std;

static int LogMe(string logInfo, string fileName)
{
	ofstream logFile("compiler.log");

	logFile << fileName + ": " + logInfo + "\n";
	cout << fileName + ": " + logInfo + "\n";
	logFile.close();
	return 0;
}
