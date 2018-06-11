#define _CRT_SECURE_NO_WARNINGS
#include <cctype>
#include "Inventory.h"

void Inventory::runOptions()
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
		Book* b = books->getBundle();
		(b + index)->print();
	}
}

void Inventory::AddNewBooks()
{
	int count = 0;
	std::cout << "How many books do you want to add?" << std::endl;
	std::cin >> count;

	for (int i = 0; i < count; i++)
	{
		std::cout << "Enter the title for book #" << i + 1 << ": ";
		std::string title;
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

		int month = std::stoi(today.substr(0, 2));
		int day = std::stoi(today.substr(3, 2));
		int year = std::stoi(today.substr(6, 4));
		Date todayDate(month, day, year);

		books->addBook(title, author, publisher, ISBN, todayDate, quantity, cost, price);

		std::cout << "Book added.\n\n";
	}


}

void Inventory::DeleteBooks()
{
	int count = 0;
	std::cout << "How many books do you want to delete?" << std::endl;
	std::cin >> count;

	for (int i = 0; i < count; i++)
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
			books->removeBook(index);
			std::cout << "Book deleted.\n\n";
		}
	}

}

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
		
	}
}

int Inventory::searchByTitle(std::string title)
{
	int index = -1;
	return index;
}

int Inventory::searchByISBN(int ISBN)
{
	int index = -1;
	return index;
}
