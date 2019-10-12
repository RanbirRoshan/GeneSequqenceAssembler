
#include "pch.h"
#include "utility.hpp"
#include <cstdlib>

int ** Utility::Get2dMergeArray(int pVerticalSize, int pHorizontalSize)
{
	int ** retArr;

	retArr = (int**)calloc(pVerticalSize, sizeof(int*));

	for (int i = 0; i < pVerticalSize; i++)
	{
		retArr[i] = (int*)calloc(pHorizontalSize, sizeof(int));
	}

	return retArr;
}

void Utility::Free2dMeregeArray(int ** pArray, int pVerticalSize) {
	
	for (int i = 0; i < pVerticalSize; i++) {
		free (pArray[i]);
	}

	free(pArray);
}