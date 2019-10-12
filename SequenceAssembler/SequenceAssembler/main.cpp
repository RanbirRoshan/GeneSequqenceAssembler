// SequenceAssembler.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include "struct.hpp"
#include "SequenceAssembler.hpp"
using namespace std;

int main(int argc, char * argv[])
{
	
	if (argc != 6) {
		std::cout << "5 command line argument required in form of <input file name> <score for match> <penalty for replace>\
			<penalty for delete/insert> <outfile name>" << endl;
		return 0;
	}

	CmdLineData data(argv[1], argv[2], argv[3], argv[4], argv[5]);
	SequenceAssembler app(data);

	if (!app.Initialize()) {
		std::cout << "App initialization failed.";
		return 0;
	}

	app.PrintInfo(false);

	app.Execute();

	return 0;
}