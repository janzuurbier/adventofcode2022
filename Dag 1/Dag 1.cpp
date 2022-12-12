// Dag 1.cpp : This file contains the 'main' function. Program execution begins and ends there.
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

	int sum = 0, max1 = 0, max2 = 0, max3 = 0;

	string line;
	while (getline(input, line)) {
		if (line.size() == 0) {
			//cout << sum << endl;
			if (sum > max1) {
				max3 = max2; max2 = max1;  max1 = sum;
			}
			else if (sum > max2) {
				max3 = max2;  max2 = sum;
			}
			else if (sum > max3)
				max3 = sum;
			//cout << max1 << '\t' << max2 << '\t' << max3 << endl;
			sum = 0;
		}
		else {
			int cals = stoi(line);
			sum += cals;
		}
	}
	cout << max1 + max2 + max3 << endl;

}