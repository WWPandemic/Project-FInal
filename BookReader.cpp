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
	std::cout << "Creating book inventory data, please enter the file path location ...\n";
	do {
		std::string userInFile;
		std::cout << "Input File: ";
		getline(std::cin, userInFile);			// User enters input file location
		inFile.open(userInFile);
		
		if (!inFile) {			// Validate input file
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

std::string* BookReader::splitInfo(std::string* splitInfo, std::string bookInfo, int size)		// Splits bookInfo into an array of strings
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

std::string BookReader::stringISBN(int isbn)		// Convert isbn back to string and conserve 0's
{
	std::string newisbn = "";
	if (isbn < 100000000) {	
		newisbn = "00" + std::to_string(isbn);
	}
	else if (isbn < 1000000000) {
		newisbn = "0" + std::to_string(isbn);
	}
	else {
		newisbn = std::to_string(isbn);
	}
	return newisbn;
}

std::string BookReader::stringDate(Date date)		// Convert date object back to string
{
	std::string str = "";
	if (*(date.getDate() + 0) < 10)
		str.append("0");
	str.append(std::to_string(*(date.getDate() + 0)));
	if (*(date.getDate() + 1) < 10)
		str.append("0");
	str.append(std::to_string(*(date.getDate() + 1)));
	str.append(std::to_string(*(date.getDate() + 2)));
	return str;
}

Bundle BookReader::createBundle()				// Creates bundle from input file
{
	std::string bookInfo;			// All book info in a single string
	Bundle bundle(30);				// Created bundle with expected max of 30

	// Read each line, separate into variables and create a new book
	while (std::getline(inFile, bookInfo))
	{
		//Split bookInfo into an array of strings
		const int PARAM = 8;					// Number of book parameters
		std::string info[PARAM];				// Array to store book info in
		splitInfo(info, bookInfo, PARAM);		// Call function to split bookInfo into array

		// Convert date info into Date object
		Date date(stoi(info[4].substr(0, 2)), stoi(info[4].substr(2, 2)), stoi(info[4].substr(4, 4)));

		// Add book to bundle
		bundle.addBook(info[0], info[1], info[2], stoi(info[3]), date, stoi(info[5]), stod(info[6]), stod(info[7]));

		// Check bundle size
		bundle.ensureSize(bundle.getSize());
	}

	return Bundle(bundle);
}

// **temp**
void BookReader::exportBundle(Bundle bundle)			// Sends bundle to output file
{
	// Open output file
	std::cout << "Exporting book inventory data, please enter the file path location ...\n";
	do {
		std::string userOutFile;
		std::cout << "Output File: ";
		getline(std::cin, userOutFile);			// User enters output file location
		outFile.open(userOutFile);

		if (!outFile) {			// Validate output file
			std::cout << "Could not find the specified file, please try again.\n\n";
		}
		else {
			std::cout << "File successfully opened!\n\n";
		}
	} while (!outFile);
	
	// Write to output file
	Book *write = bundle.getBundle();
	for (int i = 0; i < bundle.getSize(); i++) {
		outFile << (write + i)->getTitle() << ";" <<
			(write + i)->getAuthor() << ";" <<
			(write + i)->getPublisher() << ";" <<
			stringISBN((write + i)->getISBN()) << ";" <<
			stringDate((write + i)->getDateAdded()) << ";" <<
			(write + i)->getQuantityOnHand() << ";" <<
			(write + i)->getWholesaleCost() << ";" <<
			(write + i)->getRetailPrice() << "\n";
	}

	outFile.close();
}