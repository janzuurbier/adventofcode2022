// Dag 8.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "../../adventofcode2021/matrix/matrix.h"
#include <fstream>

using namespace std;

const int N = 99;

int scenicval(matrix<char, N, N>& m, int row, int col) {
	int val1 = 0;
	int i = row + 1;
	while (m.isInRange(i, col)) {
		val1++;
		if (m[i][col] >= m[row][col]) break;
		i++;
	}
	int val2 = 0;
	i = row - 1;
	while (m.isInRange(i, col) ) {
		val2++;
		if (m[i][col] >= m[row][col]) break;
		i--;
	}
	int val3 = 0;
	i = col + 1;
	while (m.isInRange(row, i)) {
		val3++;
		if (m[row][i] >= m[row][col]) break;
		i++;
	}
	int val4 = 0;
	i = col - 1;
	while (m.isInRange(row, i) ) {
		val4++;
		if (m[row][i] >= m[row][col]) break;
		i--;
	}
	return val1 * val2 * val3 * val4;
}

int main()
{
	ifstream input("C:\\Users\\Jan\\Desktop\\input.txt");
	if (!input) {
		cout << "file not found" << endl;
		return 1;
	}

	matrix<char, N, N> heigth(0);
	matrix<bool, N, N> visible(false);

	input >> heigth;


	for (int i = 0; i < N ; i++) {
		int max = -1;
		for (int j = 0; j < N ; j++) {
			if (heigth[i][j] > max) {
				max = heigth[i][j];
				visible[i][j] = true;
				if (max == '9') break;
			}
		}
	}
	for (int j = 0; j < N ; j++) {
		int max = -1;
		for (int i = 0; i < N; i++) {
			if (heigth[i][j] > max) {
				max = heigth[i][j];
				visible[i][j] = true;
				if (max == '9') break;
			}
		}
	}
	for (int i = 0; i < N ; i++) {
		int max = -1;
		for (int j = N - 1; j >= 0 ; j--) {
			if (heigth[i][j] > max) {
				max = heigth[i][j];
				visible[i][j] = true;
				if (max == '9') break;
			}
		}
	}
	for (int j = 0; j < N ; j++) {
		int max = -1;
		for (int i = N - 1; i >= 0 ; i--) {
			if (heigth[i][j] > max) {
				max = heigth[i][j];
				visible[i][j] = true;
				if (max == '9') break;
			}
		}
	}

	int count = 0;
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			if (visible[i][j])count++;
	cout << endl << count << endl;

	int maxsv = 0;
	for(int i = 0; i < N; i++)
		for (int j = 0; j < N; j++) {
			int sv = scenicval(heigth, i, j);
			//cout << i << " " << j << " " << heigth[i][j] << " " << sv << endl;
			if (sv > maxsv)
				maxsv = sv;
		}
	cout << endl << maxsv << endl;
}
