// Dag6.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

vector<char> v;

int main()
{
	ifstream input("C:\\Users\\Jan\\Desktop\\input.txt");
	if (!input) {
		cout << "file not found" << endl;
		return 1;
	}

	char ch;
	for (int i = 0; i < 14; i++) {
		input >> ch;
		v.push_back(ch);
	}

	int pos = 14;

	while (true) {
		vector<char> w(v);
		sort(w.begin(), w.end());
		bool alldifferent = true;
		for (int i = 0; i < 13; i++)
			if (w[i] == w[i + 1]) {
				alldifferent = false;
				break;
			}
		if (alldifferent)
			break;
		pos++;
		char ch;
		input >> ch;
		if (!input) {
			cout << "error ";
			break;
		}
		v.erase(v.begin());
		v.push_back(ch);
	}

	cout << pos << endl;

}
