/*
 * lifeguards.cpp
 *
 *  Created on: Dec 13, 2018
 *      Author: Stanley
 */

#include <fstream>
#include <bitset>

using namespace std;

struct Shift {
	int start, end;
	int len;
	int only_lg;
};

int main() {
	ifstream fin("lifeguards.in");
	ofstream fout("lifeguards.out");

	int lg_c;
	fin >> lg_c;


	Shift shifts[lg_c];
	for (int l=0; l<lg_c; l++) {
		fin >> shifts[l].start >> shifts[l].end;
		shifts[l].only_lg = 0;
	}

	for (int l=0; l<lg_c; l++) {
		for (int i=shifts[l].start; i<shifts[l].end; i++) {
			if (false) {

			}
		}
	}

	return 0;
}
