// Dag 4.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

int main()
{
	ifstream input("C:\\Users\\Jan\\Desktop\\input.txt");
	if (!input) {
		cout << "file not found" << endl;
		return 1;
	}

	int sum = 0;

	string line;
	while (getline(input, line)) {
		istringstream in(line);
		char komma, streepje;
		int a, b, c, d;
		in >> a >> komma >> b >> streepje >> c >> komma >> d;
		//if (a <= c && b >= d || a >= c && b <= d) sum++;
		if (!(b < c) && !(d < a)) sum++;
	}
	cout << sum << endl;
}

