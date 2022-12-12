// Dag 9.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <set>
#include "../../adventofcode2021/matrix/matrix.h"

using namespace std;

void update_tail(int& xt, int& yt, int xh, int yh) {
	
	if (xt - xh > 1) {
		xt--;
		if (yt > yh) yt--;
		else if (yt < yh) yt++;
	}
	if (xh - xt > 1) {
		xt++;
		if (yt > yh) yt--;
		else if (yt < yh) yt++;
	}
	if (yt - yh > 1) {
		yt--;
		if (xt > xh) xt--;
		else if (xt < xh) xt++;
	}
	if (yh - yt > 1) {
		yt++;
		if (xt > xh) xt--;
		else if (xt < xh) xt++;
	}
}

int main()
{
	ifstream input("C:\\Users\\Jan\\Desktop\\input.txt");
	if (!input) {
		cout << "file not found" << endl;
		return 1;
	}

	set<pair<int, int>> tail_positions;
	int x[10]{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	int y[10]{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

	

	string line;
	while (getline(input, line)) {
		stringstream regel(line);
		char dir;
		int steps;
		regel >> dir;
		regel >> steps;
		
		switch (dir) {
		case 'U': {
			for (int i = 0; i < steps; i++) {
				y[0]++;
				for(int i = 1; i <= 9; i++)
					update_tail(x[i], y[i], x[i-1], y[i-1]);
				tail_positions.insert(pair<int, int>(x[9], y[9]));
			}
			break;
		}
		case 'D': {
			for (int i = 0; i < steps; i++) {
				y[0]--;
				for (int i = 1; i <= 9; i++)
					update_tail(x[i], y[i], x[i - 1], y[i - 1]);
				tail_positions.insert(pair<int, int>(x[9], y[9]));
			}
			break;
		}
		case 'R': {
			for (int i = 0; i < steps; i++) {
				x[0]++;
				for (int i = 1; i <= 9; i++)
					update_tail(x[i], y[i], x[i - 1], y[i - 1]);
				tail_positions.insert(pair<int, int>(x[9], y[9]));
			}
			break;
		}
		case 'L': {
			for (int i = 0; i < steps; i++) {
				x[0]--;
				for (int i = 1; i <= 9; i++)
					update_tail(x[i], y[i], x[i - 1], y[i - 1]);
				tail_positions.insert(pair<int, int>(x[9], y[9]));
			}
			break;
		}
		}
		
	}

	cout << endl << tail_positions.size() << endl;
}
