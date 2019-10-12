
#include "pch.h"
#include "SequencePartitioner.hpp"

using namespace std;

SequencePartitioner::SequencePartitioner(CmdLineData pData) {
	vCmdData = pData;
	remove(pData.uOutFileName.c_str());
	vOutFile.open(vCmdData.uOutFileName, fstream::in | fstream::out | fstream::trunc);
	vInFile.open(vCmdData.uInFileName, fstream::in);
}

SequencePartitioner::~SequencePartitioner()
{
	vInFile.close();
	vOutFile.close();
}

void SequencePartitioner::Execute(){
	
	int gapSize = vCmdData.uMaxLen - vCmdData.uMinLen + 1;

	for (std::string line; getline(vInFile, line); )
	{
		int pos = 0;
		int chance = rand();
		int subLen = vCmdData.uMinLen + (chance % gapSize);

		while (pos + subLen < line.length()) {
			vOutFile << line.substr(pos, subLen) << "\n";
			pos += subLen;

			chance = rand();
			subLen = vCmdData.uMinLen + (chance % gapSize);
		}

		if (line.length() - pos >= vCmdData.uMinLen && line.length() - pos <= vCmdData.uMaxLen)
			vOutFile << line.substr(pos) << "\n";
	}


}