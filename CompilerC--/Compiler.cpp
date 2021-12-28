#include <iostream>
#include <fstream>
#include <windows.h>
#include <sstream>
#include <string>
#include "Logger.cpp"
#include <vector>

using namespace std;

static int Compile(string InputName, string outputName)
{
    string extension = ".cmm";
    string FileName;

    // Check if filename correct
    if (InputName.substr(InputName.length() - extension.length()) != extension) {
        FileName = InputName + extension;
    }
    else {
        FileName = InputName;
    }

    // Get Code File
    ifstream codeFile;
    codeFile.open(FileName);
    LogMe("Got file", FileName);

    // Get file contents
    string codeFileContents;
    ostringstream ss;
    ss << codeFile.rdbuf();
    codeFileContents = ss.str();

    if (codeFileContents != "") {
        LogMe("Loaded Code file, contents are " + codeFileContents, "Compiler");
    }
    else {
        LogMe("Code file failed to load.", "Compiler");
    }

    // Compile File
    LogMe("Compiling", FileName);
    string compileFileContents;

    istringstream inputString(codeFileContents);

    if (codeFileContents.find("\n") != string::npos || codeFileContents.find(";") != string::npos) {
        LogMe("Found Entry", FileName);

        if (!codeFile.is_open()) { LogMe("Failed to open file", "Compiler"); return EXIT_FAILURE; }

        string line;

        LogMe("Found thingy", FileName);

        while (std::getline(inputString, line)) {

            LogMe("Line: " + line, FileName);

            // Remove useless symbols
            if (line.find(";") != string::npos) {
                line.replace(line.find(";"), line.length(), "");
            }
            if (line.find(" ") != string::npos) {
            line.replace(line.find(" "), line.length(), "");
            }

            // CHECK FOR MATH STUFF

            // ADDITION
            if (line.find("+") != string::npos) {
                size_t pos = line.find("+");
                string beforeSymbol = line.substr(0, pos);
                string afterSymbol = line.substr(pos, line.length());

                float beforeValue = stof(beforeSymbol);
                float afterValue = stof(afterSymbol);
               
                compileFileContents = compileFileContents + to_string(beforeValue + afterValue) + "\n";
            }
            // SUBTRACT
            if (line.find("-") != string::npos) {
                size_t pos = line.find("-");
                string beforeSymbol = line.substr(0, pos);
                string afterSymbol = line.substr(pos, line.length());

                float beforeValue = stof(beforeSymbol);
                float afterValue = stof(afterSymbol);

                compileFileContents = compileFileContents + to_string(beforeValue - afterValue) + "\n";
            }
            // DIVIDE
            if (line.find("/") != string::npos) {
                size_t pos = line.find("/");
                string beforeSymbol = line.substr(0, pos);
                string afterSymbol = line.substr(pos, line.length());

                float beforeValue = stof(beforeSymbol);
                float afterValue = stof(afterSymbol);

                compileFileContents = compileFileContents + to_string(beforeValue / afterValue) + "\n";
            }
            // MULTIPLY
            if (line.find("*") != string::npos) {
                size_t pos = line.find("*");
                string beforeSymbol = line.substr(0, pos);
                string afterSymbol = line.substr(pos, line.length());

                float beforeValue = stof(beforeSymbol);
                float afterValue = stof(afterSymbol);

                compileFileContents = compileFileContents + to_string(beforeValue * afterValue) + "\n";
            }
        }
    }

    // Set Output File Name
    string outputFileName = outputName + ".compiled";

    // Send Output File
    ofstream outputFile(outputFileName);

    LogMe("Created output file, contents to be added: " + compileFileContents, "Compiler");
    outputFile << compileFileContents;

    LogMe("Compiled File", FileName);
    outputFile.close();

    return 0;
}
