#pragma once
#include <string>
#include <fstream>
#include "Bundle.h"

class BookReader
{
private:
	std::ifstream inFile;
	std::ofstream outFile;

public:
	// Constructor/Destructor
	BookReader();
	~BookReader();

	// Accessor/Mutator
	//std::ifstream getInFile();
	//std::ofstream getOutFile();
	//void setInFile(std::string);
	//void setOutFile(std::string);

	// Functions
	Book* createBundle();			// Creates bundle from input file	**** (replace Book* with Bundle) ****
	void exportBundle(Bundle);				// Sends bundle to output file
	std::string* splitInfo(std::string*, std::string, int);		// Split bookInfo into an array of strings
};

/*
Main functions of BookReader:
1. Create Bundle from input file
2. Create output file from Bundle
*/