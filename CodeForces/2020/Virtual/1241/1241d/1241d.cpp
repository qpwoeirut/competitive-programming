/*
 * 1241d.cpp
 *
 *  Created on: Oct 6, 2019
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

#define PRS(A) for (int i=0; i<SZ(A); i++) cout << A[i] << " ";
#define PRL(A) for (int i=0; i<SZ(A); i++) cout << A[i] << endl;

typedef long long ll;
typedef unsigned long long ull;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;

typedef map<int,int> mii;
typedef map<ll,ll> mll;
typedef map<string,int> msi;

int solve() {
	int N;
	cin >> N;

	pii pos[300001];
	for (int i=0; i<=N; i++) {
		pos[i] = MP(INT_MAX, -1);
	}
	int tmp;
	for (int i=0; i<N; i++) {
		cin >> tmp;
		pos[tmp] = MP(min(pos[tmp].first, i), max(pos[tmp].second, i));
	}

	int ct = 0;
	int best = 0;
	int rel_sort = 0;
	pii prev = MP(-1, -1);
	for (int i=0; i<=N; i++) {
		if (pos[i].second == -1) {
			continue;
		}
		if (prev.first == -1) {
			prev = pos[i];
			continue;
		}

		ct++;
		if (prev.second < pos[i].first) {
			rel_sort++;
			best = max(rel_sort, best);
		}
		else {
			rel_sort = 0;
		}
		prev = pos[i];
	}

	return ct - best;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	int T;
	cin >> T;
	while (T>0) {
		T--;
		cout << solve() << endl;
	}


	return 0;
}
