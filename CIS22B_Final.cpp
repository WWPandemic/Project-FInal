#include <iostream>
#include <string>
#include "Bundle.h"

using namespace std;

int main() {
	Date testDate1(6, 5, 2018);
	Date testDate2(7, 4, 2018);
	Date testDate3(testDate1);
	Book testBook1("title", "author", "publisher", 1, testDate1, 12, 5.5, 10.75);
	Book testBook2 = testBook1;
	Bundle testBundle(5);
	testBundle.addBook(testBook1);
	testBundle.addBook(testBook2);
	cout << testBundle << endl;
	//testBundle.printAll();
	testBundle.addBook(testBook1);
	cout << "Please press  the <Enter> key to exit" << endl;
	cin.get();
	return 0;
}