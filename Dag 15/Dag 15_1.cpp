// Dag 15_1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <set>

using namespace std;

//const int N = 2000000;
const int N = 10;

class line_t {

public:
	int x_start;
	int x_eind;

	line_t(int a, int b, bool c = false) : x_start(a), x_eind(b) {}

	bool isEmpty() {
		return x_eind < x_start;
	}

	bool contains(int x) {
		return x >= x_start && x <= x_eind;
	}
};

class manhattan_circle {
	int x_center;
	int y_center;
	int radius;

public:
	manhattan_circle(int x, int y, int r): x_center(x), y_center(y), radius(r) {}

	line_t line_at(int y) {
		int d = abs(y - y_center);
		return line_t(x_center - radius + d, x_center + radius - d);
	}

	bool contains(int x, int y) {
		return abs(x_center - x) + abs(y_center - y) <= radius;
	}
};

int abs(int x) {
	return x < 0 ? -x : x;
}

int main()
{
	ifstream input("C:\\Users\\Jan\\Desktop\\input.txt");
	if (!input) {
		cout << "file not found" << endl;
		return 1;
	}

	vector<line_t> lines;
	set<int> points;
	set<int> beacon_positions;

	string line;
	while (getline(input, line)) {
		size_t p = line.find('=');
		size_t q = line.find(',');
		int x1 = stol(line.substr(p + 1, q - p));
		size_t r = q + 1;
		p = line.find('=', r);
		q = line.find(':', r);
		int y1 = stoi(line.substr(p + 1, q - p));
		r = q + 1;
		p = line.find('=', r);
		q = line.find(',', r);
		int x2 = stoi(line.substr(p + 1, q - p));
		r = q + 1;
		p = line.find('=', r);
		int y2 = stoi(line.substr(p + 1));
		manhattan_circle mc(x1, y1, abs(y2 - y1) + abs(x2 - x1));
		line_t l = mc.line_at(N);
		if (!l.isEmpty()) {
			lines.push_back(l);
			points.insert(l.x_eind);
			points.insert(l.x_start);
		}
		if(y2 == N) beacon_positions.insert(y2);
	}

	int count = 0;
	int prev = *points.begin();
	for (int i : points) {
		bool b = false;
		for(line_t l: lines)
			if(l.contains(i-1))
				b = true;
		if(b) count += i - prev;
		prev = i;
	}
	cout << count - beacon_positions.size() + 1 << endl;
}

