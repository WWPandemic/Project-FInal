#pragma once
#include <string>
#include <fstream>
#include "Bundle.h"

class BookReader
{
private:
	std::ifstream inFile;
	std::ofstream outFile;

	std::string* splitInfo(std::string*, std::string, int);		// Splits bookInfo into an array of strings
	std::string stringISBN(int);			// Convert isbn back to string and conserve 0's
	std::string stringDate(Date);			// Convert date object back to string

public:
	// Constructor/Destructor
	BookReader();
	~BookReader();

	// Functions
	void setInFile();					// Get input file from user and open
	void openInputFile(std::string);	// Open file with exception handling
	void createBundle(Bundle &b);		// Creates bundle from input file
	void exportBundle(Bundle);			// Sends bundle to output file

};
