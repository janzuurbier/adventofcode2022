#include <iostream>
#include <string>
#include <fstream>

using namespace std;

int64_t decode(string s) {
	int64_t retval = 0;
	while (s.size() > 0) {
		retval *= 5;
		char ch = s[0];
		s = s.substr(1);
		switch (ch) {
		case '2': retval += 2; break;
		case '1': retval += 1; break;
		case '0': retval += 0; break;
		case '-': retval += -1; break;
		case '=': retval += -2; break;
		}
	}
	return retval;
}

string encode(int64_t val) {
	string retstring;
	while (val > 0) {
		int64_t rest = val % 5;
		val /= 5;
		switch (rest) {
		case 2: retstring = '2' + retstring; break;
		case 1: retstring = '1' + retstring; break;
		case 0: retstring = '0' + retstring; break;
		case 3: retstring = '=' + retstring;  val += 1;  break;
		case 4: retstring = '-' + retstring; val += 1; break;
		}
	}
	return retstring;
}

int main()
{
	ifstream input("C:\\Users\\Jan\\Desktop\\input.txt");
	if (!input) {
		cout << "file not found" << endl;
		return 1;
	}

	int64_t sum = 0;

	string line;
	while (getline(input, line)) {
		sum += decode(line);
	}
	cout << sum << endl;
	cout << encode(sum) << endl;
}