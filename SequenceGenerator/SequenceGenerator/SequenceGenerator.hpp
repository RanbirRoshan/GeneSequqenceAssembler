#pragma once

#ifndef SEQUENCE_GENERATOR_HPP

#define SEQUENCE_GENERATOR_HPP

#include "structure.hpp"
#include <fstream>

class SequenceGenerator {
public:
	SequenceGenerator(CmdLineData pData);
	~SequenceGenerator();

	void Execute();

private:

	std::string GetBaseString();
	void WriteToFile(std::string pOutputData);
	std::string GetMutatedString();
	char GetReplaceCharacter(char pOrigChar);

	CmdLineData vCmdData;
	std::fstream vFile;
	std::string vBaseString;
};

#endif