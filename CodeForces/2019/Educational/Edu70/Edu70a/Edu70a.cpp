/*
 * Edu70a.cpp
 *
 *  Created on: Aug 7, 2019
 *      Author: Stanley
 */


#include <iostream>
#include <algorithm>
#include <cctype>
#include <climits>
#include <cmath>
#include <cstdlib>
#include <iomanip>
#include <utility>
#include <bitset>
#include <deque>
#include <forward_list>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

#define MP make_pair

#define PB push_back
#define F first
#define S second
#define B begin
#define E end

#define SZ(A) ((int)(A).size());
#define SORT(A) sort(A.begin(), A.end());
#define REV(A) reverse(A.begin(), A.end());

#define PR(a) cout << a << " ";
#define PR1(a) cout << a << endl;
#define PR2(a,b) cout << a << " " << b << endl;
#define PR3(a,b,c) cout << a << " " << b << " " << c << endl;
#define PR4(a,b,c,d) cout << a << " " << b << " " << c << " " << d << endl;

typedef long long ll;
typedef unsigned long long ull;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;

bool lex_min(const vector<bool>& a, const vector<bool>& b) {
	int ln = min(a.size(), b.size());
	for (int i=0; i<ln; i++) {
		if (a[i] ^ b[i]) return a[i];
	}

	return a.size() > b.size();
}

vector<bool> radd(const vector<bool>& a, const vector<bool>& b, int idx) {
	int N = a.size(), M = b.size();
	int ln = max(N, M);
	vector<bool> ret(idx);
	for (int i=0; i<idx; i++) {
		ret[i] = a[N-i-1];
	}

	bool ca, cb, cc = false;
	for (int i=0; i<ln; i++) {
		ca = (i+idx<a.size() && a[N-idx-i-1]);
		cb = (i<b.size() && b[M-i-1]);
		ret.push_back((ca ^ cb) ^ cc);
		cc = (ca & cb) | (ca & cc) | (cb & cc);
	}
	if (cc) ret.push_back(cc);

	return ret;
}

void solve() {
	string tmp;
	cin >> tmp;
	vector<bool> x(tmp.size());
	for (int i=0; i<tmp.size(); i++) {
		x[i] = (tmp[i] == '1');
	}
	cin >> tmp;

	vector<bool> y(tmp.size());
	for (int i=0; i<tmp.size(); i++) {
		y[i] = (tmp[i] == '1');
	}

	vector<bool> mn;
	vector<bool> sum;
	int best = -1;
	for (int sh=0; sh<x.size(); sh++) {
		sum = radd(x, y, sh);
		if (best == -1 || lex_min(mn, sum)) {
			best = sh;
			mn = sum;
		}
	}

	cout << best << endl;
}

int main() {
	int T;
	cin >> T;

	while (T > 0) {
		T--;

		solve();
	}

	return 0;
}
