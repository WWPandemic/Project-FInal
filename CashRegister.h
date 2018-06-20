#pragma once
#include <string>
#include "Bundle.h"
#include "Date.h"
#include "ShoppingCart.h"
#include "Menu.h"

class CashRegister : public Menu
{
private:
	// CashRegister variables
	Bundle *bPtr;						// Pointer to reference of main bundle
	const double TAX_RATE = 9.0;		// Current city tax rate
	Date currentDate;					// Current date
	double totalSales;					// Total sales
	double totalTax;					// Total tax collected
	double totalProfit;					// Total profit
	int transactions;					// Number of transactions
	int booksSold;						// Number of books sold

	// Mutators
	void setUpDate();					// Set current date
	void addSales(double s);			// Add amount to totalSales
	void addTax(double t);				// Add amount to totalTax
	void addProfit(double p);			// Add amount to totalProfit
	void addBookSold(int b);			// Add amount to booksSold
	void refundMoney(Book b);			// Reduce book amounts from register

	// Menu
	void getInput();
	void runOptions();

public:
	// Constructors
	CashRegister(Bundle &b);

	// Functions
	std::string getConfirmation();					// Get confirmation
	std::string getDate();							// Return date as string
	void newTransaction(Bundle *b);					// Create a new transaction (pass main book bundle)
	void processCart(ShoppingCart c);				// Adds cart values to register
	void reduceStock(Bundle *b, ShoppingCart c);	// Adjust inventory based on purchased items
	void increaseStock(Bundle *b, Book book);		// Add book back to inventory from refund
	int findIndex(const Bundle *b, Book book);		// Locates book's index in main bundle
	void refundBook(Bundle *b);						// Refund a book (pass main book bundle)
	Bundle sortISBN(Bundle *b);						// Sort bundle by isbn
	int searchISBN(Bundle b, int search);			// Search main bundle for isbn
	void printBook(Book);							// Print book details
	void printReceipt(ShoppingCart c);				// Print details of current transaction
	void printSalesReport();						// Print sales report of cash register
	void printCenter(std::string);					// Print center text in between line breaks
	void clearScreen();								// Clear text from console
};