#include <iostream>
#include <string>
#include <fstream>
#include <set>
#include <vector>
#include <stdexcept>
#include <sstream>

using namespace std;

enum operation_t { PLUS, MIN, MAAL, DELING };

struct monkey {
	string naam;
	int64_t number1 = 0;
	int64_t number2 = 0;
	string monkey1 = "????";
	string monkey2 = "????";
	int64_t number = 0;
	bool knows_number = false;
	bool knows_number1 = false;
	bool knows_number2 = false;
	operation_t operation;

	bool operator<(const monkey& rhs) const {
		return naam < rhs.naam;
	}
};
vector<monkey> all_monkeys;
monkey root;

int main() {
	ifstream input("C:\\Users\\Jan\\Desktop\\input.txt");
	if (!input) {
		cout << "file not found" << endl;
		return 1;
	}

	string line;
	while (getline(input, line)) {
		monkey m;
		size_t pos = line.find(':');
		m.naam = line.substr(0, pos);
		line = line.substr(pos + 1);
		try {
			m.number = stoll(line);
			m.knows_number = true;
		}
		catch (const invalid_argument& ia) {
			stringstream ss(line);
			char ch;
			ss >> m.monkey1 >> ch >> m.monkey2;
			switch (ch) {
			case '+': m.operation = PLUS; break;
			case '-': m.operation = MIN; break;
			case '*': m.operation = MAAL; break;
			case '/': m.operation = DELING; break;
			}
		}
		all_monkeys.push_back(m);
	}

	vector<monkey> monkeys = all_monkeys;
	while (monkeys.size() > 1) {
		vector<monkey> temp;
		for (monkey& m : monkeys) {
			if (!m.knows_number) temp.push_back(m);
		}
		for (const monkey& n : monkeys) {
			if (n.knows_number) {
				string naam = n.naam;
				int64_t number = n.number;
				for (monkey& m : temp) {
					if (!m.knows_number1 && m.monkey1 == naam) {
						m.number1 = number;
						m.knows_number1 = true;
					}
					if (!m.knows_number2 && m.monkey2 == naam) {
						m.number2 = number;
						m.knows_number2 = true;
					}
					if (m.knows_number1 && m.knows_number2) {
						switch (m.operation) {
						case PLUS: m.number = m.number1 + m.number2; break;
						case MIN: m.number = m.number1 - m.number2; break;
						case MAAL: m.number = m.number1 * m.number2; break;
						case DELING: m.number = m.number1 / m.number2; break;
						}
						m.knows_number = true;
					}
				}
			}
		}
		monkeys.clear();
		for (monkey& m : temp)
			monkeys.push_back(m);
		temp.clear();
	}

	cout << monkeys[0].number << endl;
	cout << monkeys[0].number1 << " == " << monkeys[0].number2 << endl;
}
