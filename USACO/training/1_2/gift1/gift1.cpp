/*
ID: zhongbr1
TASK: gift1
LANG: C++11
 */

#include <fstream>
#include <string>
#include <map>

using namespace std;

int main() {
	ifstream fin("gift1.in");
	ofstream fout("gift1.out");
	int NP;
	fin >> NP;
	map<string, int> accounts;
	string ppl[10];

	for (int i=0; i<NP; i++) {
		fin >> ppl[i];
		accounts[ppl[i]] = 0;
	}

	string giver, receiver;
	int total, amt, gift_c;
	for (int i=0; i<NP; i++) {
		fin >> giver >> total >> gift_c;
		amt = total / gift_c;
		accounts[giver] -= total;
		if (total > 0 && gift_c > 0) {
			accounts[giver] += total % gift_c;
			for (int j=0; j<gift_c; j++) {
				fin >> receiver;
				accounts[receiver] += amt;
			}
		}
	}

	for (int i=0; i<NP; i++) {
		fout << ppl[i] << " " << accounts[ppl[i]] << endl;
	}

	return 0;
}
