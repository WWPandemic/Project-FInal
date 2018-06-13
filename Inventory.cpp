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
		Book* b = books->getBundle();
		switch (std::stoi(input))
		{
		case 1:
			std::cout << "Enter a new title: ";
			getline(std::cin, input);
			(b + index)->setTitle(input);
			std::cout << "Title set\n";
			break;
		case 2:
			std::cout << "Enter a new author: ";
			getline(std::cin, input);
			(b + index)->setAuthor(input);
			std::cout << "Author set\n";
			break;
		case 3:
			std::cout << "Enter a new publisher: ";
			getline(std::cin, input);
			(b + index)->setPublisher(input);
			std::cout << "Publisher set\n";
			break;
		case 4:
			std::cout << "Enter a new ISBN: ";
			int ISBN;
			std::cin >> ISBN;
			(b + index)->setISBN(ISBN);
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
			//Date d(day);
			(b + index)->setDate(Date(day));
			std::cout << "Date set\n";
			break;
		case 6:
			std::cout << "Enter quantity on hand: ";
			int num;
			std::cin >> num;
			(b + index)->setQuantityOnHand(num);
			std::cout << "Quantity on hand set\n";
			break;
		case 7:
			std::cout << "Enter a new wholesale cost: ";
			double cost;
			std::cin >> cost;
			(b + index)->setWholesaleCost(cost);
			std::cout << "Cost set\n";
			break;
		case 8:
			std::cout << "Enter a new retail price: ";
			double price;
			std::cin >> price;
			(b + index)->setRetailPrice(price);
			std::cout << "Retail price set\n";
			break;
		default:
			std::cout << "Invalid Input\n\n";
			break;
		}
	}
}

int Inventory::searchByTitle(std::string title)
{
	Book* b = books->getBundle();
	for (int i = 0; i < books->getSize(); i++)
	{
		int min = i;
		for (int j = i + 1; j < books->getSize(); j++)
			if ((b + j)->getTitle() < (b + min)->getTitle())
				min = j;
		if (min != i)
		{
			std::string temp = (b + min)->getTitle();
			(b + min)->setTitle((b + i)->getTitle());
			(b + i)->setTitle(temp);
		}
	}
	
	int index = -1;
	int first = 0;
	int last = books->getSize();

	while (first <= last && index == -1)
	{
		int mid = (first + last) / 2;
		if ((b + mid)->getTitle() == title)
			index = mid;
		else if ((b + mid)->getTitle() < title)
			first = mid + 1;
		else
			last = mid - 1;
	}
	
	return index;
}

int Inventory::searchByISBN(int ISBN)
{
	Book* b = books->getBundle();
	for (int i = 0; i < books->getSize(); i++)
	{
		int min = i;
		for (int j = i + 1; j < books->getSize(); j++)
			if ((b + j)->getISBN() < (b + min)->getISBN())
				min = j;
		if (min != i)
		{
			int temp = (b + min)->getISBN();
			(b + min)->setISBN((b + i)->getISBN());
			(b + i)->setISBN(temp);
		}
	}

	int index = -1;
	int first = 0;
	int last = books->getSize();

	while (first <= last && index == -1)
	{
		int mid = (first + last) / 2;
		if ((b + mid)->getISBN() == ISBN)
			index = mid;
		else if ((b + mid)->getISBN() < ISBN)
			first = mid + 1;
		else
			last = mid - 1;
	}
	return index;
}
