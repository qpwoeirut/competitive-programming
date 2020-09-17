/*
 * 1201d.cpp
 *
 *  Created on: Aug 4, 2019
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

typedef long long ll;
typedef unsigned long long ull;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;

bool comp(const pii& a, const pii& b) {
	if (a.F == b.F) return a.S < b.S;
	return a.F < b.F;
}

int N, M, K, Q;
int s[200001];
vector<pii> t(200001, MP(INT_MAX, INT_MIN));
int dist(pii start, pii end) {
	if (start.F == end.F) return end.S - start.S;
	int safe = -1;
	int df = INT_MAX;
	for (int i=0; i<Q; i++) {
		if (s[i] < start.S) {
			if (df > start.S - s[i]) {
				df = start.S - s[i];
				safe = s[i];
			}
		}
		else if (start.S <= s[i] && s[i] <= end.S) {
			df = 0;
			safe = s[i];
			break;
		}
		else if (df > s[i] - end.S) {
			df = s[i] - end.S;
			safe = s[i];
		}
	}

	return end.F - start.F + df + abs(safe - end.S);
}

ll mem[200001];
ll dp(int row) {
	if (row == N) return 0;
	if (mem[row] != -1) {
		return mem[row];
	}


}

int main() {
	cin >> N >> M >> K >> Q;

	int ta, tb;
	for (int i=0; i<K; i++) {
		cin >> ta >> tb;
		ta--;
		tb--;
		t[ta].F = min(t[ta].F, tb);
		t[ta].S = max(t[ta].S, tb);
	}

	for (int i=0; i<Q; i++) {
		cin >> s[i];
		s[i]--;
	}

	return 0;
}
