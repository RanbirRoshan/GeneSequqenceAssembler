#pragma once
#include <string>
#include <iostream>
#include <cstdlib>

#ifndef STRUCTURE_HPP

#define STRUCTURE_HPP

struct CmdLineData {

	CmdLineData() {
	}

	CmdLineData(char * pFractionT, char* pMutationProbability, char * pFractionG, char* pSequenceLength, char* pOutputCount, char * pFractionC, char * pFractionA, char *pOutFileName) {
		
		uOutFileName.assign(pOutFileName);
		uSequenceLength = atoi(pSequenceLength);
		uOutputCount = atoi(pOutputCount);
		uFractionA = atoi(pFractionA);
		uFractionC = atoi(pFractionC);
		uFractionG = atoi(pFractionG);
		uFractionT = atoi(pFractionT);
		uMaxLimitForA = uFractionA / (float)(uFractionA + uFractionC + uFractionG + uFractionT);
		uMaxLimitForC = uMaxLimitForA + uFractionC / (float)(uFractionA + uFractionC + uFractionG + uFractionT);
		uMaxLimitForG = uMaxLimitForC + uFractionG / (float)(uFractionA + uFractionC + uFractionG + uFractionT);
		uMaxLimitForT = uMaxLimitForG + uFractionT / (float)(uFractionA + uFractionC + uFractionG + uFractionT);
		uMutationProbability = atof(pMutationProbability);
	}

	void operator= (const CmdLineData& pOrignalData)
	{
		uOutFileName = pOrignalData.uOutFileName;
		uSequenceLength = pOrignalData.uSequenceLength;
		uFractionA = pOrignalData.uFractionA;
		uFractionC = pOrignalData.uFractionC;
		uFractionG = pOrignalData.uFractionG;
		uFractionT = pOrignalData.uFractionT;
		uMaxLimitForA = pOrignalData.uMaxLimitForA;
		uMaxLimitForC = pOrignalData.uMaxLimitForC;
		uMaxLimitForG = pOrignalData.uMaxLimitForG;
		uMaxLimitForT = pOrignalData.uMaxLimitForT;
		uMutationProbability = pOrignalData.uMutationProbability;
		uOutputCount = pOrignalData.uOutputCount;
	}

	void PrintInfo()
	{
		std::cout << "The following command line configuration received:" << std::endl;
		std::cout << "\t Sequence Length: " << uSequenceLength << std::endl;
		std::cout << "\t Fraction of A: " << uFractionA << std::endl;
		std::cout << "\t Fraction of C: " << uFractionC << std::endl;
		std::cout << "\t Fraction of G: " << uFractionG << std::endl;
		std::cout << "\t Fraction of T: " << uFractionT << std::endl;
		std::cout << "\t Mutation Probability: " << uMutationProbability << std::endl;
		std::cout << "\t Output File Name: " << uOutFileName << std::endl;
	}


	std::string uOutFileName;
	int uSequenceLength;
	int uOutputCount;
	int uFractionA;
	int uFractionC;
	int uFractionG;
	int uFractionT;
	float uMaxLimitForA;
	float uMaxLimitForC;
	float uMaxLimitForG;
	float uMaxLimitForT;
	float uMutationProbability;
};

#endif
