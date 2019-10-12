
#include "pch.h"
#include "SequenceAssembler.hpp"
#include "utility.hpp"
#include <fstream>
#include <algorithm>
#include <assert.h>
#include <iomanip>


SequenceAssembler::SequenceAssembler(CmdLineData &pCmdLineData)
{
	vCmdLineData = pCmdLineData;
}

void SequenceAssembler::PrintInfo(bool pPrintAllDetails)
{
	vCmdLineData.PrintInfo();
	std::cout << "\n\n\nInternal Data:" << endl;
	std::cout << "\tNumber of gene sequence:" << vGeneSequences.size() << endl;
	for (int i = 0; i < vGeneSequences.size(); i++) {
		std::cout << "\t" << vGeneSequences[i] << endl;

		// just print first 5 values in case print all details in not asked
		if (!pPrintAllDetails && i > 2) {

			std::cout << "\t..." << endl;
			cout << "\n\n\n";
			return;
		}
	}
	cout << "\n\n\n";
}

void SequenceAssembler::WriteOutputGeneSeq(string pOutStr) {

	// open file for readings
	fstream output(vCmdLineData.uOutFileName, fstream::in | fstream::out | fstream::trunc);

	output << pOutStr << "\n";

	// close the stream as we have read all we wanted
	output.close();
}

/**
 * @brief The function would read the genesequence from input file and populate the gene sequence vector
 */
void SequenceAssembler::ReadInputGeneSeq() {
	
	// open file for readings
	ifstream input(vCmdLineData.uInFileName, ifstream::in);
	
	// read all lines and add them to the  gene sequence vector
	for (std::string line; getline(input, line); ) {
		vGeneSequences.push_back(line);
	}
	
	// close the stream as we have read all we wanted
	input.close();
}

bool SequenceAssembler::Initialize()
{
	ReadInputGeneSeq();

	return true;
}

GeneMergeData* SequenceAssembler::MergeGeneStrings(string pGeneV, string pGeneH, const CmdLineData pCmdData)
{
	int lenGeneV = pGeneV.length();
	int lenGeneH = pGeneH.length();
	
	int ** mergeScoreArr = Utility::Get2dMergeArray(lenGeneV+1, lenGeneH+1);

	int bestMergeScore;

	string retVal;

	PopulateMergeArray(mergeScoreArr, pGeneV, pGeneH, lenGeneV, lenGeneH, pCmdData);

	retVal = GetBestMergeSequence(pGeneV, pGeneH, mergeScoreArr, lenGeneV, lenGeneH, pCmdData, bestMergeScore);
	
	Utility::Free2dMeregeArray(mergeScoreArr, lenGeneV);

	return new GeneMergeData(bestMergeScore, retVal);
}

string SequenceAssembler::GetBestMergeSequence(string pGeneV, string pGeneH, int** pScoreArr, int pLenGeneV, int pLenGeneH, CmdLineData pCmdData, int& pBestMergeScore)
{
	string retVal;

	int endX=pLenGeneV, endY=pLenGeneH;
	int startX = 0, startY = 0;

	for (int iter = 1; iter <= pLenGeneV; iter++) {
		if (pScoreArr[iter][pLenGeneH] > pScoreArr[endX][endY]) {
			endX = iter;
		}
	}

	for (int iter = 1; iter <= pLenGeneH; iter++) {
		if (pScoreArr[pLenGeneV][iter] > pScoreArr[endX][endY]) {
			endY = iter;
			endX = pLenGeneV;
		}
	}

	TrackSequenceStartPoint(pScoreArr, endX, endY, startX, startY, pCmdData);

	if (endX == pLenGeneV) {
		//take pre
		retVal = pGeneV.substr(0, startX);

		//take mege
		retVal += pGeneH.substr(0,endY);

		//take end
		retVal += pGeneH.substr(endY);

	}
	else {
		//take pre
		retVal = pGeneH.substr(0, startY);

		//take mege
		retVal += pGeneV.substr(0, endX);

		//take end
		retVal += pGeneV.substr(endX);
	}

	pBestMergeScore = pScoreArr[endX][endY];

	return retVal;
}

void SequenceAssembler::TrackSequenceStartPoint(int ** pScoreArr, int pEndX, int pEndY, int& pOutStartX, int& pOutStartY, CmdLineData pCmdData)
{
	pOutStartX = pEndX;
	pOutStartY = pEndY;

	while (pOutStartX != 1 && pOutStartY != 1) {
		if (pScoreArr[pOutStartX][pOutStartY - 1] - pCmdData.uInsDelPenelty == pScoreArr[pOutStartX][pOutStartY])
			pOutStartY--;
		else if (pScoreArr[pOutStartX - 1][pOutStartY] - pCmdData.uInsDelPenelty == pScoreArr[pOutStartX][pOutStartY])
			pOutStartX--;
		else {
#ifdef _DEBUG || NDEBUG
			if (pScoreArr[pOutStartX - 1][pOutStartY - 1] - pCmdData.uReplacePenelty != pScoreArr[pOutStartX][pOutStartY] &&
				pScoreArr[pOutStartX - 1][pOutStartY - 1] + pCmdData.uMatchScore != pScoreArr[pOutStartX][pOutStartY]) {
				std::cout << "Error in code logic SequenceAssembler::TrackSequenceStartPoint" << endl;
			}
#endif

			pOutStartX--;
			pOutStartY--;

		}
	}
}

void SequenceAssembler::PopulateMergeArray(int ** pMergeScoreArr, string pGeneV, string pGeneH, int pLenGeneV, int pLenGeneH, const CmdLineData pCmdData)
{
	for (int ver = 1; ver <= pLenGeneV; ver++) {
		for (int hor = 1; hor <= pLenGeneH; hor++) {
			int ver_score = pMergeScoreArr[ver - 1][hor] - pCmdData.uInsDelPenelty;
			int hor_score = pMergeScoreArr[ver][hor - 1] - pCmdData.uInsDelPenelty;
			int dia_score = pMergeScoreArr[ver-1][hor - 1];

			if (pGeneV[ver-1] != pGeneH[hor-1])
				dia_score -= pCmdData.uReplacePenelty;
			else
				dia_score += pCmdData.uMatchScore;

			pMergeScoreArr[ver][hor] = max({ ver_score, hor_score, dia_score });
		}
	}

	/*for (int ver = 0; ver <= pLenGeneV; ver++) {
		for (int hor = 0; hor <= pLenGeneH; hor++) {
			std::cout << pMergeScoreArr[ver][hor] << "\t";
		}
		std::cout << endl;
	}*/
}

void GetBestMergeStringPosition(vector < vector<GeneMergeData*>*>& pData, int& pOutFirstMergePos, int& pOutSecondMergePos)
{
	pOutFirstMergePos = 0;
	pOutSecondMergePos = 0;

	for (int iter = 0; iter < pData.size(); iter++) {
		for (int pos = 0; pos < pData[iter]->size(); pos++) {
			if (pData[pOutFirstMergePos]->at(pOutSecondMergePos)->uMergeScore < pData[iter]->at(pos)->uMergeScore) {
				pOutFirstMergePos = iter;
				pOutSecondMergePos = pos;
			}
		}
	}

	pOutSecondMergePos += pOutFirstMergePos+1;
}

void RemoveSingleEntryByPos(vector < vector<GeneMergeData*>*>& pData, int pRemovePos)
{
	for (int i = 0; i < pRemovePos; i++){
		delete pData[i]->at(pRemovePos - i - 1);
		pData[i]->erase(pData[i]->begin() + (pRemovePos - i - 1));
	}
	if (pRemovePos < pData.size()) {
		delete pData.at(pRemovePos);
		pData.erase(pData.begin() + pRemovePos);
	}
}

void RemoveEntryByPos(vector < vector<GeneMergeData*>*>& pData, int pOutFirstMergePos, int pOutSecondMergePos)
{
	assert(pOutSecondMergePos>pOutFirstMergePos);
	RemoveSingleEntryByPos(pData, pOutSecondMergePos);
	RemoveSingleEntryByPos(pData, pOutFirstMergePos);
}

void IncrementTaskDone(int & pTaskDone, const int pTotal) {
	pTaskDone++;
	static float prev = 0;
	float percent = ((pTaskDone * 100) / (float)pTotal);
	//if (percent > 99.8) {
		prev = percent;
		std::cout << "Progress: [";
		for (int i = 0; i < 50; i++) {
			if ((float)i<(percent/2))
				std::cout << "*";
			else
				std::cout << "-";
		}
		
		std::cout << std::fixed << std::setprecision(5) << "] " << percent << "%" << '\r';
	//}
}

void SequenceAssembler::Execute() {

	if (vGeneSequences.size() < 2) {
		if (vGeneSequences.size() == 1) {
			WriteOutputGeneSeq(vGeneSequences[0]);
			std::cout << "Only one gene sequence defined." << vGeneSequences[0] << endl;
		} else
			std::cout << "No data in gene sequence" << endl;
		return;
	}

	int total_task, task_done=0;

	total_task = (((vGeneSequences.size()-1)*(vGeneSequences.size() - 2)) >> 1) + 
				 ((vGeneSequences.size()*(vGeneSequences.size() - 1)) >> 1);

	int firstMergePos = 0, secondMergePos = 0;
	vector < vector<GeneMergeData*>*> mergeInfo;

	for (int iter = 0; iter < vGeneSequences.size() - 1; iter++) {
		vector<GeneMergeData*> *data = new vector<GeneMergeData*>();
		
		for (int pos = iter+1; pos < vGeneSequences.size(); pos++) {
			data->push_back(MergeGeneStrings(vGeneSequences[iter], vGeneSequences[pos], vCmdLineData));
			IncrementTaskDone(task_done, total_task);
		}
		
		mergeInfo.push_back(data); 
	}

	GetBestMergeStringPosition(mergeInfo, firstMergePos, secondMergePos);
	do {
		//std::cout << "Merge Data: " << firstMergePos << "\t2nd Pos: " << secondMergePos << "\tgene count: " << vGeneSequences.size() << "\t Merge Size" << mergeInfo.size() << endl;
		GeneMergeData *mergeData = mergeInfo[firstMergePos]->at(secondMergePos- firstMergePos - 1);
		vGeneSequences.push_back(mergeData->uMergedString);
		RemoveEntryByPos(mergeInfo, firstMergePos, secondMergePos);
		vGeneSequences.erase(vGeneSequences.begin() + (secondMergePos));
		vGeneSequences.erase(vGeneSequences.begin() + (firstMergePos));
		mergeInfo.push_back(new vector<GeneMergeData*>());
		for (int iter = 1; iter < vGeneSequences.size(); iter++) {
			mergeInfo[iter - 1]->push_back(MergeGeneStrings(vGeneSequences[iter - 1], vGeneSequences.back(), vCmdLineData));
			IncrementTaskDone(task_done, total_task);
		}

		GetBestMergeStringPosition(mergeInfo, firstMergePos, secondMergePos);
	} while (vGeneSequences.size() > 1);

	WriteOutputGeneSeq(vGeneSequences[0]);
	//std::cout << "\n"<<"\n\nAns:\n" << vGeneSequences[0] << endl;
}