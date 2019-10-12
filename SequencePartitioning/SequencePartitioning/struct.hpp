#pragma once
#include <string>
#include <iostream>
#include "pch.h"
#include <cstdlib>

#ifndef STRUCTURE_HPP

#define STRUCTURE_HPP

struct CmdLineData {

	CmdLineData() {
	}

	CmdLineData(char * pInFileName, char* pMinLen, char* pMaxLen, char *pOutFileName) {

		uOutFileName.assign(pOutFileName);
		uMinLen = atoi(pMinLen);
		uMaxLen = atoi(pMaxLen);
		uInFileName.assign(pInFileName);
	}

	void operator= (const CmdLineData& pOrignalData)
	{
		uOutFileName = pOrignalData.uOutFileName;
		uInFileName = pOrignalData.uInFileName;
		uMinLen = pOrignalData.uMinLen;
		uMaxLen = pOrignalData.uMaxLen;
	}

	void PrintInfo()
	{
		std::cout << "The following command line configuration received:" << std::endl;
		std::cout << "\t Input File Name: " << uInFileName << std::endl;
		std::cout << "\t Min Len: " << uMinLen << std::endl;
		std::cout << "\t Max Len: " << uMaxLen << std::endl;
		std::cout << "\t Output File Name: " << uOutFileName << std::endl;
	}


	std::string uInFileName;
	std::string uOutFileName;
	int uMinLen;
	int uMaxLen;
};

#endif
