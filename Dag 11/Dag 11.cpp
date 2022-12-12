// Dag 11.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <fstream>
#include <string>

using namespace std;



class Monkey;
vector<Monkey> monkeys;

class Monkey {
	enum type_t  { PLUS, MAAL,KWADRAAT };
	type_t monkey_type;
	int operatie_getal;
	vector<int64_t> items;
	int monkey_a;
	int monkey_b;
	

public:
	int inspection_count = 0;
	int64_t test_getal;

	int64_t operation(int64_t n) {
		switch (monkey_type) {
		case PLUS:
			return n + operatie_getal;
		case MAAL:
			return n * operatie_getal;
		case KWADRAAT:
			return n * n;
		default:
			return 0;
		}
	}

	int calc_next_monkey(int64_t item){
		if (item % test_getal == 0)
			return monkey_a;
		else
			return monkey_b;
	}

	void add(int64_t item) {
		items.push_back(item);
	}

	void play_round(int64_t modulus){
		for (auto it = items.begin(); it != items.end(); it = items.erase(it)) {
			inspection_count++;
			int64_t item = operation(*it);
			//item /= 3;
			item = item % modulus;
			int next_monkey = calc_next_monkey(item);
			monkeys[next_monkey].add(item);
		}
	}

	friend istream& operator>>(istream& in, Monkey& m) {
		string line;
		while (getline(in, line)) {
			if (line.substr(0, 6) == "Monkey")
				break;
		}
		string woord;
		int getal;
		char ch;
		m.items.clear();
		in >> woord >> woord;
		in >> getal;
		m.items.push_back(getal);
		in.get(ch);
		while (ch == ',') {
			in >> getal;
			m.items.push_back(getal);
			in.get(ch);
		}
		in >> woord >> woord >> woord >> woord;
		in >> ch;
		if (ch == '+') {
			in >> getal;
			m.operatie_getal = getal;
			m.monkey_type = PLUS;
		} 
		else if (ch == '*') {
			in >> woord;
			if (woord == "old") {
				m.monkey_type = KWADRAAT;
			}
			else {
				m.operatie_getal = stoi(woord);
				m.monkey_type = MAAL;
			}
		}
		in >> woord >> woord >> woord;
		in >> m.test_getal;
		in >> woord >> woord >> woord >> woord >> woord;
		in >> m.monkey_a;
		in >> woord >> woord >> woord >> woord >> woord;
		in >> m.monkey_b;
		return in;
	}
};


int main()
{
	ifstream input("C:\\Users\\Jan\\Desktop\\input.txt");
	if (!input) {
		cout << "file not found" << endl;
		return 1;
	}

	Monkey m;
	while (input >> m) {
		monkeys.push_back(m);
	}

	int64_t modulus = 1;
	for (Monkey m : monkeys)
		modulus *= m.test_getal;

	int i = 0;
	for ( ; i < 1000; i++) {		
		for (Monkey& m : monkeys)
			m.play_round(modulus);
	}

	cout << "\t==After round " << i << "==" << endl;
	for (int i = 0; i < monkeys.size(); i++) {
		cout << "Monkey " << i << " inspected items ";
		cout << monkeys[i].inspection_count << " times." << endl;
	}

}
