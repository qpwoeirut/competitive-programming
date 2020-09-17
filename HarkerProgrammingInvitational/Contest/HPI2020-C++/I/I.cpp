#include <iostream>
#include <algorithm>
#include <map>
#include <set>
#include <string>

using namespace std;

int N, K;
map<string, int> mem[101][5];

string remove(string s, string b) {
	string ret = "";
	for (int i=0; i<s.size(); i++) {
		if (b.find(s[i]) == string::npos) {
			ret.push_back(s[i]);
		}
	}

	return ret;
}

string skills[101];

int dp(int idx, int ct, string rem) {
	if (ct == K) {
		return rem.empty();
	}
	if (idx == N) {
		return 0;
	}

	map<string,int>::iterator it=mem[idx][ct].find(rem);
	if (it != mem[idx][ct].end()) {
		return it->second;
	}

	mem[idx][ct][rem] = dp(idx+1, ct, rem) + dp(idx+1, ct+1, remove(rem, skills[idx]));
	return mem[idx][ct][rem];
}

int main() {
	cin >> N >> K;

	string S;
	cin >> S;

	for (int i=0; i<N; i++) {
		cin >> skills[i];
	}

	cout << dp(0, 0, S) << endl;

	return 0;
}
