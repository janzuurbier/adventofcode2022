#include <iostream>
#include <string>
#include <fstream>
#include <deque>
#include <set>
#include <map>
#include "../matrix/matrix.h"

using namespace std;

deque<char> directions{ 'N', 'S', 'W', 'E' };
void rotate_directions() {
	directions.push_back(directions.front());
	directions.pop_front();
}

set<pair<int, int>> positions;
map<pair<int, int>, int> proposed_positons;

class elf {
public:
	int x;
	int y;
	int proposed_x;
	int proposed_y;
	bool hasmoved;

	elf(int x, int y) : x(x), y(y) {}

	void propose() {
		proposed_x = x;
		proposed_y = y;
		if (positions.count(pair<int, int>(x - 1, y - 1)) == 0 &&
			positions.count(pair<int, int>(x, y - 1)) == 0 &&
			positions.count(pair<int, int>(x + 1, y - 1)) == 0 &&
			positions.count(pair<int, int>(x - 1, y + 1)) == 0 &&
			positions.count(pair<int, int>(x, y + 1)) == 0 &&
			positions.count(pair<int, int>(x + 1, y + 1)) == 0 &&
			positions.count(pair<int, int>(x - 1, y)) == 0 &&
			positions.count(pair<int, int>(x + 1, y)) == 0
			)
			return;

		for (char ch : directions) {
			if (ch == 'N' &&
				positions.count(pair<int, int>(x - 1, y - 1)) == 0 &&
				positions.count(pair<int, int>(x, y - 1)) == 0 &&
				positions.count(pair<int, int>(x + 1, y - 1)) == 0 
				) {
				proposed_x = x;
				proposed_y = y - 1;
				break;
			}
			else if (ch == 'S' &&
				positions.count(pair<int, int>(x - 1, y + 1)) == 0 &&
				positions.count(pair<int, int>(x, y + 1)) == 0 &&
				positions.count(pair<int, int>(x + 1, y + 1)) == 0 
				) {
				proposed_x = x;
				proposed_y = y + 1;
				break;
			}
			else if (ch == 'W' &&
				positions.count(pair<int, int>(x - 1, y - 1)) == 0 &&
				positions.count(pair<int, int>(x - 1, y )) == 0 &&
				positions.count(pair<int, int>(x - 1, y + 1)) == 0
				) {
				proposed_x = x - 1;
				proposed_y = y;
				break;
			}
			else if (ch == 'E' &&
				positions.count(pair<int, int>(x + 1, y - 1)) == 0 &&
				positions.count(pair<int, int>(x + 1, y)) == 0 &&
				positions.count(pair<int, int>(x + 1, y + 1)) == 0
				) {
				proposed_x = x + 1;
				proposed_y = y;
				break;
			}
		}
		if (proposed_positons.count(pair<int, int>(proposed_x, proposed_y)) > 0)
			proposed_positons[pair<int, int>(proposed_x, proposed_y)]++;
		else
			proposed_positons[pair<int, int>(proposed_x, proposed_y)] = 1;
	}

	void move() {
		hasmoved = false;
		if (proposed_positons[pair<int, int>(proposed_x, proposed_y)] == 1) {
			if (x != proposed_x || y != proposed_y)
				hasmoved = true;
			x = proposed_x;
			y = proposed_y;
		}
	}
};

vector<elf> all_elfs;

void show_elfs() {
	matrix<char, 11, 14> m('.');
	for (elf e : all_elfs)
		if(m.isInRange(e.x, e.y)) m[e.y][e.x] = '#';
	cout << m << endl;
}


int main() {
	ifstream input("C:\\Users\\Jan\\Desktop\\input.txt");
	if (!input) {
		cout << "file not found" << endl;
		return 1;
	}

	string line;
	int i = 0;
	while (getline(input, line)) {
		for (int j = 0; j < line.size(); j++)
			if (line[j] == '#')
				all_elfs.push_back(elf(j, i));
		i++;
	}
	//show_elfs();

	for (int round = 1;/*round <= 10*/ ; round++) {
		positions.clear();
		proposed_positons.clear();
		for (const elf& e : all_elfs)
			positions.insert(pair<int, int>(e.x, e.y));
		for (elf& e : all_elfs)
			e.propose();
		for (elf& e : all_elfs)
			e.move();
		rotate_directions();
		cout << "after round " << round  << endl;
		//show_elfs();
		bool hasmoved = false;
		for (elf e : all_elfs)
			if (e.hasmoved) hasmoved = true;
		if (!hasmoved) {
			cout << " no moves after round " << round << endl;
			break;
		}
	}

	int min_x = INT_MAX;
	int min_y = INT_MAX;
	int max_x = INT_MIN;
	int max_y = INT_MIN;
	for (elf e : all_elfs) {
		if (e.x < min_x)
			min_x = e.x;
		if (e.x > max_x)
			max_x = e.x;
		if (e.y < min_y)
			min_y = e.y;
		if (e.y > max_y)
			max_y = e.y;
	}

	//cout << (max_x - min_x + 1)*(max_y - min_y + 1) - all_elfs.size() << endl;
	cout << min_x << ", " << max_x << endl;
	cout << min_y << ", " << max_y << endl;


}