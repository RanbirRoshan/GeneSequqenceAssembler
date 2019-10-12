#pragma once


#ifndef UTILITY_HPP

#define UTILITY_HPP

class Utility {

public:
	static int** Get2dMergeArray(int pVerticalSize, int pHorizontalSize);
	static void Free2dMeregeArray(int ** pArray, int pVerticalSize);
};


#endif