//
//de following transformation is used:
//u = x + y
//v = x - y
//reverse transformation: 
//x = (u+v)/2
//y = (u-v)/2

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <set>

using namespace std;

const int N = 4000000;
//const int N = 20;

class manhattan_circle {
	int x_center;
	int y_center;
	int radius;

public:
	manhattan_circle(int x, int y, int r) : x_center(x), y_center(y), radius(r) {
	}

	bool contains(int x, int y) {
		return abs(x_center - x) + abs(y_center - y) <= radius;
	}

	int getMaxU() {
		return x_center + y_center + radius;
	}

	int getMinU() {
		return x_center + y_center - radius;
	}

	int getMaxV() {
		return x_center - y_center + radius;
	}

	int getMinV() {
		return x_center - y_center - radius;
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

	set<int> points_u;
	set<int> points_v;
	vector<manhattan_circle> mcs;

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
		mcs.push_back(mc);
		points_u.insert(mc.getMaxU());
		points_u.insert(mc.getMinU());
		points_v.insert(mc.getMaxV());
		points_v.insert(mc.getMinV());
	}

	int prev_u = *points_u.begin();
	int prev_v = *points_v.begin();
	for (int u : points_u) {
		for (int v : points_v) {
			//we can try u, v - 1 or u - 1, v or u - 1, v - 1
			if ((u + v) % 2 == 0) {
				int x = (u + v - 2) / 2;
				int y = (u - v) / 2;
				bool b = false;
				for (manhattan_circle mc : mcs)
					if (mc.contains(x, y))
						b = true;
				//print x,y that is not in one of the circles
				if (!b) {
					if (0 <= x && x <= N && 0 <= y && y <= N) {
						cout << x << ", " << y << endl;
						cout << (uint64_t)x * 4000000 + (uint64_t)y << endl;
					}
				}			
			}
			else {
				int x = (u - 1 + v) / 2;
				int y = (u - 1 - v ) / 2;
				bool b = false;
				for (manhattan_circle mc : mcs)
					if (mc.contains(x, y))
						b = true;
				//print x,y that is not in one of the circles
				if (!b) {
					if (0 <= x && x <= N && 0 <= y && y <= N) {
						cout << x << ", " << y << endl;
						cout << (uint64_t)x * 4000000 + (uint64_t)y << endl;
					}
				}
				x = (u + v - 1) / 2;
				y = (u - v + 1) / 2;
				b = false;
				for (manhattan_circle mc : mcs)
					if (mc.contains(x, y))
						b = true;
				//print x,y that is not in one of the circles
				if (!b) {
					if (0 <= x && x <= N && 0 <= y && y <= N) {
						cout << x << ", " << y << endl;
						cout << (uint64_t)x * 4000000 + (uint64_t)y << endl;
					}
				}
			}
			prev_v = v;
		}
		prev_u = u;
	}
}

