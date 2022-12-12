#include <iostream>
#include <string>
#include <fstream>


using namespace std;
//int punten[3][3]  { {4, 1, 7 }, { 8, 5, 2 }, { 3, 9, 6 }};
int punten[3][3]{ {3, 1, 2 }, { 4, 5, 6 }, { 8, 9, 7 } };

int main()
{
	ifstream input("C:\\Users\\Jan\\Desktop\\input.txt");
	if (!input) {
		cout << "file not found" << endl;
		return 1;
	}

	int sum = 0;
	string line;
	while (getline(input, line)) {
			char opponent = line[0];
			char player = line[2]; 
			int points = punten[player - 'X'][opponent - 'A'];
			sum += points;	
			//cout << opponent << " " << player << " " << points << endl;
	}

	cout << endl << sum << endl;
	

}