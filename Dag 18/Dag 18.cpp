#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <tuple>
#include <set>

using namespace std;

const int K = 19;
const int L = 19;
const int M = 19;

class cube{
public:
	int x, y, z;
	bool is_lava;
	int nr_of_free_sides = 6;
	bool is_trapped = true;
	bool is_marked = false;

	cube(int x, int y, int z, bool l = true) : x(x), y(y), z(z), is_lava(l) {}
	
	set<cube*> neighbours;

	//mark cubus on the edge and their neigbours.
	//leaving de unmarked empty cubed as trapped = true;
	void mark_trapped() {
		if (is_marked || is_lava) return;
		set<cube*> unmarked;
		unmarked.insert(this);
		while (!unmarked.empty()) {
			auto it = unmarked.begin();
			cube* c = *it;
			c->is_marked = true;
			c->is_trapped = false;
			unmarked.erase(it);
			for (cube* d : c->neighbours)
				if(!d->is_marked) unmarked.insert(d);
		}
	}	
};

bool compareXYZ(const cube* rhs, const cube* lhs) {
	if (rhs->x < lhs->x)
		return true;
	else if (rhs->x == lhs->x && rhs->y < lhs->y)
		return true;
	else
		if (rhs->x == lhs->x && rhs->y == lhs->y && rhs->z < lhs->z)
			return true;
	return false;

}

bool compareYZX(const cube* rhs, const cube* lhs) {
	if (rhs->y < lhs->y)
		return true;
	else if (rhs->y == lhs->y && rhs->z < lhs->z)
		return true;
	else
		if (rhs->y == lhs->y && rhs->z == lhs->z && rhs->x < lhs->x)
			return true;
	return false;
}

bool compareZXY(const cube* rhs, const cube* lhs) {
	if (rhs->z < lhs->z)
		return true;
	else if (rhs->z == lhs->z && rhs->x < lhs->x)
		return true;
	else
		if (rhs->z == lhs->z && rhs->x == lhs->x && rhs->y < lhs->y)
			return true;
	return false;
}

int main()
{
	ifstream input("C:\\Users\\Jan\\Desktop\\input.txt");
	if (!input) {
		cout << "file not found" << endl;
		return 1;
	}

	vector<cube*> lave_cubes;

	string line;
	while (getline(input, line)) {
		stringstream ss(line);
		int x, y, z;
		char komma;
		ss >> x >> komma >> y >> komma >> z;
		lave_cubes.push_back(new cube(x, y, z));
	}
	cout << "nr cubes: " << lave_cubes.size() << endl;

	//determine nr of connected & unconnected sides
	sort(lave_cubes.begin(), lave_cubes.end(), compareXYZ);
	for (int i = 1; i < lave_cubes.size(); i++)
		if (lave_cubes[i]->x == lave_cubes[i - 1]->x &&
			lave_cubes[i]->y == lave_cubes[i - 1]->y &&
			lave_cubes[i]->z - lave_cubes[i - 1]->z == 1) {
			lave_cubes[i]->nr_of_free_sides--;
			lave_cubes[i - 1]->nr_of_free_sides--;
		}

	sort(lave_cubes.begin(), lave_cubes.end(), compareYZX);
	for (int i = 1; i < lave_cubes.size(); i++)
		if (lave_cubes[i]->y == lave_cubes[i - 1]->y &&
			lave_cubes[i]->z == lave_cubes[i - 1]->z &&
			lave_cubes[i]->x - lave_cubes[i - 1]->x == 1) {
			lave_cubes[i]->nr_of_free_sides--;
			lave_cubes[i - 1]->nr_of_free_sides--;
		}

	sort(lave_cubes.begin(), lave_cubes.end(), compareZXY);
	for (int i = 1; i < lave_cubes.size(); i++)
		if (lave_cubes[i]->z == lave_cubes[i - 1]->z &&
			lave_cubes[i]->x == lave_cubes[i - 1]->x &&
			lave_cubes[i]->y - lave_cubes[i - 1]->y == 1) {
			lave_cubes[i]->nr_of_free_sides--;
			lave_cubes[i - 1]->nr_of_free_sides--;
		}
	
	int sum = 0;
	for (cube* c : lave_cubes)
		sum += c->nr_of_free_sides;
	cout << "nr faces not joining (answer part one): " << sum << endl << endl;

	//empty space between the lava
	vector<cube*> empty_cubes;
	for (int i = 0; i <= K; i++)
		for (int j = 0; j <= L; j++)
			for (int k = 0; k <= M; k++) {
				bool found = false;
				for (cube* c : lave_cubes) {
					if (c->x == i && c->y == j && c->z == k) {
						found = true;
						break;
					}
				}
				if(!found) empty_cubes.push_back(new cube(i, j, k, false));
			}
	cout << "nr empty cubes: " << empty_cubes.size() << endl;

	//find neigbours
	sort(empty_cubes.begin(), empty_cubes.end(), compareXYZ);
	for (int i = 1; i < empty_cubes.size(); i++)
		if (empty_cubes[i]->x == empty_cubes[i - 1]->x &&
			empty_cubes[i]->y == empty_cubes[i - 1]->y &&
			empty_cubes[i]->z - empty_cubes[i - 1]->z == 1) {
			empty_cubes[i]->neighbours.insert(empty_cubes[i - 1]);
			empty_cubes[i - 1]->neighbours.insert(empty_cubes[i]);
		}
					
	sort(empty_cubes.begin(), empty_cubes.end(), compareYZX);
	for (int i = 1; i < empty_cubes.size(); i++)
		if (empty_cubes[i]->y == empty_cubes[i - 1]->y &&
			empty_cubes[i]->z == empty_cubes[i - 1]->z &&
			empty_cubes[i]->x - empty_cubes[i - 1]->x == 1) {
			empty_cubes[i]->neighbours.insert(empty_cubes[i - 1]);
			empty_cubes[i - 1]->neighbours.insert(empty_cubes[i]);
		}

	sort(empty_cubes.begin(), empty_cubes.end(), compareZXY);
	for (int i = 1; i < empty_cubes.size(); i++)
		if (empty_cubes[i]->z == empty_cubes[i - 1]->z &&
			empty_cubes[i]->x == empty_cubes[i - 1]->x &&
			empty_cubes[i]->y - empty_cubes[i - 1]->y == 1) {
			empty_cubes[i]->neighbours.insert(empty_cubes[i - 1]);
			empty_cubes[i - 1]->neighbours.insert(empty_cubes[i]);
		}

	//mark cubus on the edge and their neigbours. (flood fill)
	for (cube* c : empty_cubes)
		if (c->x == 0 || c->x == K || c->y == 0 || c->y == L || c->z == 0 || c->z == M)
			if(!c->is_lava && !c->is_marked) c->mark_trapped();
	
	//We keep only unmarked non-lava cubes that are trapped in a bubble.
	vector<cube*> bubble_cubes;
	for (cube* c : empty_cubes) {
		if (c->is_trapped) bubble_cubes.push_back(c);
	}
	cout << "nr empty cubes in bubble: " << bubble_cubes.size() << endl << endl;

	//the sides of the cubes in the bubble that have no neighbour in the bubble
	//are connected to an lava_cube.
	int sum2 = 0;
	for (cube* c : bubble_cubes)
		sum2 += (6 - c->neighbours.size());
	cout << "nr of sides of the bubble cubes that are on the outside of the bubble: " << sum2 << endl;
	cout << "answer part two: " << sum - sum2 << endl;

}


