#pragma once

#ifndef SEQUENCE_PARTITIONER_HPP

#define SEQUENCE_PARTITIONER_HPP

#include"struct.hpp"
#include <fstream>

class SequencePartitioner {

public:
	SequencePartitioner(CmdLineData pData);
	~SequencePartitioner();
	void Execute();

private:

	CmdLineData vCmdData;

	std::fstream vInFile;
	std::fstream vOutFile;
};

#endif