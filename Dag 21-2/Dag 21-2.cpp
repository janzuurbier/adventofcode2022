#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <vector>
#include <stdexcept>
#include <sstream>

using namespace std;

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
	char operation;

	bool operator<(const monkey& rhs) const {
		return naam < rhs.naam;
	}
};

map<string, monkey> all_monkeys;

string find_expression(string monkeynaam) {
	monkey m = all_monkeys[monkeynaam];
	if (m.knows_number) {
		if (m.naam == "humn")
			return "?";
		else
			return to_string(m.number);
	}
	return "(" + find_expression(m.monkey1) + " " + m.operation + " " + find_expression(m.monkey2) + ")";
}

int64_t hulp_eval(const string& s) {
	size_t p = 1;
	string sval1;
	while (s[p] != ' ') {
		sval1 += s[p];
		p++;
	}
	p++;
	char op = s[p];
	p++;
	p++;
	string sval2;
	while (s[p] != ')') {
		sval2 += s[p];
		p++;
	}
	int64_t ival1 = stoll(sval1);
	int64_t ival2 = stoll(sval2);
	switch (op) {
	case '+': ival1 += ival2; break;
	case '-': ival1 -= ival2; break;
	case '*': ival1 *= ival2; break;
	case '/': ival1 /= ival2; break;
	}
	return ival1;
}

string& reduce(string& s) {
	size_t p = s.find(')');
	size_t q = s.rfind('(', p);
	string t = s.substr(q, p - q + 1);
	int64_t val = hulp_eval(t);
	s.replace(q, p - q + 1, to_string(val));
	return s;
}

string eval(string s) {
	while (s[0] == '(') {
		s = reduce(s);
	}
	return s;
}

//parameter val can replace the ?
int64_t calculate(string expression, int64_t val = 0) {
	size_t pos = expression.find('?');
	if(pos != expression.npos)
		expression.replace(pos, 1, to_string(val));
	return stoll(eval(expression));
}


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
			m.number = stoi(line);
			m.knows_number = true;
		}
		catch (const invalid_argument& ia) {
			stringstream ss(line);
			ss >> m.monkey1 >> m.operation >> m.monkey2;
		}
		all_monkeys[m.naam] = m;
	}

	monkey root = all_monkeys["root"];
	string s1 = find_expression(root.monkey1);
	string s2 = find_expression(root.monkey2);

	cout << s1 << endl;
	cout << s2 << endl;

	int64_t a = calculate(s2);
	cout << a << endl;

	int64_t h = 4000000000000;
	int64_t l = 3000000000000;
	int64_t midden;
	while (true) {
		midden = (h + l) / 2;
		int64_t x = calculate(s1, midden);
		cout << x << endl;
		if (x > a)
			l = midden;
		else if (x < a)
			h = midden;
		else
			break;
	}
	cout << midden << endl;
	for (int64_t i = midden - 10; i < midden + 5; i++) {
		cout << "f(" << i << ") = " << calculate(s1, i) << endl;
	}
}



