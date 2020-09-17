/*
 * 1201a.cpp
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

int main() {
	int N, M;
	cin >> N >> M;

	string str[1001];
	int pts[1001];
	for (int i=0; i<N; i++) {
		cin >> str[i];
	}
	for (int i=0; i<M; i++) {
		cin >> pts[i];
	}
	int ct[1001][5];
	for (int i=0; i<M; i++) {
		for (int j=0; j<5; j++) {
			ct[i][j] = 0;
		}
	}

	for (int i=0; i<N; i++) {
		for (int j=0; j<M; j++) {
			ct[j][str[i][j] - 'A']++;
		}
	}

	int ans = 0;
	for (int i=0; i<M; i++) {
		ans += pts[i] * (*max_element(ct[i], ct[i]+5));
	}

	cout << ans << endl;


	return 0;
}
