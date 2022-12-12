// Dag5.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <stack>
#include <vector>

using namespace std;
const int N = 9;

stack<char> stacks[N];

//char inputgetallen [][N]{ { 'Z', 'N' }, { 'M', 'C', 'D' }, { 'P' } };

char inputgetallen[][N]{
	{ 'S', 'Z', 'P', 'D', 'L', 'B', 'F', 'C'},
	{ 'N', 'V', 'G', 'P', 'H', 'W', 'B'},
	{ 'F', 'W', 'B', 'J', 'G' },
	{ 'G', 'J', 'N', 'F', 'L', 'W', 'C', 'S' },
	{ 'W', 'J', 'L', 'T', 'P', 'M', 'S', 'H' },
	{ 'B', 'C', 'W', 'G', 'F', 'S' },
	{ 'H', 'T', 'P', 'M', 'Q', 'B', 'W' },
	{ 'F', 'S', 'W', 'T'},
	{ 'N', 'C', 'R'} 
};




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
		if (line.size() == 0) break;
	}

	for (int i = 0; i < N; i++) {
		for (char ch : inputgetallen[i]) {
			if(ch >= 'A' && ch <= 'Z')
			stacks[i].push(ch);
			cout << ch;
		}
		cout << endl;
	}

	for (int i = 0; i < N; i++)
		cout << stacks[i].size() << '\t'; 
	cout << endl;

	
	while (getline(input, line)) {
		istringstream invoerregel(line);
		string woord;
		int aantal, van, naar;
		invoerregel >> woord >> aantal >> woord >> van >> woord >> naar; 
		string s;
		for (int i = 0; i < aantal; i++) {
			//char ch = stacks[van - 1].top();
			//stacks[naar - 1].push(ch);
			//stacks[van - 1].pop();
			
			char ch = stacks[van - 1].top();
			s = ch + s;
			stacks[van - 1].pop();
		}
		for (char ch : s)
			stacks[naar - 1].push(ch);

			

		

		for (int i = 0; i < N; i++)
			cout << stacks[i].size() << '\t';
		cout << endl;
	}

	for (int i = 0; i < N; i++)
		cout << stacks[i].top();


}




