#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

struct blueprint {
	int ore_robot_ore;
	int clay_robot_ore;
	int obs_robot_ore;
	int obs_robot_clay;
	int geo_robot_ore;
	int geo_robot_obs;
	int max_ore_robots;
};

blueprint bp;

int get_max(int ore, int clay, int obs, int geode, int nrorr, int nrclr, int nrobr, int nrgr, int minute_left) {
	string s;
	if (minute_left == 0) return geode;
	if (minute_left == 1) return geode + nrgr;
	if (minute_left == 2 && ore >= bp.geo_robot_ore && obs >= bp.geo_robot_obs) {
		return geode + 2 * nrgr + 1;
	}
	if (minute_left == 2) return geode + 2 * nrgr;
	//don't build anymore robots
	int max = geode + minute_left * nrgr;
	//next robot is geode robot
	if (nrobr != 0) {
		int k1;
		if (ore >= bp.geo_robot_ore)
			k1 = 0;
		else if (ore < bp.geo_robot_ore) {
			int r1 = (bp.geo_robot_ore - ore) % nrorr;
			int d1 = (bp.geo_robot_ore - ore) / nrorr;
			k1 = r1 == 0 ? d1 : d1 + 1;
		}
		int k2;
		if (obs >= bp.geo_robot_obs)
			k2 = 0;
		if (obs < bp.geo_robot_obs) {
			int r2 = (bp.geo_robot_obs - obs) % nrobr;
			int d2 = (bp.geo_robot_obs - obs) / nrobr;
			k2 = r2 == 0 ? d2 : d2 + 1;
		}
		int k = k1 > k2 ? k1 : k2;
		k++;
		if (k < minute_left - 1) {
			int n = get_max(ore - bp.geo_robot_ore + k * nrorr, clay + k * nrclr, obs - bp.geo_robot_obs + k * nrobr, geode + k * nrgr, nrorr, nrclr, nrobr, nrgr + 1, minute_left - k);
			if (n > max) {
				max = n;
			}
		}
	}
	//next robort is obsidian robot
	if (nrclr != 0) {
		int k1;
		if (ore >= bp.obs_robot_ore)
			k1 = 0;
		if (ore < bp.obs_robot_ore) {
			int r1 = (bp.obs_robot_ore - ore) % nrorr;
			int d1 = (bp.obs_robot_ore - ore) / nrorr;
			k1 = r1 == 0 ? d1 : d1 + 1;
		}
		int k2;
		if (clay >= bp.obs_robot_clay)
			k2 = 0;
		if (clay < bp.obs_robot_clay) {
			int r2 = (bp.obs_robot_clay - clay) % nrclr;
			int d2 = (bp.obs_robot_clay - clay) / nrclr;
			k2 = r2 == 0 ? d2 : d2 + 1;
		}
		int k = k1 > k2 ? k1 : k2;
		k++;
		if (k < minute_left - 1 && geode + nrgr * minute_left + (minute_left - k) * (minute_left - k - 1) / 2 > max) {
			int n = get_max(ore - bp.obs_robot_ore + k * nrorr, clay - bp.obs_robot_clay + k * nrclr, obs + k * nrobr, geode + k * nrgr, nrorr, nrclr, nrobr + 1, nrgr, minute_left - k);
			if (n > max) {
				max = n;
			}
		}
	}
	//next robot is clay robot
	int k;
	if (ore >= bp.clay_robot_ore) {
		k = 0;
	}
	else {
		int r = (bp.clay_robot_ore - ore) % nrorr;
		int d = (bp.clay_robot_ore - ore) / nrorr;
		k = r == 0 ? d : d + 1;
	}
	k++;
	if (k < minute_left - 2 && geode + nrgr * minute_left + (minute_left - k) * (minute_left - k - 1) / 2 > max) {
		int n = get_max(ore - bp.clay_robot_ore + k * nrorr, clay + k * nrclr, obs + k * nrobr, geode + k * nrgr, nrorr, nrclr + 1, nrobr, nrgr, minute_left - k);
		if (n > max) {
			max = n;
		}
	}
	//next robot is ore robot.
	if (nrorr < bp.max_ore_robots) {
		if (ore >= bp.ore_robot_ore) {
			k = 0;
		}
		else {
			int r = (bp.ore_robot_ore - ore) % nrorr;
			int d = (bp.ore_robot_ore - ore) / nrorr;
			k = r == 0 ? d : d + 1;
		}
		k++;
		if (k < minute_left - 1 && geode + nrgr * minute_left + (minute_left - k) * (minute_left - k - 1) / 2 > max) {
			int n = get_max(ore - bp.ore_robot_ore + k * nrorr, clay + k * nrclr, obs + k * nrobr, geode + k * nrgr, nrorr + 1, nrclr, nrobr, nrgr, minute_left - k);
			if (n > max) {
				max = n;
			}
		}
	}

	return max;
}


int main()
{
	ifstream input("C:\\Users\\Jan\\Desktop\\input.txt");
	if (!input) {
		cout << "file not found" << endl;
		return 1;
	}

	string line;
	int nr_of_blueprint = 0;
	int sum = 0;
	while (getline(input, line)) {
		nr_of_blueprint++;
		bp.max_ore_robots = 0;
		stringstream ss(line);
		string s;
		for (int i = 0; i < 6; i++) ss >> s;
		ss >> bp.ore_robot_ore;
		if (bp.ore_robot_ore > bp.max_ore_robots) bp.max_ore_robots = bp.ore_robot_ore;
		for (int i = 0; i < 5; i++) ss >> s;
		ss >> bp.clay_robot_ore;
		if (bp.clay_robot_ore > bp.max_ore_robots) bp.max_ore_robots = bp.clay_robot_ore;
		for (int i = 0; i < 5; i++) ss >> s;
		ss >> bp.obs_robot_ore;
		if (bp.obs_robot_ore > bp.max_ore_robots) bp.max_ore_robots = bp.obs_robot_ore;
		for (int i = 0; i < 2; i++) ss >> s;
		ss >> bp.obs_robot_clay;
		for (int i = 0; i < 5; i++) ss >> s;
		ss >> bp.geo_robot_ore;
		if (bp.geo_robot_ore > bp.max_ore_robots) bp.max_ore_robots = bp.geo_robot_ore;
		for (int i = 0; i < 2; i++) ss >> s;
		ss >> bp.geo_robot_obs;
		int nr_of_geodes = get_max(0, 0, 0, 0, 1, 0, 0, 0, 24);
		cout << nr_of_blueprint << ": " << nr_of_geodes << endl;
		sum += nr_of_blueprint * nr_of_geodes;
	}
	cout << sum << endl;
}
