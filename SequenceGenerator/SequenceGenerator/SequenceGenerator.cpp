#include "pch.h"
#include "SequenceGenerator.hpp"
#include "Util.hpp"
#include <cstdio>
#include <iostream>
#include <iomanip>
using namespace std;

SequenceGenerator::SequenceGenerator(CmdLineData pData) {
	vCmdData = pData;
	remove(pData.uOutFileName.c_str());
	vFile.open(vCmdData.uOutFileName, fstream::in | fstream::out | fstream::trunc);
}

SequenceGenerator::~SequenceGenerator() {
	vFile.close();
}

string SequenceGenerator::GetBaseString()
{
	string retVal = "";

	for (int i = 0; i < vCmdData.uSequenceLength; i++) {
		retVal += Utility::GetACGT(vCmdData);
	}

	return retVal;
}

void SequenceGenerator::WriteToFile(string pOutData) {
	vFile << pOutData.c_str() << "\n";
}

char SequenceGenerator::GetReplaceCharacter(char pOrigChar) {
	char replaceChar;
	do {
		replaceChar = Utility::GetACGT(vCmdData);
	} while (replaceChar == pOrigChar);

	return replaceChar;
}

string SequenceGenerator::GetMutatedString()
{
	string mutatedString = "";
	float chance;

	for (int i = 0; i < vCmdData.uSequenceLength; i++) {
		chance = (rand()%101)/100;

		if (chance <= vCmdData.uMutationProbability) {
			int mutation = rand() % 3;
			switch (mutation) {
			case 0: //replace
				mutatedString += GetReplaceCharacter(vBaseString[i]);
				break;
			case 1: //delete
				break;
			case 2: //insert
				mutatedString += Utility::GetACGT(vCmdData);
				i--;
			}
		}
	}
	return mutatedString;
}

void IncrementTaskDone(int & pTaskDone, const int pTotal) {
	pTaskDone++;
	static float prev = 0;
	float percent = ((pTaskDone * 100) / (float)pTotal);
	if (prev < percent - 0.1 || percent > 99.8) {
		prev = percent;
		std::cout << "Progress: [";
		for (int i = 0; i < 50; i++) {
			if ((float)i < (percent / 2))
				std::cout << "*";
			else
				std::cout << "-";
		}

		std::cout << std::fixed << std::setprecision(3) << "] " << percent << "%" << '\r';
	}
}


void SequenceGenerator::Execute() {
	int taskDone = 0;
	vBaseString = GetBaseString();
	WriteToFile(vBaseString);
	IncrementTaskDone(taskDone, vCmdData.uOutputCount);

	for (int iter = 1; iter < vCmdData.uOutputCount; iter++)
	{
		WriteToFile(GetMutatedString());
		IncrementTaskDone(taskDone, vCmdData.uOutputCount);
	}
}