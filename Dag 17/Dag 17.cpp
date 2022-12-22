
#include <iostream>
#include <vector>
#include <fstream>
#include "../../adventofcode2021/matrix/matrix.h"

using namespace std;
const int N = 100000;
uint64_t onder_grens = 0;


uint64_t max_hoogtes[7]{ 0,0,0,0,0,0,0 };
matrix<char, N, 7> hoogtes('.');

class Rock {
protected:
	vector<pair<int, uint64_t>> blokjes;
	uint64_t hoogte;

	void initialize() {
		for (auto& b : blokjes) {
			b.second += (hoogte + 4);
		}
	}

public:

	Rock(uint64_t h) : hoogte(h) {}

	bool kan_naar_rechts() {
		for (const auto& b : blokjes) {
			if (b.first == 6)
				return false;
			if (hoogtes[b.second - onder_grens][b.first + 1] == '#')
				return false;
		}
		return true;
	}

	bool kan_naar_links() {
		for (const auto& b : blokjes) {
			if (b.first == 0)
				return false;
			if (hoogtes[b.second - onder_grens][b.first - 1] == '#')
				return false;
		}
		return true;
	}

	bool kan_omlaag() {
		for (const auto& b : blokjes) {
			if (b.second == 1)
				return false;
			if (hoogtes[(b.second - onder_grens - 1)][b.first] == '#')
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
			hoogtes[b.second - onder_grens][b.first] = '#';
		for (int i = 0; i < 7; i++)
			for (const auto& b : blokjes)
				if (i == b.first && b.second  > max_hoogtes[i]) {
					max_hoogtes[i] = b.second  ;
					break;
				}
	}
};

class PlusRock : public Rock {
public:
	PlusRock(uint64_t h): Rock(h) {
		blokjes.push_back(pair<int, uint64_t>(2, 1));
		blokjes.push_back(pair<int, uint64_t>(3, 2));
		blokjes.push_back(pair<int, uint64_t>(3, 1));
		blokjes.push_back(pair<int, uint64_t>(3, 0));				
		blokjes.push_back(pair<int, uint64_t>(4, 1));
		initialize();
	}	
};

class MinRock : public Rock {
public:
	MinRock(uint64_t h) : Rock(h) {
		blokjes.push_back(pair<int, uint64_t>(2, 0));
		blokjes.push_back(pair<int, uint64_t>(3, 0));
		blokjes.push_back(pair<int, uint64_t>(4, 0));
		blokjes.push_back(pair<int, uint64_t>(5, 0));
		initialize();
	}
};

class CornerRock : public Rock {
public:
	CornerRock(uint64_t h) : Rock(h) {
		blokjes.push_back(pair<int, uint64_t>(2, 0));
		blokjes.push_back(pair<int, uint64_t>(3, 0));
		blokjes.push_back(pair<int, uint64_t>(4, 2));
		blokjes.push_back(pair<int, uint64_t>(4, 1));
		blokjes.push_back(pair<int, uint64_t>(4, 0));
		initialize();
	}
};

class DashRock : public Rock {
public:
	DashRock(uint64_t h) : Rock(h) {
		blokjes.push_back(pair<int, uint64_t>(2, 3));
		blokjes.push_back(pair<int, uint64_t>(2, 2));
		blokjes.push_back(pair<int, uint64_t>(2, 1));
		blokjes.push_back(pair<int, uint64_t>(2, 0));
		initialize();
	}
};

class BlockRock : public Rock {
public:
	BlockRock(uint64_t h) : Rock(h) {
		blokjes.push_back(pair<int, uint64_t>(2, 1));
		blokjes.push_back(pair<int, uint64_t>(2, 0));
		blokjes.push_back(pair<int, uint64_t>(3, 1));
		blokjes.push_back(pair<int, uint64_t>(3, 0));
		initialize();
	}
};


int main()
{
	ifstream input("C:\\Users\\Jan\\Desktop\\input.txt");
	if (!input) {
		cout << "file not found" << endl;
		return 1;
	}

	for (uint64_t i = 0; i < 1000000000000L; i++) {
		uint64_t max_hoogte = 0;
		for (uint64_t h : max_hoogtes)
			if (h > max_hoogte) max_hoogte = h;
		Rock *r = nullptr;
		switch (i % 5) {
		case 0: r = new MinRock(max_hoogte); break;
		case 1: r = new PlusRock(max_hoogte); break;
		case 2: r = new CornerRock(max_hoogte); break;
		case 3: r = new DashRock(max_hoogte); break;
		case 4: r = new BlockRock(max_hoogte); break;
		}
		while (true) {
			char ch = '?';
			input.get(ch);
			if (!input) {
				input.clear();
				input.seekg(0);
				input.get(ch);
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
		uint64_t min_hoogte = UINT64_MAX;
		for (uint64_t h : max_hoogtes)
			if (h < min_hoogte) min_hoogte = h;
		if (min_hoogte > onder_grens + N/2) {
			int shift = N / 2;
			for (int i = shift; i < N; i++)
				for (int j = 0; j < 7; j++) {
					hoogtes[i - shift][j] = hoogtes[i][j];
					hoogtes[i][j] = '.';
				}
			onder_grens += shift;
			cout << onder_grens << endl;
		}
		int64_t gelijk = max_hoogtes[0];


		delete r;
	}
	uint64_t max_hoogte = 0;
	for (uint64_t h : max_hoogtes)
		if (h > max_hoogte) max_hoogte = h;
	cout << max_hoogte << endl;
}

