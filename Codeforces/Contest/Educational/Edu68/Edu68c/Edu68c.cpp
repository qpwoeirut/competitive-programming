/*
 * Edu68c.cpp
 *
 *  Created on: Jul 14, 2019
 *      Author: Stanley
 */

#include <iostream>
#include <map>

using namespace std;

map<char, int> ct;
bool sol(const string& S, const string& T, int idx1, int idx2) {
	if (idx1 == S.size() && idx2 == T.size()) return true;

	if (S[idx1] == T[idx2]) return sol(S, T, idx1 + 1, idx2 + 1);

	bool ret = false;
	map<char,int>::iterator it = ct.find(T[idx2]);
	if (it != ct.end() && it->second > 0) {
		it->second--;
		if (sol(S, T, idx1, idx2+1)) ret = true;
		it->second++;
	}

	return ret;
}

int main() {
	int Q;
	cin >> Q;

	string p, s, t;
	for (int i=0; i<Q; i++) {
		cin >> s >> t >> p;

		ct.clear();
		for (int i=0; i<p.size(); i++) {
			ct[p[i]]++;
		}
		cout << (sol(s, t, 0, 0) ? "YES" : "NO") << endl;
	}

	return 0;
}
