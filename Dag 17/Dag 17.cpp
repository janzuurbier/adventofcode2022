#include <iostream>
#include <vector>
#include <fstream>
#include "../matrix/matrix.h"

using namespace std;
const int N = 10000;
const int M = 2022;

int64_t max_hoogtes[7]{ 0,0,0,0,0,0,0 };
int64_t max_hoogte = 0;
matrix<char, N, 7> tetris('.');

class Rock {
protected:
	vector<pair<int, int64_t>> blokjes;
	int64_t hoogte;

	void initialize() {
		for (auto& b : blokjes) {
			b.second += (hoogte + 4);
		}
	}

public:

	Rock(int64_t h) : hoogte(h) {}

	bool kan_naar_rechts() {
		for (const auto& b : blokjes) {
			if (b.first == 6)
				return false;
			if (tetris[b.second ][b.first + 1] == '#')
				return false;
		}
		return true;
	}

	bool kan_naar_links() {
		for (const auto& b : blokjes) {
			if (b.first == 0)
				return false;
			if (tetris[b.second ][b.first - 1] == '#')
				return false;
		}
		return true;
	}

	bool kan_omlaag() {
		for (const auto& b : blokjes) {
			if (b.second == 1)
				return false;
			if (tetris[(b.second  - 1)][b.first] == '#')
				return false;
		}
		return true;
	}

	void naar_rechts() {
		for (auto& b : blokjes) {
			b.first++;
		}
	}

	void naar_links() {
		for (auto& b : blokjes) {
			b.first--;
		}
	}

	void omlaag() {
		for (auto& b : blokjes) {
			b.second --;
		}
	}

	void pas_hoogtes_aan() {
		for (const auto& b : blokjes)
			tetris[b.second ][b.first] = '#';
		for (int i = 0; i < 7; i++)
			for (const auto& b : blokjes)
				if (i == b.first && b.second  > max_hoogtes[i]) {
					max_hoogtes[i] = b.second  ;
					break;
				}
		for (int64_t h : max_hoogtes)
			if (h > max_hoogte) max_hoogte = h;
	}
};

class PlusRock : public Rock {
public:
	PlusRock(int64_t h): Rock(h) {
		blokjes.push_back(pair<int, int64_t>(2, 1));
		blokjes.push_back(pair<int, int64_t>(3, 2));
		blokjes.push_back(pair<int, int64_t>(3, 1));
		blokjes.push_back(pair<int, int64_t>(3, 0));				
		blokjes.push_back(pair<int, int64_t>(4, 1));
		initialize();
	}	
};

class MinRock : public Rock {
public:
	MinRock(int64_t h) : Rock(h) {
		blokjes.push_back(pair<int, int64_t>(2, 0));
		blokjes.push_back(pair<int, int64_t>(3, 0));
		blokjes.push_back(pair<int, int64_t>(4, 0));
		blokjes.push_back(pair<int, int64_t>(5, 0));
		initialize();
	}
};

class CornerRock : public Rock {
public:
	CornerRock(int64_t h) : Rock(h) {
		blokjes.push_back(pair<int, int64_t>(2, 0));
		blokjes.push_back(pair<int, int64_t>(3, 0));
		blokjes.push_back(pair<int, int64_t>(4, 2));
		blokjes.push_back(pair<int, int64_t>(4, 1));
		blokjes.push_back(pair<int, int64_t>(4, 0));
		initialize();
	}
};

class DashRock : public Rock {
public:
	DashRock(int64_t h) : Rock(h) {
		blokjes.push_back(pair<int, int64_t>(2, 3));
		blokjes.push_back(pair<int, int64_t>(2, 2));
		blokjes.push_back(pair<int, int64_t>(2, 1));
		blokjes.push_back(pair<int, int64_t>(2, 0));
		initialize();
	}
};

class BlockRock : public Rock {
public:
	BlockRock(int64_t h) : Rock(h) {
		blokjes.push_back(pair<int, int64_t>(2, 1));
		blokjes.push_back(pair<int, int64_t>(2, 0));
		blokjes.push_back(pair<int, int64_t>(3, 1));
		blokjes.push_back(pair<int, int64_t>(3, 0));
		initialize();
	}
};

int main(){
	ifstream input("C:\\Users\\Jan\\Desktop\\input.txt");
	if (!input) {
		cout << "file not found" << endl;
		return 1;
	}

	for (int64_t i = 0; i < M; i++) {
		Rock *r = nullptr;
		switch (i % 5) {
		case 0: r = new MinRock(max_hoogte); break;
		case 1: r = new PlusRock(max_hoogte); break;
		case 2: r = new CornerRock(max_hoogte); break;
		case 3: r = new DashRock(max_hoogte); break;
		case 4: r = new BlockRock(max_hoogte); break;
		}
		bool b = false;
		while (true) {
			char ch;
			input.get(ch);
			if (!input) {
				input.clear();
				input.seekg(0);
				input.get(ch);
				b = true;
			}
			if (ch == '>' && r->kan_naar_rechts())
				r->naar_rechts();
			if (ch == '<' && r->kan_naar_links())
				r->naar_links();
			if (r->kan_omlaag())
				r->omlaag();
			else
				break;
		}
		r->pas_hoogtes_aan();
		delete r;
		//find repetion for part two
		if (b) {
			cout << i << ":\t";
			for (int64_t h : max_hoogtes)
				cout << h - max_hoogtes[0] << ", ";
			cout << '\t' << max_hoogte << endl;
		}
	}
	cout << max_hoogte << endl;	
}

