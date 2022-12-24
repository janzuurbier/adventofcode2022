#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include "../matrix/matrix.h"

//const int N = 6;
//const int M = 8;
const int N = 37;
const int M = 102;

using namespace std;

matrix<string, N, M> valley ("");
matrix<int, N, M> dist(-1);

void show_valley() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (valley[i][j].size() > 1)
				cout << valley[i][j].size();
			else
				cout << valley[i][j];
		}
		cout << endl;
	}
	cout << endl;
}

void move_blizzard() {
	matrix<string, N, M>m("");
	for(int i = 0; i < N; i++)
		for (int j = 0; j < M; j++) {
			if (valley[i][j].find('>') != string::npos) {
				if(valley[i][j + 1] == "#")
					m[i][1] += '>';
				else
					m[i][j + 1] += '>';
			}
			if (valley[i][j].find('<') != string::npos) {
				if (valley[i][j - 1] == "#")
					m[i][M - 2] += '<';
				else
					m[i ][j - 1] += '<';
			}
			if (valley[i][j].find('v') != string::npos) {
				if (valley[i + 1][j] == "#")
					m[1][j] += 'v';
				else
					m[i + 1][j] += 'v';
			}
			if (valley[i][j].find('^') != string::npos) {
				if (valley[i - 1][j] == "#")
					m[N - 2][j] += '^';
				else
					m[i - 1][j] += '^';
			}
			if (valley[i][j] == "#")
				m[i][j] = "#";
		}
	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++)
			if (m[i][j].size() == 0)
				valley[i][j] = ".";
			else
				valley[i][j] = m[i][j];
}

void mark_dist(int minute) {
	matrix<int, N, M> old_dist = dist;
	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++) {
			if (old_dist[i][j] == minute) {
				if (valley[i][j] == ".") dist[i][j] = minute + 1;
				if (valley.isInRange(i + 1, j) && valley[i + 1][j] == ".") dist[i + 1][j] = minute + 1;
				if (valley.isInRange(i - 1, j) && valley[i - 1][j] == ".") dist[i - 1][j] = minute + 1;
				if (valley.isInRange(i, j + 1) && valley[i][j + 1] == ".") dist[i][j + 1] = minute + 1;
				if (valley.isInRange(i, j - 1) && valley[i][j - 1] == ".") dist[i][j - 1] = minute + 1;
			}
		}
}

int main(){
	ifstream input("C:\\Users\\Jan\\Desktop\\input.txt");
	if (!input) {
		cout << "file not found" << endl;
		return 1;
	}

	matrix<char, N, M> m('.');
	input >> m;
	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++)
			valley[i][j] += m[i][j];
	dist[0][1] = 0;
	bool gevonden = false;

	int minute = 0;
	for (;  !gevonden; minute++) {
		move_blizzard();
		mark_dist(minute);
		if (dist[N - 1][M - 2] > 0) gevonden = true;
	}
	cout << "after " << minute << " minutes we reached the goal." << endl;
	dist = matrix<int, N, M>(0);
	dist[N - 1][M - 2] = minute;
	gevonden = false;
	for (; !gevonden; minute++) {
		move_blizzard();
		mark_dist(minute);
		if (dist[0][1] > 0) gevonden = true;
	}
	cout << "after " << minute << " minutes I reached the start." << endl;
	dist = matrix<int, N, M>(0);
	dist[0][1] = minute;
	gevonden = false;
	for (; !gevonden; minute++) {
		move_blizzard();
		mark_dist(minute);
		if (dist[N - 1][M - 2] > 0) gevonden = true;
	}
	cout << "after " << minute << " minutes I reached the goal again." << endl;
}




