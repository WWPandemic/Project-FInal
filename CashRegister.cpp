// CashRegister class definitions
#include <iostream>
#include <iomanip>
#include <string>
#include "CashRegister.h"

//**************************
//* Constructor definition *
//**************************

CashRegister::CashRegister()
{
	totalSales = 0.0;
	totalTax = 0.0;
	totalProfit = 0.0;
	transactions = 0;
	booksSold = 0;

	int m, d, y, x;			// Temp for input
	std::cout << "Starting up Cash Register module ...\n";
	std::cout << "Please enter today's date (MM DD YYYY): ";			// Needs validation
	std::cin >> m >> d >> y;
	currentDate.setDate(m, d, y);
	std::cout << "Please enter amount of money in cash register: $";		// Needs validation
	std::cin >> x;
	balance = x;
}

//************************
//* Accessor definitions *
//************************

std::string CashRegister::getDate()			// Return date as string
{
	return currentDate.toString();
}

double CashRegister::getBalance()			// Return balance
{
	return balance;
}

double CashRegister::getSales()				// Return totalSales
{
	return totalSales;
}

double CashRegister::getProfit()			// Return totalProfit
{
	return totalProfit;
}

double CashRegister::getTax()				// Return totalTax
{
	return totalTax;
}

int CashRegister::getTransactions()			// Return transactions
{
	return transactions;
}

int CashRegister::getBooksSold()			// Return booksSold
{
	return booksSold;
}

//***********************
//* Mutator definitions *
//***********************

void CashRegister::setDate(int m, int d, int y)		// Set currentDate
{
	currentDate.setDate(m, d, y);
}

void CashRegister::setBalance(double b)				// Set balance
{
	balance = b;
}

void CashRegister::addSales(double s)				// Add amount to totalSales
{
	totalSales += s;
}

void CashRegister::addTax(double t)					// Add amount to totalTax
{
	totalTax += t;
}

void CashRegister::addProfit(double p)				// Add amount to totalProfit
{
	totalProfit += p;
}

void CashRegister::addTransaction()					// Add one to transactions
{
	transactions++;
}

void CashRegister::addBookSold()					// Add one to booksSold
{
	booksSold++;
}

//************************
//* Function definitions *
//************************

ShoppingCart CashRegister::newTransaction(Bundle b)		// Create a new transaction
{
	// Ask user to enter ISBN
		// Sentinel value to stop
	// Calculate values
	// Return shopping cart
}

void CashRegister::refundBook(Bundle b)					// Refund a book
{
	// Ask user to enter ISBN
	// Reduce balance, totalSales, totalProfit by book price
	// Add one to book quantity
}

// *** Needs reformatting ***
void CashRegister::printReceipt(ShoppingCart c)			// Print details of current transaction
{
	printLines(25);
	std::cout << "Serendipity Booksellers Order Summary" << std::endl;
	std::cout << currentDate.toString() << std::endl;
	printLines(25);

	// Print book details (title, author, price)

	printLines(25);
	std::cout << std::setprecision(2) << std::fixed;
	std::cout << "Subtotal: $" << c.getSubtotal() << std::endl;
	std::cout << "Tax: $" << c.getTax() << std::endl;
	std::cout << "Total: $" << c.getTotalCost << std::endl << std::endl;
	std::cout << "Amount Paid: $" << c.getAmountPaid() << std::endl;
	std::cout << "Change: $" << c.getChange() << std::endl;
	printLines(25);
}

// *** Needs reformatting ***
void CashRegister::printSalesReport()					// Print sales report of cash register
{
	printLines(25);
	std::cout << "Serendipity Booksellers Sales Report" << std::endl;
	std::cout << currentDate.toString() << std::endl;
	printLines(25);
	std::cout << std::setprecision(2) << std::fixed << std::endl;
	std::cout << "Register Balance: $" << getBalance() << std::endl;
	std::cout << "Total Sales: $" << getSales() << std::endl;
	std::cout << "Total Tax: $" << getTax() << std::endl;
	std::cout << "Total Profit: $" << getProfit() << std::endl;
	std::cout << "Number of Transactions: " << getTransactions() << std::endl;
	std::cout << "Number of Books Sold: " << getBooksSold() << std::endl << std::endl;
	printLines(25);
}

void CashRegister::printLines(int l)					// Print lines for formatting
{
	for (int i = 0; i < l; i++) {
		std::cout << "=";
	}
	std::cout << std::endl;
}