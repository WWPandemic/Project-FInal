#pragma once
#include "Bundle.h"

class ShoppingCart : public Bundle
{
private:
	const double TAX_RATE = 9.0;	// Current city tax rate
	double subtotal;				// Total cost before taxes
	double totalCost;				// Total cost of ShoppingCart
	double totalProfit;				// Total profit of ShoppingCart
	double amountPaid;				// Total paid by customer
	double change;					// Change owed to customer
	bool completeCart;				// If cart is valid or not

public:
	// Constructors
	ShoppingCart();
	ShoppingCart(Bundle);
	~ShoppingCart();

	// Accessors
	double getSubtotal() const;				// Return subtotal
	double getTotalCost() const;			// Return totalCost
	double getTotalProfit() const;			// Return totalProfit
	double getAmountPaid() const;			// Return amountPaid
	double getChange() const;				// Return change
	double getTax() const;					// Return tax amount
	bool getComplete() const;				// Return complete cart status

	// Mutators
	void addSubtotal(double);			// Add amount to subtotal
	void addTotalProfit(double);		// Add amount to totalProfit
	void calculateTotal();				// Calculate totalCost
	void calculateChange();				// Calculate change
	void processPay();					// Input value for amountPaid

	// Functions
	void addItems(Bundle);				// Add items to cart
	void sortISBN(Bundle);				// Sort bundle by isbn
	int searchISBN(Bundle, int);		// Search main bundle for isbn
	void processTotals();				// Calculate all total values
	void validateCart();				// Validate status of cart
	void printAll();					// Print all books in cart
};