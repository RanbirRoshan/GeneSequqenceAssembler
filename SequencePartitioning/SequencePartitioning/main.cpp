#include "pch.h"
#include <iostream>
#include "SequencePartitioner.hpp"
using namespace std;

int main(int argc, char * argv[])
{
	if (argc != 5) {
		std::cout << "Need 4 arguments <input file name> <minimum fragment length> <maximum fragment length> "
              "<output file name>" << std::endl;

		return 0;
	}

	CmdLineData data(argv[1], argv[2], argv[3], argv[4]);

	SequencePartitioner app(data);

	data.PrintInfo();

	app.Execute();
}