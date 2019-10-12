#include "pch.h"
#include "Util.hpp"

char Utility::GetACGT(const CmdLineData & pCmdLineData)
{
	float chance = (rand()%100)/(float)100;

	if (chance <= pCmdLineData.uMaxLimitForA)
		return 'A';

	if (chance <= pCmdLineData.uMaxLimitForC)
		return 'C';

	if (chance <= pCmdLineData.uMaxLimitForG)
		return 'G';
		
	return 'T';
}