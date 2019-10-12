#include "pch.h"
#include <iostream>
#include "SequenceGenerator.hpp"
using namespace std;

int main(int argc, char * argv[])
{
	if (argc != 9) {
		std::cout << "Need 8 arguments <sequence length> <fraction of \'A\'> <fraction of \'C\'> <fraction of \'G\'> "
              "<fraction of \'T\'> <no. of sequence> <mutation probability> <output file name>" << std::endl;
		
		return 0;
	}

	CmdLineData data(argv[5], argv[7], argv[4], argv[1], argv[6], argv[3], argv[2], argv[8]);

	SequenceGenerator app(data);

	data.PrintInfo();

	app.Execute();
}