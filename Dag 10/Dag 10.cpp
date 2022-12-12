#include <iostream>
#include <string>
#include <fstream>
#include "../../adventofcode2021/matrix/matrix.h"

using namespace std;

int sum = 0;
int cycle = 0;
int X = 1;

matrix<char, 6, 40> crt(' ');
int sprite_pos[3] { 0 ,1 ,2 };

void clock_cycle() {
	int row = cycle % 40;
	int col = cycle / 40;
	if (sprite_pos[0] == row || sprite_pos[1] == row || sprite_pos[2] == row) {
		crt[col][row] = '#';
	}
	cycle++;
}


int main()
{
	ifstream input("C:\\Users\\Jan\\Desktop\\input.txt");
	if (!input) {
		cout << "file not found" << endl;
		return 1;
	}

	string line;
	while (getline(input, line)) {
		string instruction = line.substr(0, 4);
		if (instruction == "noop")
			clock_cycle();
		else if (instruction == "addx") {
			int parameter = stoi(line.substr(5));
			clock_cycle();
			clock_cycle();
			X += parameter;
			sprite_pos[0] = X - 1;
			sprite_pos[1] = X;
			sprite_pos[2] = X + 1;
		}
	}

	cout << endl << crt << endl;
}