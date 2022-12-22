#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "../matrix/matrix.h"

using namespace std;

const int N = 200;
const int M = 150;
const int K = 50;
enum direction_t { RIGHT, DOWN, LEFT, UP };

matrix<char, N, M> kaart(' ');
int x = 0;
int y = 0;
int f = 1;
direction_t dir = RIGHT;
char dir_char = '>';
char get_dir_char() {
	switch (dir) {
	case UP: return '^';
	case DOWN: return 'v';
	case LEFT: return '<';
	case RIGHT: return '>';
	}
}

matrix<char, K, K> faces[7] = { matrix<char, K, K>(' '),
								matrix<char, K, K>(' '),
								matrix<char, K, K>(' '),
								matrix<char, K, K>(' '),
								matrix<char, K, K>(' '),
								matrix<char, K, K>(' '),
								matrix<char, K, K>(' ') };

void to_new_face(int& f , int& x, int& y, direction_t& dir) {
	switch (f) {
	case 1:
		switch (dir) {
		case RIGHT: f = 2; x = 0; y = y; dir = RIGHT; break;
		case DOWN: f = 3; x = x;  y = 0;  dir = DOWN;  break;
		case LEFT: f = 4; x = 0; y = K - 1 - y; dir = RIGHT; break;
		case UP: f = 6; y = x;  x = 0;  dir = RIGHT; break;
		}
		break;
	case 2:
		switch (dir) {
		case RIGHT: f = 5; x = K - 1; y = K - 1 - y; dir = LEFT; break;
		case DOWN: f = 3;  y = x; x = K - 1; dir = LEFT; break;
		case LEFT: f = 1; x = K - 1; y = y; dir = LEFT; break;
		case UP: f = 6;  x = x; y = K - 1;  dir = UP; break;
		}
		break;
	case 3:
		switch (dir) {
		case RIGHT: f = 2; x = y; y = K - 1; dir = UP; break;
		case DOWN: f = 5; x = x; y = 0; dir = DOWN; break;
		case LEFT: f = 4; x = y; y = 0; dir = DOWN; break;
		case UP: f = 1; x = x; y = K - 1; dir = UP; break;
		}
		break;
	case 4:
		switch (dir) {
		case RIGHT: f = 5; x = 0; y = y; dir = RIGHT; break;
		case DOWN: f = 6; x = x; y = 0; dir = DOWN; break;
		case LEFT: f = 1; x = 0; y = K - 1 - y; dir = RIGHT; break;
		case UP: f = 3;  y = x; x = 0; dir = RIGHT; break;
		}
		break;
	case 5:
		switch (dir) {
		case RIGHT: f = 2; x = K - 1; y = K - 1 - y; dir = LEFT; break; 
		case DOWN: f = 6; y = x; x = K - 1;  dir = LEFT; break;
		case LEFT: f = 4; x = K - 1; y = y; dir = LEFT; break; 
		case UP: f = 3; x = x; y = K - 1; dir = UP; break; 
		}
		break;
	case 6:
		switch (dir) {
		case RIGHT: f = 5; x = y; y = K - 1; dir = UP; break; 
		case DOWN: f = 2; x = x; y = 0; dir = DOWN; break; 
		case LEFT: f = 1; x = y; y = 0; dir = DOWN; break;
		case UP: f = 4; x = x; y = K - 1; dir = UP; break; 
		}
		break;
	}
}
								
void advance() {
	int new_x = x;
	int new_y = y;
	int new_f = f;
	direction_t new_dir = dir;
	switch (dir) {
	case RIGHT:
		new_x++;
		if (new_x > K - 1)
			to_new_face(new_f, new_x, new_y, new_dir);
		break;
	case DOWN:
		new_y++;
		if (new_y > K - 1)
			to_new_face(new_f, new_x, new_y, new_dir);
		break;
	case LEFT:
		new_x--;
		if (new_x < 0)
			to_new_face(new_f, new_x, new_y, new_dir);
		break;
	case UP:
		new_y--;
		if (new_y < 0)
			to_new_face(new_f, new_x, new_y, new_dir);
		break;
	}
	if (faces[new_f][new_y][new_x] != '#') {
		x = new_x;
		y = new_y;
		f = new_f;
		dir = new_dir;
		faces[new_f][y][x] = get_dir_char();
	}
}

void turn_right() {
	switch (dir) {
	case RIGHT: dir = DOWN;  break;
	case DOWN: dir = LEFT;  break;
	case LEFT: dir = UP;  break;
	case UP: dir = RIGHT;  break;
	}
	kaart[y][x] = get_dir_char();
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

void lees_kaart(istream& is, matrix<char, N, M>& k) {
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

	lees_kaart(input, kaart);
	kaart[0][2 * K] = dir_char;
	string line;
	getline(input, line);
	getline(input, line);

	for (int i = 0; i < K; i++)
		for (int j = 0; j < K; j++)
			faces[1][i][j] = kaart[i][j + K];
	for (int i = 0; i < K; i++)
		for (int j = 0; j < K; j++)
			faces[2][i][j] = kaart[i][j + 2* K];
	for (int i = 0; i < K; i++)
		for (int j = 0; j < K; j++)
			faces[3][i][j] = kaart[i + K ][j + K];
	for (int i = 0; i < K; i++)
		for (int j = 0; j < K; j++)
			faces[4][i][j] = kaart[i + 2 * K][j];
	for (int i = 0; i < K; i++)
		for (int j = 0; j < K; j++)
			faces[5][i][j] = kaart[i + 2* K][j + K];
	for (int i = 0; i < K; i++)
		for (int j = 0; j < K; j++)
			faces[6][i][j] = kaart[i + 3* K ][j ];

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

	for (int i = 0; i < K; i++)
		for (int j = 0; j < K; j++)
			kaart[i][j + K] = faces[1][i][j];
	for (int i = 0; i < K; i++)
		for (int j = 0; j < K; j++)
			kaart[i][j + 2 * K] = faces[2][i][j];
	for (int i = 0; i < K; i++)
		for (int j = 0; j < K; j++)
			kaart[i + K][j + K] = faces[3][i][j];
	for (int i = 0; i < K; i++)
		for (int j = 0; j < K; j++)
			kaart[i + 2 * K][j] = faces[4][i][j];
	for (int i = 0; i < K; i++)
		for (int j = 0; j < K; j++)
			kaart[i + 2 * K][j + K] = faces[5][i][j];
	for (int i = 0; i < K; i++)
		for (int j = 0; j < K; j++)
			kaart[i + 3 * K][j] = faces[6][i][j];

	switch (f) {
	case 1: x = x + K; break;
	case 2: x = x + 2 * K; break;
	case 3: x = x + K; y = y + K; break;
	case 4: y = y +2 * K;
	case 5: x = x + K; y = y + 2 * K;
	case 6: y = y + 3 * K;
	}

	cout << "row: " << y + 1 << endl;
	cout << "col: " << x + 1 << endl;
	cout << "dir: " << dir << endl;
	cout << "password: " << 1000 * (y + 1) + 4 * (x + 1) + dir << endl;
}

