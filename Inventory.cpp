#define _CRT_SECURE_NO_WARNINGS
#include <cctype>
#include "Inventory.h"

void Inventory::runOptions()//Runs function selected earlier by user.
{
	switch (chosenOption)
	{
	case 1:
		LookUpBooks();
		break;
	case 2:
		AddNewBooks();
		break;
	case 3:
		DeleteBooks();
		break;
	case 4:
		EditBookInformation();
		break;
	case 5:
	default:
		isUsingMenu = false;
		break;
	}
}

/*
Prompts the user to enter the title or ISBN of desired book.
If the user input begins and ends with a number it is assumed that the input is an ISBN and the search by ISBN function is called.
If not the user input is assumed to be a title and the search by title function is called.
If a valid index (i.e. greater than zero) is returned by either function the details of the book at that index are printed. 
*/
void Inventory::LookUpBooks()
{
	std::cout << "Enter the title or ISBN of the book: ";
	std::string info;
	getline(std::cin, info);

	int index;

	if (std::isdigit(info.front()) && std::isdigit(info.back()))
		index = searchByISBN(std::stoi(info));
	else
		index = searchByTitle(info);

	if (index < 0)
		std::cout << "Book was not found.\n\n";
	else
	{
		std::cout << (*books)[index] << std::endl;
	}
}

/*
The user is prompted to enter the desired number of books to add.
The user is promted to enter the required data to make a book, the the book is added to the bundle.
This is repeated the number of times the user specified.
*/
void Inventory::AddNewBooks()
{
	int count = 0;
	std::cout << "How many books do you want to add?" << std::endl;
	std::cin >> count;

	for (int i = 0; i < count; i++)
	{
		std::cout << "Enter the title for book #" << i + 1 << ": ";
		std::string title;
		std::cin.ignore();
		getline(std::cin, title);

		std::cout << "Enter the author's name for book #" << i + 1 << ": ";
		std::string author;
		getline(std::cin, author);

		std::cout << "Enter the publisher for book #" << i + 1 << ": ";
		std::string publisher;
		getline(std::cin, publisher);

		std::cout << "Enter the ISBN for book #" << i + 1 << ": ";
		int ISBN;
		std::cin >> ISBN;

		std::cout << "Enter today's date (MM/DD/YYYY): ";
		std::string today;
		std::cin >> today;

		std::cout << "Enter the number on hand: ";
		int quantity;
		std::cin >> quantity;

		std::cout << "Enter the wholesale cost for book #" << i + 1 << ": ";
		double cost;
		std::cin >> cost;

		std::cout << "Enter the retail price for book #" << i + 1 << ": ";
		double price;
		std::cin >> price;

		int month = std::stoi(today.substr(0, 2));//Series of lines to find the date in a string entered MM/DD/YYYY
		int day = std::stoi(today.substr(3, 2));  //And turn the string into three numbers representing the date.
		int year = std::stoi(today.substr(6, 4));
		Date todayDate(month, day, year);

		(*books).addBook(title, author, publisher, ISBN, todayDate, quantity, cost, price);
		
		std::cin.ignore();
		std::cout << "Book added.\n\n";
	}


}

/*
Prompts the user to enter number of books to be deleted
Prompts the user to enter the title or ISBN of the book to be deleted.
If the user input begins and ends with a number it is assumed that the input is an ISBN and the search by ISBN function is called.
If not the user input is assumed to be a title and the search by title function is called.
If a valid index (i.e. greater than zero) is returned by either function the book is deleted from the bundle.
This is repeated the specified number of times.
*/
void Inventory::DeleteBooks()
{
	int count = 0;
	std::cout << "How many books do you want to delete?" << std::endl;
	std::cin >> count;

	for (int i = 0; i < count; i++)
	{
		std::cout << "Enter the title or ISBN of the book: ";
		std::string info;
		std::cin.ignore();
		getline(std::cin, info);

		int index;

		if (std::isdigit(info.front()) && std::isdigit(info.back()))
			index = searchByISBN(std::stoi(info));
		else
			index = searchByTitle(info);

		if (index < 0)
			std::cout << "Book was not found.\n\n";
		else
		{
			(*books).removeBook(index);
			std::cout << "Book deleted.\n\n";
		}
	}

}

/*
Promts the user to enter the title or ISBN of the book to be edited.
If the user input begins and ends with a number it is assumed that the input is an ISBN and the search by ISBN function is called.
If not the user input is assumed to be a title and the search by title function is called.
If a valid index (i.e. greater than zero) is returned by either function the user is given a menu a prompted to select a field to be edited.
Once the selection is made the user is then prompted to enter the information they wish to change it to.
*/
void Inventory::EditBookInformation()
{
	std::cout << "Enter the title or ISBN of the book: ";
	std::string info;
	getline(std::cin, info);

	int index;

	if (std::isdigit(info.front()) && std::isdigit(info.back()))
		index = searchByISBN(std::stoi(info));
	else
		index = searchByTitle(info);

	if (index < 0)
		std::cout << "Book was not found.\n\n";
	else
	{
		std::cout << "---------------------------------------------------------------------------" << std::endl;
		std::cout << "                         Options For Editing:" << std::endl;
		std::cout << "1 - Title" << std::endl;
		std::cout << "2 - Author" << std::endl;
		std::cout << "3 - Publisher" << std::endl;
		std::cout << "4 - ISBN" << std::endl;
		std::cout << "5 - Date Added" << std::endl;
		std::cout << "6 - Quantity On Hand" << std::endl;
		std::cout << "7 - Wholesale Cost" << std::endl;
		std::cout << "8 - Retail Price" << std::endl;
		std::cout << "---------------------------------------------------------------------------" << std::endl;
		std::cout << "What will you edit?" << std::endl;
		std::string input;
		getline(std::cin, input);
		switch (std::stoi(input))
		{
		case 1:
			std::cout << "Enter a new title: ";
			getline(std::cin, input);
			(*books)[index].setTitle(input);
			std::cout << "Title set\n";
			break;
		case 2:
			std::cout << "Enter a new author: ";
			getline(std::cin, input);
			(*books)[index].setAuthor(input);
			std::cout << "Author set\n";
			break;
		case 3:
			std::cout << "Enter a new publisher: ";
			getline(std::cin, input);
			(*books)[index].setPublisher(input);
			std::cout << "Publisher set\n";
			break;
		case 4:
			std::cout << "Enter a new ISBN: ";
			int ISBN;
			std::cin >> ISBN;
			(*books)[index].setISBN(ISBN);
			std::cout << "ISBN set\n";
			break;
		case 5:
			int day[3];
			std::cout << "Enter month added: ";
			std::cin >> day[0];
			std::cout << "Enter day added: ";
			std::cin >> day[1];
			std::cout << "Enter year added: ";
			std::cin >> day[2];
			(*books)[index].setDate(Date(day));
			std::cout << "Date set\n";
			break;
		case 6:
			std::cout << "Enter quantity on hand: ";
			int num;
			std::cin >> num;
			(*books)[index].setQuantity(num);
			std::cout << "Quantity on hand set\n";
			break;
		case 7:
			std::cout << "Enter a new wholesale cost: ";
			double cost;
			std::cin >> cost;
			(*books)[index].setCost(cost);
			std::cout << "Cost set\n";
			break;
		case 8:
			std::cout << "Enter a new retail price: ";
			double price;
			std::cin >> price;
			(*books)[index].setPrice(price);
			std::cout << "Retail price set\n";
			break;
		default:
			std::cout << "Invalid Input\n\n";
			break;
		}
	}
}

/*
The bundle is first sorted to ensure it is in order by title
Then a binary search is conducted to find the index of a book with a matching title
The index of that book is returned if found.
Otherwise index is set to -1 to indicate the book was not found.
*/
int Inventory::searchByTitle(std::string title)
{
	for (int i = 0; i < (*books).getSize(); i++)
	{
		int min = i;
		for (int j = i + 1; j < (*books).getSize(); j++)
			if ((*books)[j].getTitle() < (*books)[min].getTitle())
				min = j;
		if (min != i)
		{
			Book temp((*books)[i]);
			(*books)[i] = (*books)[min];
			(*books)[min] = temp;
		}
	}
	
	int index = -1;
	int first = 0;
	int last = (*books).getSize();

	while (first <= last && index == -1)
	{
		int mid = (first + last) / 2;
		if ((*books)[mid].getTitle() == title)
			index = mid;
		else if ((*books)[mid].getTitle() < title)
			first = mid + 1;
		else
			last = mid - 1;
	}
	
	return index;
}

/*
The bundle is sorted to be in order by ISBN
A binary search is conducted to find the index of a book with a matching ISBN
The bundle is resorted to be in order by title becuase the bundle class is designed to always be in order by title.
The index of the matching book is modified as part of the seccond sort to ensure it is still acurate.
The index is returned and is either -1 if the book was not found or is the index of the book that has the correct ISBN.
*/
int Inventory::searchByISBN(int ISBN)
{
	for (int i = 0; i < (*books).getSize(); i++)
	{
		int min = i;
		for (int j = i + 1; j < (*books).getSize(); j++)
			if ((*books)[j].getISBN() < (*books)[min].getISBN())
				min = j;
		if (min != i)
		{
			Book temp((*books)[i]);
			(*books)[i] = (*books)[min];
			(*books)[min] = temp;
		}
	}

	int index = -1;
	int first = 0;
	int last = (*books).getSize();

	while (first <= last && index == -1)
	{
		int mid = (first + last) / 2;
		if ((*books)[mid].getISBN() == ISBN)
			index = mid;
		else if ((*books)[mid].getISBN() < ISBN)
			first = mid + 1;
		else
			last = mid - 1;
	}

	for (int i = 0; i < (*books).getSize(); i++)
	{
		int min = i;
		for (int j = i + 1; j < (*books).getSize(); j++)
			if ((*books)[j].getTitle() < (*books)[min].getTitle())
				min = j;
		if (min != i)
		{
			Book temp((*books)[i]);
			(*books)[i] = (*books)[min];
			(*books)[min] = temp;
			if (min == index)
				index = i;
		}
	}
	return index;
}
