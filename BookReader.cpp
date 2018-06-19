#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <fstream>
#include "BookReader.h"

/*
Constructor:	BookReader
Author:			Terry Chiem
Parameters:		none
Returns:		BookReader object
Description:	This constructor creates a BookReader and prompts the user
				for an input file location.
*/
BookReader::BookReader()
{
	setInFile();
}
/*
Function:		setInFile
Author :		Terry Chiem
Parameters :	none
Returns :		none
Description :	Prompts user for input file location and validates it.
*/
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
/*
Function:		openInputFile
Author :		Terry Chiem
Parameters :	string file - File location
Returns :		none
Description :	Opens the file and throws an exception if invalid.
*/
void BookReader::openInputFile(std::string file)
{
	inFile.open(file);

	if (!inFile) {
		std::string fileException = "Could not find the specified file, please try again.";
		throw fileException;
	}
}
/*
Function:		splitInfo
Author :		Terry Chiem
Parameters :	string* splitInfo - The array to hold information in
				string bookInfo - Book information from file in a single line
				int size - Size of the splitInfo array
Returns :		string*
Description :	Splits book information from file into a string array.
				Uses ';' as a delimiter.
*/
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
/*
Function:		stringISBN
Author :		Terry Chiem
Parameters :	int isbn
Returns :		string
Description :	Converts the ISBN back to string and conserve any missing 0's.
*/
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
/*
Function:		stringDate
Author :		Henry Reusser
Parameters :	Date date
Returns :		none
Description :	Converts date object back into string and conserve 0's.
*/
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
/*
Function:		createBundle
Author :		Terry Chiem
Parameters :	none
Returns :		Bundle
Description :	Creates a bundle from the input file. Goes through each line
				in the file, splits the information into an array, and then
				creates a new Book.
*/
Bundle BookReader::createBundle()
{
	Bundle b;						// Create bundle
	std::string bookInfo;			// All book info in a single string
	int count = 0;					// Number of books

	// Read each line, separate into variables and create a new book
	while (getline(inFile, bookInfo))
	{
		//Split bookInfo into an array of strings
		const int PARAM = 8;					// Number of book parameters
		std::string info[PARAM];				// Array to store book info in
		splitInfo(info, bookInfo, PARAM);		// Call function to split bookInfo into array

		// Convert date info into Date object
		Date date(stoi(info[4].substr(0, 2)), stoi(info[4].substr(2, 2)), stoi(info[4].substr(4, 4)));

		// Add book to bundle
		b.addBook(Book(info[0], info[1], info[2], stoi(info[3]), date, stoi(info[5]), stod(info[6]), stod(info[7])));

		// Check bundle size
		b.ensureSize(++count);
	}
	inFile.close();
	return b;
}
/*
Function:		exportBundle
Author :		Terry Chiem
Parameters :	Bundle b - Bundle to be exported to output file
Returns :		none
Description :	Writes each book in the bundle to an output file.
*/
void BookReader::exportBundle(Bundle b)			// Sends bundle to output file
{
	// Open output file
	std::cout << "Exporting book inventory data to 'BookData.txt'\n";
	outFile.open("BookData.txt");

	std::cout << "Press <Enter> to Continue ...";
	std::string pause;
	getline(std::cin, pause);

	// Write to output file
	for (int i = 0; i < b.getSize(); i++) {
		outFile << b[i].getTitle() << ";" <<
			b[i].getAuthor() << ";" <<
			b[i].getPublisher() << ";" <<
			stringISBN(b[i].getISBN()) << ";" <<
			stringDate(b[i].getDate()) << ";" <<
			b[i].getQuantity() << ";" <<
			b[i].getCost() << ";" <<
			b[i].getPrice() << "\n";
	}

	std::cout << "Export completed!\n\n";
	outFile.close();
}