# include <string>
# include <iostream>

#ifndef STRUCT_HPP
#define STRUCT_HPP
using namespace std;

struct CmdLineData {

	CmdLineData(){
	}

	CmdLineData(char * pInFileName, char * pMatchScore, char * pInsDelPenelty, char * pReplacePenelty, char *pOutFileName) {
		uInFileName.assign(pInFileName);
		uOutFileName.assign(pOutFileName);
		uMatchScore = atoi(pMatchScore);
		uInsDelPenelty = atoi(pInsDelPenelty);
		uReplacePenelty = atoi(pReplacePenelty);
	}

	void operator= (const CmdLineData& pOrignalData)
	{
		uInFileName = pOrignalData.uInFileName;
		uOutFileName = pOrignalData.uOutFileName;
		uMatchScore = pOrignalData.uMatchScore;
		uInsDelPenelty = pOrignalData.uInsDelPenelty;
		uReplacePenelty = pOrignalData.uReplacePenelty;
	}

	void PrintInfo()
	{
		std::cout << "The following command line configuration received:" << endl;
		std::cout << "\t Input File Name: " << uInFileName << endl;
		std::cout << "\t Output File Name: " << uOutFileName << endl;
		std::cout << "\t Match Score: " << uMatchScore << endl;
		std::cout << "\t Insert Delete Penelty: " << uInsDelPenelty << endl;
		std::cout << "\t Replace Penelty: " << uReplacePenelty << endl;
	}


	std::string uInFileName;
	std::string uOutFileName;
	int uMatchScore;
	int uInsDelPenelty;
	int uReplacePenelty;
};

struct GeneMergeData {
	
	GeneMergeData(int pScore, string pMergedString) {
		uMergedString = pMergedString;
		uMergeScore = pScore;
	}

	int uMergeScore;
	string uMergedString;
};
#endif