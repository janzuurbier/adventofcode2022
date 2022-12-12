// Dag 3.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <fstream>


using namespace std;


int main()
{
	ifstream input("C:\\Users\\Jan\\Desktop\\input.txt");
	if (!input) {
		cout << "file not found" << endl;
		return 1;
	}

	int sum = 0;

	string line1, line2, line3;
	while (getline(input, line1)) {
		getline(input, line2);
		getline(input, line3);
		
		for (char ch : line1)
			if (line2.find(ch) != string::npos && line3.find(ch) != string::npos) {
				//cout << ch << endl;
				sum += ch >= 'a' ? ch - 'a' + 1 : ch - 'A' + 27;
				break;
			}
	}
	cout << endl << sum << endl;
}