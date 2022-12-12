// Dag 7.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <fstream>

using namespace std;


int sum = 0;
int64_t min = INT64_MAX;


struct file {
	string name;
	int64_t size;

	file(string n, int64_t s): name(n), size(s) {}

};

struct dir {
	string name;
	dir* parent;
	vector<file> files;
	map<string, dir*> dirs;

	dir(string n, dir* p): name(n), parent(p) {
		
	}

	void addfile(string name, int64_t size) {
		file f(name, size);
		files.push_back(f);
	}

	void adddir(string name, dir* parent) {
		if (dirs.count(name) == 0) {
			dir* d = new dir(name, parent);
			dirs.insert(pair<string, dir*> (name, d));
		}
	}

	int64_t size() {
		int64_t retval = 0;
		for (file f : files) retval += f.size;
		if (dirs.empty())
			return retval;
		for (auto it = dirs.begin(); it != dirs.end(); ++it) {
			retval += it->second->size();
		}
		return retval;
	}

	void listdirs() {
		int64_t s = size();
		cout << name << '\t' << size();
		if (s <= 100000) {
			cout << " **";
			sum += s;
		}
		cout << endl;

		for (auto it = dirs.begin(); it != dirs.end(); ++it) {
			it->second->listdirs();
		}
	}

	void findsmallestover(int64_t unusedspace) {
		int64_t s = size();
		if (unusedspace + s > 30000000L && s < min)
			min = s;
		for (auto it = dirs.begin(); it != dirs.end(); ++it) {
			it->second->findsmallestover(unusedspace);
		}

	}	
};

int main()
{
	ifstream input("C:\\Users\\Jan\\Desktop\\input.txt");
	if (!input) {
		cout << "file not found" << endl;
		return 1;
	}

	dir* home  = new dir("/" , nullptr);
	

	dir* current = home;

	string line;
	while (getline(input, line)) {
		if (line[0] == '$'){
			string command = line.substr(2, 2);
			if (command == "ls") {
				//go to next line
			}
			else if (command == "cd") {
				string newdir = line.substr(5);
				if (newdir == "..") {
					current = current->parent;
				}
				else if (newdir == "/"){
					current = home;
				}
				else {
					current = current->dirs.find(newdir)->second;
				}
			}
		}
		else {
			if (line.substr(0, 3) == "dir") {
				string n = line.substr(4);
				current->adddir(n, current);
			}
			else {
				size_t pos = line.find(' ');
				int s = stoi(line.substr(0, pos));
				string n = line.substr(pos + 1);
				current->addfile(n, s);
			}
		}
	}

	home->listdirs();
	cout << endl << sum << endl;

	int64_t homesize = home->size();
	int64_t unusedspace = 70000000L - homesize;
	home->findsmallestover(unusedspace);

	cout << endl << min << endl;

}
