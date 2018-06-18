#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include "Bundle.h"

using namespace std;

int main() {
	Date testDate1(6, 5, 2018);

	Book testBook1("a", "*", "*", 1, testDate1, 2, 1, 1);
	Book testBook2("b", "*", "*", 1, testDate1, 2, 1, 1);
	Book testBook3("c", "*", "*", 1, testDate1, 2, 1, 1);
	Book testBook4("d", "*", "*", 1, testDate1, 2, 1, 1);
	Book testBook5("e", "*", "*", 1, testDate1, 2, 1, 1);
	
	Bundle testBundle(25);
	testBundle.addBook(testBook5);
	testBundle.addBook(testBook3);
	testBundle.addBook(testBook2);
	testBundle.addBook(testBook4);
	testBundle.addBook(testBook1);

	testBundle.addBook("f", "*", "*", 1, testDate1, 2, 1, 1);
	testBundle.addBook("e", "*", "*", 1, testDate1, 2, 1, 1);
	testBundle.addBook("z", "*", "*", 1, testDate1, 2, 1, 1);
	testBundle.addBook("h", "1*", "*", 1, testDate1, 2, 1, 1);
	testBundle.addBook("e", "1*", "*", 1, testDate1, 2, 1, 1);
	
	cout << testBundle << endl;
	int index = testBundle.findFirstIndex("e");
	cout << index << endl;

	int index2[2] = { 0,0 };
	testBundle.findIndexBounds("e",index2);
	cout << "is something happening" << endl;
	cout << index2[0] << " " << index2[1] << endl;

	cout << "Please press the <Enter> key to exit" << endl;
	cin.get();
	return 0;
}