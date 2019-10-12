#pragma once

#include "struct.hpp"
#include <vector>

#ifndef SEQUENCE_ASSEMBLER_HPP

#define SEQUENCE_ASSEMBLER_HPP

class SequenceAssembler {
	   
public:
	SequenceAssembler(CmdLineData &pCmdLineData);
	
	// helper function to peek into data and state
	void PrintInfo (bool pPrintAllDetails);

	bool Initialize ();

	void Execute ();

	static GeneMergeData* MergeGeneStrings (string pString1, string pString2, const CmdLineData pCmdData);

private:

	void WriteOutputGeneSeq(string pOutStr);

	static string GetBestMergeSequence (string pGeneV, string pGeneH, int** pScoreArr, int pLenGeneV, int pLenGeneH, CmdLineData pCmdData, int& pBestMergeScore);
	static void TrackSequenceStartPoint (int ** pScoreArr, int pEndX, int pEndY, int& pOutStartX, int& pOutStartY, CmdLineData pCmdData);
	static void PopulateMergeArray (int ** pMergeScoreArr, string pGeneV, string pGeneH, int pLenGeneV, int pLenGeneH, const CmdLineData pCmdData);

	void ReadInputGeneSeq ();

	CmdLineData		vCmdLineData;
	vector<string>	vGeneSequences;
};

#endif