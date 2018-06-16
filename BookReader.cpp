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
	setInFile();
}

BookReader::~BookReader()
{
	inFile.close();
}

//************************
//* Function definitions *
//************************

// Get input file from user and open
void BookReader::setInFile()
{
	std::cout << "Creating book inventory data, please enter the file path location ...\n";
	do {
		std::string userInFile;
		std::cout << "Input File: ";
		getline(std::cin, userInFile);

		try
		{
			openInputFile(userInFile);
			std::cout << "File successfully opened!\n\n";
		}
		catch (std::string fileException)
		{
			std::cout << fileException << std::endl << std::endl;
		}
	} while (!inFile);
}

// Open file with exception handling
void BookReader::openInputFile(std::string file)
{
	inFile.open(file);

	if (!inFile) {
		std::string fileException = "Could not find the specified file, please try again.";
		throw fileException;
	}
}

// Splits bookInfo into an array of strings
std::string* BookReader::splitInfo(std::string* splitInfo, std::string bookInfo, int size)
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

// Convert isbn back to string and conserve 0's
std::string BookReader::stringISBN(int isbn)
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

// Convert date object back to string
std::string BookReader::stringDate(Date date)
{
	std::string str = "";
	if (date[0] < 10)
		str.append("0");
	str.append(std::to_string(date[0]));
	if (date[1] < 10)
		str.append("0");
	str.append(std::to_string(date[1]));
	str.append(std::to_string(date[2]));
	return str;
}

// Creates bundle from input file
Bundle BookReader::createBundle()
{
	std::string bookInfo;			// All book info in a single string
	Bundle bundle(25);				// Create bundle

	// Read each line, separate into variables and create a new book
	while (getline(inFile, bookInfo))
	{
		//Split bookInfo into an array of strings
		const int PARAM = 8;					// Number of book parameters
		std::string info[PARAM];				// Array to store book info in
		splitInfo(info, bookInfo, PARAM);		// Call function to split bookInfo into array
		int count = 0;							// Number of books

		// Convert date info into Date object
		Date date(stoi(info[4].substr(0, 2)), stoi(info[4].substr(2, 2)), stoi(info[4].substr(4, 4)));

		// Add book to bundle, add one to count
		bundle[count++] = Book(info[0], info[1], info[2], stoi(info[3]), date, stoi(info[5]), stod(info[6]), stod(info[7]));

		// Check bundle size
		if (count >= bundle.getLength()) {
			//bundle.getArray().reSize(count + 1);
		}
	}

	return bundle;
}

//// **temp**
//void BookReader::exportBundle(Bundle bundle)			// Sends bundle to output file
//{
//	// Open output file
//	std::cout << "Exporting book inventory data, please enter the file path location ...\n";
//	do {
//		std::string userOutFile;
//		std::cout << "Output File: ";
//		getline(std::cin, userOutFile);			// User enters output file location
//		outFile.open(userOutFile);
//
//		if (!outFile) {			// Validate output file
//			std::cout << "Could not find the specified file, please try again.\n\n";
//		}
//		else {
//			std::cout << "File successfully opened!\n\n";
//		}
//	} while (!outFile);
//	
//	// Write to output file
//	Book *write = bundle.getBundle();
//	for (int i = 0; i < bundle.getSize(); i++) {
//		outFile << (write + i)->getTitle() << ";" <<
//			(write + i)->getAuthor() << ";" <<
//			(write + i)->getPublisher() << ";" <<
//			stringISBN((write + i)->getISBN()) << ";" <<
//			stringDate((write + i)->getDateAdded()) << ";" <<
//			(write + i)->getQuantityOnHand() << ";" <<
//			(write + i)->getWholesaleCost() << ";" <<
//			(write + i)->getRetailPrice() << "\n";
//	}
//
//	outFile.close();
//}