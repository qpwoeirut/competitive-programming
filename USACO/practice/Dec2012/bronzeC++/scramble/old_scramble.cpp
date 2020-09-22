/*
 * scramble.cpp
 *
 *  Created on: Dec 20, 2018
 *      Author: Stanley
 *
 * Converted from previous Java submission
 * Testing differences between languages
 */

#include <fstream>
#include <algorithm>
#include <iterator>
#include <set>
#include <string>

using namespace std;

int not_main() {
	ifstream fin("scramble.in");
	ofstream fout("scramble.out");

	int name_count;
	fin >> name_count;
	string sorted_names[name_count];
	string reversed_names[name_count];

	string tmp_str;
	set<string> sorted_name_set, reversed_name_set;
	for (int i = 0; i < name_count; i++) {
		fin >> tmp_str;
		sort(tmp_str.begin(), tmp_str.end());
		sorted_names[i] = tmp_str;
		sorted_name_set.insert(tmp_str);

		reverse(tmp_str.begin(), tmp_str.end());
		reversed_names[i] = tmp_str;
		reversed_name_set.insert(tmp_str);
	}

	int lowPos, highPos;
	for (int i = 0; i < name_count; i++) {
		sorted_name_set.erase(sorted_names[i]);
		sorted_name_set.insert(reversed_names[i]);
		reversed_name_set.erase(reversed_names[i]);
		reversed_name_set.insert(sorted_names[i]);

		lowPos = distance(reversed_name_set.begin(), reversed_name_set.find(sorted_names[i]));
		highPos = distance(sorted_name_set.begin(), sorted_name_set.find(reversed_names[i]));
		lowPos++;
		highPos++;
		fout << lowPos << " " << highPos << endl;

		sorted_name_set.erase(reversed_names[i]);
		sorted_name_set.insert(sorted_names[i]);
		reversed_name_set.erase(sorted_names[i]);
		reversed_name_set.insert(reversed_names[i]);
	}
	fout.close();

	return 0;
}
