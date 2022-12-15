#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

struct packet {
	int x = -1;
	vector<packet> y;

	void make_packet(string s) {
		if (s.size() == 0) return;
		if (s[0] == '[') {
			s = s.substr(1, s.size() - 2);
			if (s.size() == 0) return;
			while (true) {
				int bracket_count = 0;
				int pos = 0;
				for (; pos < s.size(); pos++) {
					if (s[pos] == '[')
						bracket_count++;
					if (s[pos] == ']')
						bracket_count--;
					if (s[pos] == ',' && bracket_count == 0)
						break;
				}
				if (pos == s.size())
					break;
				string t = s.substr(0, pos);
				s = s.substr(pos + 1);
				packet p;
				p.make_packet(t);
				y.push_back(p);
			}
			packet p;
			p.make_packet(s);
			y.push_back(p);
		}
		else{
			x = stoi(s);
		}
	}

	friend ostream& operator<<(ostream& os, const packet& p) {
		if (p.x == -1) {
			os << '[';
			if (p.y.size() > 0) 
				os << p.y[0];
			for (int i = 1; i < p.y.size(); i++)
				os << ',' << p.y[i];
			os << ']';
		}
		else
			os << p.x;
		return os;
	}

	
	friend int  compare(const packet& lhs, const packet& rhs) {
		if (lhs.x == -1 && rhs.x == -1) {			
			int i = 0;
			while (i < lhs.y.size() && i < rhs.y.size()) {
				if (compare(lhs.y[i], rhs.y[i]) < 0) 
					return -1;			
				else if (compare(lhs.y[i], rhs.y[i]) > 0)
					return 1;				
				i++;
			}
			if (i == lhs.y.size() && i == rhs.y.size())
				return 0;
			else if (i == lhs.y.size())
				return -1;
			else 
				return 1;
		}
		else if (lhs.x > -1 && rhs.x > -1) {
			if (lhs.x < rhs.x)
				return -1;
			else if (lhs.x > rhs.x)
				return 1;
			else
				return 0;
		}
		else if (lhs.x == -1 && rhs.x > -1) {
			packet p;
			p.x = -1;
			packet q;
			q.x = rhs.x;
			p.y.push_back(q);
			return compare(lhs, p);
		}
		else if (lhs.x > -1 && rhs.x == -1){
			packet p;
			p.x = -1;
			packet q;
			q.x = lhs.x;
			p.y.push_back(q);
			return compare(p, rhs);
		}
	}

	friend bool operator<(const packet& lhs, const packet& rhs) {
		return compare(lhs, rhs) < 0;
	}

	friend bool operator==(const packet& lhs, const packet& rhs) {
		return compare(lhs, rhs) == 0;
	}
};



int main()
{
	ifstream input("C:\\Users\\Jan\\Desktop\\input.txt");
	if (!input) {
		cout << "file not found" << endl;
		return 1;
	}

	vector<packet> v;

	string line;
	while (getline(input, line)) {
		if (line.size() > 0) {
			packet p;
			p.make_packet(line);
			v.push_back(p);
		}
	}
	packet p;
	p.make_packet("[[2]]");
	v.push_back(p);
	packet q;
	q.make_packet("[[6]]");
	v.push_back(q);

	sort(v.begin(), v.end());

	int index = 1;
	int indexp = 0;
	int indexq = 0;
	for (packet r : v) {
		cout << r << endl;
		if (r == p)
			indexp = index;
		if (r == q)
			indexq = index;
		index++;
	}
	cout << indexp * indexq << endl;
}