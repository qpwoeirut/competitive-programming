/*
 * 1281d.cpp
 *
 *  Created on: Dec 14, 2019
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

#define PF push_front
#define PB push_back
#define I insert

#define F first
#define S second
#define B begin
#define E end

#define LB lower_bound
#define UB upper_bound

#define PRS(A, N) for (int i=0; i<N; i++) cout << A[i] << " ";
#define PRL(A, N) for (int i=0; i<N; i++) cout << A[i] << endl;
#define PISET(A) for (set<int>::iterator it=A.B(); it!=A.E(); it++) cout << *it << " ";
#define PSSET(A) for (set<string>::iterator it=A.B(); it!=A.E(); it++) cout << *it << " ";

typedef long long ll;
typedef unsigned long long ull;
typedef pair<int,bool> pib;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;

typedef map<int,int> mii;
typedef map<ll,ll> mll;
typedef map<char, int> mci;
typedef map<string,int> msi;

ll gcd(ll a, ll b) {return b ? gcd(b, a%b) : a;}

const ll MOD = 1e9+7; // 998244353;
const ll INF = 1e18;

int R, C;
int ctr[61];
int ctc[61];

bool all_row_col() {
	for (int i=0; i<R; i++) {
		if (ctr[i] == C) return true;
	}
	for (int i=0; i<C; i++) {
		if (ctc[i] == R) return true;
	}
	return false;
}

void solve() {
	cin >> R >> C;
	string grid[61];
	for (int i=0; i<R; i++) {
		cin >> grid[i];
	}
	fill(ctr, ctr+R, 0);
	fill(ctc, ctc+C, 0);

	int a = 0;
	for (int i=0; i<R; i++) {
		for (int j=0; j<C; j++) {
			if (grid[i][j] == 'A') {
				a++;
				ctr[i]++;
				ctc[j]++;
			}
		}
	}

	if (a == 0) {
		cout << "MORTAL" << endl;
		return;
	}
	if (a == R*C) {
		cout << 0 << endl;
		return;
	}
	if (ctr[0] == C || ctr[R-1] == C || ctc[0] == R || ctc[C-1] == R) {
		cout << 1 << endl;
		return;
	}
	if (grid[0][0] == 'A' || grid[R-1][0] == 'A' || grid[0][C-1] == 'A' || grid[R-1][C-1] == 'A') {
		cout << 2 << endl;
		return;
	}
	if (all_row_col()) {
		cout << 2 << endl;
		return;
	}
	if (ctr[0] > 0 || ctr[R-1] > 0 || ctc[0] > 0 || ctc[C-1] > 0) {
		cout << 3 << endl;
		return;
	}

	cout << 4 << endl;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	int T;
	cin >> T;

	while (T > 0) {
		T--;
		solve();
	}

	return 0;
}
