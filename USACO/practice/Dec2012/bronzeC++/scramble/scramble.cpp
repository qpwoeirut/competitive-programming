/*
 * scramble.cpp
 *
 *  Created on: Dec 22, 2018
 *      Author: Stanley
 *
 * Converting to Java
 * Testing differences between languages
 */

#include <fstream>
#include <algorithm>
#include <list>
#include <string>

using namespace std;

struct Name {
	string val;
	bool reversed;
	int idx;
};

bool comp_name (const Name& a, const Name& b) {
	return a.val < b.val;
}

int main() {
	ifstream fin("scramble.in");
	ofstream fout("scramble.out");

	int name_count;
	fin >> name_count;

	Name tmp_name;
	list<Name> names;
	for (int i = 0; i < name_count; i++) {
		tmp_name.idx = i;
		fin >> tmp_name.val;

		sort(tmp_name.val.begin(), tmp_name.val.end());
		tmp_name.reversed = false;
		names.push_back(tmp_name);

		reverse(tmp_name.val.begin(), tmp_name.val.end());
		tmp_name.reversed = true;
		names.push_back(tmp_name);
	}
	names.sort(comp_name);
	// Stable sort - sorted name will always be before reversed name

	int sorted_pos[50000], reversed_pos[50000];
	int sorted_count = 0, reversed_count = 0;
	for (list<Name>::iterator it = names.begin(); it != names.end(); it++) {
		if (it->reversed == false) {
			sorted_count++;
			sorted_pos[it->idx] = reversed_count + 1;
		}
		else {
			reversed_count++;
			reversed_pos[it->idx] = sorted_count;
			// Don't add 1 to account for the sorted counterpart
		}
	}

	for (int i=0; i<name_count; i++) {
		fout << sorted_pos[i] << " " << reversed_pos[i] << endl;
	}

	fout.close();

	return 0;
}
