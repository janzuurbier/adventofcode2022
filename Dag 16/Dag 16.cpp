#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <map>
#include <set>

using namespace std;

int N = 26;

struct valve;

struct valve {
	string naam;
	int flowrate;
	vector<string> verbonden_namen;
	vector<valve*> verbonden_valves;
	bool closed = true;
	int temp_dist;
};

map<string, valve*> lookup;
vector<valve*> valves_with_flow;
vector<valve*> all_valves;
map<pair<valve*, valve*>, int> distance_table;

int get_max(valve* v, set<valve*> rest, int steps_left) {
	if (steps_left < N) steps_left--; //voor opendraaien kraan
	if (rest.size() == 0 || steps_left <=0)
		return v->flowrate*(steps_left );
	int max = 0;
	for (valve* w : rest) {
		set<valve*> hulp = rest;
		hulp.erase(w);
		int m = get_max(w, hulp, steps_left  - distance_table[pair<valve*, valve*>(v, w)]);
		if (m > max) max = m;
	}
	return max + v->flowrate*(steps_left );
}

int main()
{
	ifstream input("C:\\Users\\Jan\\Desktop\\input.txt");
	if (!input) {
		cout << "file not found" << endl;
		return 1;
	}

	string line;
	while (getline(input, line)) {
		valve* v = new valve; ;
		v->naam = line.substr(6, 2);
		size_t p = line.find('=');
		size_t q = line.find(';');
		v->flowrate = stoi(line.substr(p + 1, p - q));
		for (int i = 0; i < 5; i++) {
			p = line.find(' ', p + 1);
		}
		line = line.substr(p + 1);
		while (true) {
			v->verbonden_namen.push_back(line.substr(0, 2));
			if (line.size() < 4) break;
			line = line.substr(4);			
		}
		lookup.insert(pair<string, valve*>(v->naam, v));
		if (v->flowrate > 0) valves_with_flow.push_back(v);
		all_valves.push_back(v);
	}
	
	
	for (auto it : lookup) {
		valve* v = it.second;
		for (string s : v->verbonden_namen) 
			v->verbonden_valves.push_back(lookup[s]);
	}

	//create distance table
	valves_with_flow.push_back(lookup["AA"]);
	for (valve* v : valves_with_flow) {
		for (valve* w : all_valves)
			w->temp_dist = 1000;
		bool changed = true;
		set<valve*> tempset1;
		set<valve*> tempset2;
		tempset1.insert(v);
		v->temp_dist = 0;
		int dist = 1;
		while (changed) {
			changed = false;
			for (valve* w : tempset1)
				for (valve* u : w->verbonden_valves) {
					if (dist < u->temp_dist) {
						u->temp_dist = dist;
						changed = true;
					}
					tempset2.insert(u);
				}
			tempset1 = tempset2;
			tempset2.clear();
			dist++;
		}
		
		for (valve* w : valves_with_flow)
			distance_table[pair<valve*, valve*>(v, w)] = w->temp_dist;
	}
	

	/*
	//print distance table
	cout << " \t";
	for (valve* w : valves_with_flow)
		cout << w->naam << '\t';
	cout << endl;
	for (valve* v : valves_with_flow) {
		cout << v->naam << '\t';
		for (valve* w : valves_with_flow)
			cout << distance_table[pair<valve*, valve*>(v, w)] << '\t';
		cout << endl;
	}
	cout << endl;
	*/
	

	valves_with_flow.pop_back();

	/* Part one
	set<valve*> vwf;
	for (valve* v : valves_with_flow)
		vwf.insert(v);
	vwf.erase(lookup["AA"]);

	cout << get_max(lookup["AA"], vwf, 30) << endl;
	*/

	set<valve*> elephant;
	set<valve*> me;	
	//assuming that I and elephant both open 8 valves.
	int max = 0;
	for (int i1 = 0; i1 < 8; i1++)
		for (int i2 = i1 + 1; i2 < 9; i2++)
			for (int i3 = i2 + 1; i3  < 10; i3++)
				for (int i4 = i3 + 1; i4  < 11; i4++)
					for (int i5 = i4 + 1; i5  < 12; i5++)
						for (int i6 = i5 + 1; i6  < 13; i6++)
							for (int i7 = i6 + 1; i7  < 14; i7++)
								for (int i8 = i7 + 1; i8  < 15; i8++)
				
	{
		elephant.clear();
		me.clear();
		int number = (1 << i1) + (1 << i2) + (1 << i3) + (1 << i4) + (1 << i5) + (1 << i6) + (1 << i7) + (1 << i8);
		for (valve *v : valves_with_flow) {
			if (number & 1 )
				elephant.insert(v);
			else
				me.insert(v);
			number >>= 1;
		}
		
		cout << i1 << ": ";
		int a = get_max(lookup["AA"], elephant, N);
		int b = get_max(lookup["AA"], me, N);
		if (a + b > max) max = a + b;
		cout  << max << endl;
		
	}
	cout << max << endl;

}
