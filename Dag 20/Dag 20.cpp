
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <map>
#include <set>


using namespace std;

struct combi {
	int64_t val;
	int original_pos;

	combi(int64_t v, int p) : val(v), original_pos(p) {};
};

void swap(int64_t& i, int64_t& j) {
	int64_t temp = i;
	i = j;
	j = temp;
}

void move(vector<combi>& v, int pos1, int pos2) {
	if (pos2 > pos1) {
		for (int i = pos1; i < pos2; i++)
			swap(v[i], v[i + 1]);
	}
	else {
		for (int i = pos1; i > pos2; i--)
			swap(v[i], v[i - 1]);
	}
}

int find(const vector<combi>& v, int64_t val, int pos = 0) {
	int n = v.size();
	while (v[pos].val != val)
		pos = (pos + 1) % n;
	return pos;
}

void  mix(vector<combi>& avector, const vector<int64_t>& originalvector) {
	int n = avector.size();
	int pos = 0;
	for (int i = 0; i < n; i++) {
		int64_t steps = originalvector[i];
		while (avector[pos].original_pos != i)
			pos = find(avector, steps, (pos + 1) % n);
		int nextpos = (pos + steps) % (n - 1);
		if (nextpos < 0) nextpos = n - 1 + nextpos;
		move(avector, pos, nextpos);
	}
}


int main() {
	ifstream input("C:\\Users\\Jan\\Desktop\\input.txt");
	if (!input) {
		cout << "file not found" << endl;
		return 1;
	}

	vector<int64_t> originalnumbers;

	string line;
	while (getline(input, line)) {
		int64_t i = stoi(line);
		originalnumbers.push_back(i);
	}


	vector<combi> combies_part_one;
	for (int i = 0; i <  originalnumbers.size(); i++)
		combies_part_one.push_back(combi(originalnumbers[i], i));
	
	mix(combies_part_one, originalnumbers);

	int pos = find(combies_part_one, 0, 0);
	int pos1 = (pos + 1000) % combies_part_one.size();
	int pos2 = (pos + 2000) % combies_part_one.size();
	int pos3 = (pos + 3000) % combies_part_one.size();

	cout << "answer part one: ";
	cout << combies_part_one[pos1].val + combies_part_one[pos2].val + combies_part_one[pos3].val << endl;
	


	for (int i = 0; i < originalnumbers.size(); i++)
		originalnumbers[i] *= 811589153;


	vector<combi> combies_to_mix;
	for (int i = 0; i < originalnumbers.size(); i++)
		combies_to_mix.push_back(combi(originalnumbers[i], i));
	for (int i = 0; i < 10; i++) {
		cout << i << endl;
		mix(combies_to_mix, originalnumbers);
	}

	pos = find(combies_to_mix, 0);
	pos1 = (pos + 1000) % combies_part_one.size();
	pos2 = (pos + 2000) % combies_part_one.size();
	pos3 = (pos + 3000) % combies_part_one.size();

	cout << "answer part two: ";
	cout << combies_to_mix[pos1].val + combies_to_mix[pos2].val + combies_to_mix[pos3].val << endl;
}
