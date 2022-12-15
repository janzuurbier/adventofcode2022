#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "..\..\adventofcode2021\matrix\matrix.h"

using namespace std;

//for part 2 add line to input: 488,11 -> 512,11
//const int N = 12;
//const int M = 25;
//const int XMIN = 488;

//for part 2 add line to input: 319,180 -> 681,180
const int N = 181;
const int M = 363;
const int XMIN = 319;

int main()
{
	ifstream input("C:\\Users\\Jan\\Desktop\\input.txt");
	if (!input) {
		cout << "file not found" << endl;
		return 1;
	}

	vector<pair<int, int>> v;

	string line;
	while (getline(input, line)) {
		stringstream ss(line);
		int xoud;
		int youd;
		char komma;
		string pijltje;
		ss >> xoud >> komma >> youd >> pijltje;
		while (ss) {
			int xnieuw, ynieuw;
			ss >> xnieuw >> komma >> ynieuw >> pijltje;
			if (xoud == xnieuw && youd <= ynieuw)
				for (int y = youd; y <= ynieuw; y++)
					v.push_back(pair<int, int>(xoud, y));
			if (xoud == xnieuw && youd >= ynieuw)
				for (int y = youd; y >= ynieuw; y--)
					v.push_back(pair<int, int>(xoud, y));
			if (youd == ynieuw && xoud <= xnieuw)
				for (int x = xoud; x <= xnieuw; x++)
					v.push_back(pair<int, int>(x, youd));
			if (youd == ynieuw && xoud >= xnieuw)
				for (int x = xoud; x >= xnieuw; x--)
					v.push_back(pair<int, int>(x, youd));
			xoud = xnieuw;
			youd = ynieuw;
		}
	}

	/*int xmin = 1000;
	int xmax = 0;
	int ymin = 1000;
	int ymax = 0;
	for (auto p : v) {
		if (p.first < xmin) xmin = p.first;
		if (p.first > xmax) xmax = p.first;
		if (p.second < ymin)ymin = p.second;
		if (p.second > ymax) ymax = p.second;
	}
	cout << ymax << endl;*/

	matrix <char, N, M>map('.');
	for (auto p : v)
		map[p.second][p.first - XMIN] = '#';

	bool in_the_endless_void = false;
	while (!in_the_endless_void) {
		in_the_endless_void = false;
		int xzand = 500, yzand = 0;
		bool hasmoved = true;
		while (hasmoved) {
			hasmoved = false;
			if (map.isInRange(yzand + 1, xzand - XMIN)) {
				if (map[yzand + 1][xzand - XMIN] == '.') {
					yzand++;
					hasmoved = true;
				}
			}
			else
				in_the_endless_void = true;

			if (!hasmoved)
				if (map.isInRange(yzand + 1, xzand - 1 - XMIN)) {
					if (map[yzand + 1][xzand - 1 - XMIN] == '.') {
						xzand--;
						yzand++;
						hasmoved = true;
					}
			}
			else
				in_the_endless_void = true;
			
			if (!hasmoved)
				if( map.isInRange(yzand + 1, xzand + 1 - XMIN)) {
					if (map[yzand + 1][xzand + 1 - XMIN] == '.') {
						xzand++;
						yzand++;
						hasmoved = true;
					}
				}
				else
					in_the_endless_void = true;

		}
		if(!in_the_endless_void) map[yzand][xzand - XMIN] = 'o';
		if (yzand == 0) break;
	}

	int sum = 0;
	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++)
			if (map[i][j] == 'o')
				sum++;
	cout << sum << endl; 	
}