#include <iostream>
#include <string>
#include <fstream>
#include <set>
#include "../../adventofcode2021/matrix/matrix.h"

using namespace std;
const int N = 41;
const int M = 95;
//const int N = 5;
//const int M = 8;
matrix<char, N, M> heightmap(' ');
matrix<int, N, M> distancemap( 2000  );
set<pair<int, int>> changed;

void mark_neighbours(int row, int col) {
	set<pair<int, int>> neighbours;
	neighbours.insert(pair<int, int>(row - 1, col));
	neighbours.insert(pair<int, int>(row + 1, col));
	neighbours.insert(pair<int, int>(row, col - 1));
	neighbours.insert(pair<int, int>(row , col + 1));
	
	for(auto nb: neighbours)
		if (
			distancemap.isInRange(nb.first, nb.second) && 
			heightmap[nb.first][nb.second] <= heightmap[row][col] + 1 &&
			distancemap[row][col] + 1 < distancemap[nb.first][nb.second]
			) 
			{
				distancemap[nb.first][nb.second] = distancemap[row][col] + 1;
				changed.insert(nb);
			}
}

int main()
{
	ifstream input("C:\\Users\\Jan\\Desktop\\input.txt");
	if (!input) {
		cout << "file not found" << endl;
		return 1;
	}
	input >> heightmap;

	int start_row = 0;
	int start_col = 0;
	int end_row = 0;
	int end_col = 0;
	for(int i= 0; i < N; i++)
		for (int j = 0; j < M; j++) {
			if (heightmap[i][j] == 'S') {
				heightmap[i][j] = 'a';
				start_row = i;
				start_col = j;
			}
			if (heightmap[i][j] == 'E') {
				heightmap[i][j] = 'z';
				end_row = i;
				end_col = j;
			}
		}

	//part one
	//distancemap[start_row][start_col] = 0;
	//changed.insert(pair<int, int>(start_row, start_col));

	for(int i = 0; i < N; i++)
		for (int j = 0; j < M; j++) {
			if (heightmap[i][j] == 'a') {
				distancemap[i][j] = 0;
				changed.insert(pair<int, int>(i, j));
			}
		}

	while (!changed.empty()) {
		set<pair<int, int>> old = changed;
		changed.clear();
		for (auto p : old) {
			mark_neighbours(p.first, p.second);
		}
	}

	cout << distancemap[end_row][end_col] << endl;
}