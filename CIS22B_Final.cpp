#include <iostream>
#include <string>
#include "Book.h"


using namespace std;

int main() {
	Date testdate(5, 26, 2018);
	Book testbook("title", "author", "publisher", 1, testdate, 12, 5.5, 10.75);
	cout << testbook.toString() << endl;
	system("pause");
	return 0;
}