#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "../matrix/matrix.h"

using namespace std;

//const int N = 12;
//const int M = 16;
const int N = 200;
const int M = 150;
enum direction_t {RIGHT, DOWN, LEFT, UP};

matrix<char, N, M> kaart(' ');
int x = 0;
int y = 0;
direction_t dir = RIGHT;
char dir_char = '>';

void advance() {
	int new_x = x;
	int new_y = y;
	switch (dir) {
	case RIGHT: 
		new_x++;
		if (new_x > M - 1)	new_x = 0;
		while (kaart[new_y][new_x] == ' ') {
			new_x++;
			if (new_x > M - 1)	new_x = 0;
		}
		break;
	case DOWN: 
		new_y++;
		if (new_y > N - 1)new_y = 0;
		while (kaart[new_y][new_x] == ' ') {
			new_y++;
			if (new_y > N - 1)new_y = 0;	
		}
		break;
	case LEFT: 
		new_x--;
		if (new_x < 0)new_x = M - 1;
		while (kaart[new_y][new_x] == ' ') {
			new_x--;
			if (new_x < 0)new_x = M - 1;	
		}
		break;
	case UP: 
		new_y--;
		if (new_y < 0)new_y = N - 1;
		while (kaart[new_y][new_x] == ' ') {
			new_y--;
			if (new_y < 0)new_y = N - 1;
		}
		break;
	}
	if (kaart[new_y][new_x] != '#') {
		x = new_x;
		y = new_y;
		kaart[y][x] = dir_char;
	}
}

void turn_right() {
	switch (dir) {
	case RIGHT: dir = DOWN; dir_char = 'v'; break;
	case DOWN: dir = LEFT; dir_char = '<'; break;
	case LEFT: dir = UP; dir_char = '^'; break;
	case UP: dir = RIGHT; dir_char = '>'; break;
	}
	kaart[y][x] = dir_char;
}

void turn_left() {
	switch (dir) {
	case RIGHT: dir = UP; dir_char = '^'; break;
	case DOWN: dir = RIGHT; dir_char = '>'; break;
	case LEFT: dir = DOWN; dir_char = 'v'; break;
	case UP: dir = LEFT; dir_char = '<'; break;
	}
	kaart[y][x] = dir_char;
}


void read_map(istream& is, matrix<char, N, M>& k) {
	string line;
	for (int i = 0; i < N; i++) {
		getline(is, line);
		for (int j = 0; j < line.size() && j < M; j++) {
			k[i][j] = line[j];
		}
	}
}


int main()
{
	ifstream input("C:\\Users\\Jan\\Desktop\\input.txt");
	if (!input) {
		cout << "file not found" << endl;
		return 1;
	}
	ofstream output("C:\\Users\\Jan\\Desktop\\output.txt");
	read_map(input, kaart);
	advance();

	string line;
	getline(input, line);
	getline(input, line);

	stringstream ss(line);
	char ch;
	int steps;
	ss >> steps;
	for (int i = 0; i < steps; i++) advance();
	while (true) {
		ss >> ch;
		if (!ss) break;
		if (ch == 'L') turn_left();
		if (ch == 'R') turn_right();
		ss >> steps;
		if (!ss) break;
		for (int i = 0; i < steps; i++)advance();
	}
	output << kaart << endl;
	cout << "row: " << y + 1 << endl;
	cout << "col: " << x + 1 << endl;
	cout << "dir: " << dir << endl;
	cout << "password: " << 1000 * (y + 1) + 4 * (x + 1) + dir << endl;
}

