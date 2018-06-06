#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <fstream>
#include "BookReader.h"

//*************************************
//* Constructor/Destructor definition *
//*************************************

BookReader::BookReader()
{
	// User enters input file location
	do {
		std::string userInFile;
		std::cout << "Input File: ";
		getline(std::cin, userInFile);
		inFile.open(userInFile);
				
		if (!inFile) {
			std::cout << "Could not find the specified file, please try again.\n\n";
		}
		else {
			std::cout << "File successfully opened!\n\n";
		}
	} while (!inFile);
}

BookReader::~BookReader()
{
	inFile.close();
}

//************************
//* Function definitions *
//************************

Book* BookReader::createBundle()				// Creates bundle from input file
{
	std::string bookInfo;					// All book info in a single string
	int bundleSize = 30;					// **** PLACEHOLDER: replace with bundle ****
	Book *bundle = new Book[bundleSize];	// **** PLACEHOLDER: replace with bundle ****
	int count = 0;							// Count number of books

	// Read each line, separate into variables and create a new book
	while (inFile >> bookInfo)
	{
		//Split bookInfo into an array of strings
		const int params = 8;			// Number of book parameters
		std::string info[params];		// Array to store book info in
		splitInfo(info, bookInfo, params);		// Call function to split bookInfo into array

		// Add book to array		**** PLACEHOLDER: bundle function ****
		Date date;			// ***** need way to create date from string ******
		bundle[count] = Book(info[0], info[1], info[2], stoi(info[3]), date, stoi(info[5]), stod(info[6]), stod(info[7]));

		count++;

		//// Adjust array size if limit reached		**** PLACEHOLDER: bundle function ****
		//if (count >= bundleSize) {
		//	bundleSize += 10;		// Add 10 to array size
		//	Book* temp = new Book[bundleSize];	// Create temp pointer to new memory
		//	for (int i = 0; i < count; i++) {	// Copy old array to new array
		//		temp[i] = bookarray[i];
		//	}
		//	delete[] bookarray;		// Free old array memory
		//	bookarray = temp;		// Redirect pointer to new array memory
		//}

	}

	return bundle;			// ****PLACEHOLDER: replace with bundle ****
}

std::string* BookReader::splitInfo(std::string* splitInfo, std::string bookInfo, int size)		// Split bookInfo into an array of strings
{
	int start = 0;
	int end = 0;
	int chars = 0;

	for (int i = 0; i < size; i++)
	{
		end = bookInfo.find(';', start);		// Determine next delimiter
		chars = bookInfo.find(';', start) - start;			// Determine number of chars to copy
		splitInfo[i] = bookInfo.substr(start, chars);		// Copy string up to delimiter
		start = end + 1;		// Move start to position after delimiter
	}

	return splitInfo;
}

void BookReader::exportBundle(Bundle bundle)			// Sends bundle to output file
{
	// open output file
	// loop for each bundle item
		// write to output file
	// close output file
}



/*
To do:
- create operator for << and >>
- exportBundle function
- date workaround for createBundle
*/