#define _CRT_SECURE_NO_WARNINGS
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

double CashRegister::getBalance() const		// Return balance
{
	return balance;
}

double CashRegister::getSales() const		// Return totalSales
{
	return totalSales;
}

double CashRegister::getProfit() const		// Return totalProfit
{
	return totalProfit;
}

double CashRegister::getTax() const		// Return totalTax
{
	return totalTax;
}

int CashRegister::getTransactions() const		// Return transactions
{
	return transactions;
}

int CashRegister::getBooksSold() const		// Return booksSold
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

void CashRegister::printReceipt(ShoppingCart c)			// Print details of current transaction
{
	printLines(50);
	std::cout << std::setw(44) << "Serendipity Booksellers Order Summary" << std::endl;
	std::cout << std::setw(30) << currentDate.toString() << std::endl;
	printLines(50);

	// Print book details (title, author, price)

	printLines(50);
	std::cout << std::setprecision(2) << std::fixed;
	std::cout << std::setw(40) << std::left << "Subtotal:" << c.getSubtotal() << std::endl;
	std::cout << std::setw(40) << std::left << "Tax:" << c.getTax() << std::endl;
	std::cout << std::setw(40) << std::left << "Total:" << c.getTotalCost() << std::endl << std::endl;
	std::cout << std::setw(40) << std::left << "Amount Paid:" << c.getAmountPaid() << std::endl;
	std::cout << std::setw(40) << std::left << "Change:" << c.getChange() << std::endl;
	printLines(50);
}

void CashRegister::printSalesReport()					// Print sales report of cash register
{
	printLines(50);
	std::cout << std::setw(43) << "Serendipity Booksellers Sales Report" << std::endl;
	std::cout << std::setw(30) << currentDate.toString() << std::endl;
	printLines(50);
	std::cout << std::setprecision(2) << std::fixed << std::endl;
	std::cout << std::setw(40) << std::left << "Register Balance:" << getBalance() << std::endl;
	std::cout << std::setw(40) << std::left << "Total Sales:" << getSales() << std::endl;
	std::cout << std::setw(40) << std::left << "Total Tax:" << getTax() << std::endl;
	std::cout << std::setw(40) << std::left << "Total Profit:" << getProfit() << std::endl;
	std::cout << std::setw(40) << std::left << "Number of Transactions:" << getTransactions() << std::endl;
	std::cout << std::setw(40) << std::left << "Number of Books Sold:" << getBooksSold() << std::endl << std::endl;
	printLines(50);
}

void CashRegister::printLines(int l)					// Print lines for formatting
{
	for (int i = 0; i < l; i++) {
		std::cout << "=";
	}
	std::cout << std::endl;
}


/*
To do:
- newTransaction
- refundBook
- input validation
- book details for printReceipt
- static variable for transactions


- possible feature: save receipts to output file
*/