/*
 * 1208b.cpp
 *
 *  Created on: Aug 25, 2019
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

int a[2001];
int dp[2001][2001];
set<int> used;
int gen(int l, int r) {
	if (l == r) return 0;
	if (dp[l][r] != -1) {
		return dp[l][r];
	}

	int ret = r - l + 1;
	if (ret > 0 && used.find(a[l]) == used.end()) {
		used.insert(a[l]);
		ret = min(ret, gen(l+1, r));
		used.erase(a[l]);
	}
	if (ret > 0 && used.find(a[r]) == used.end()) {
		used.insert(a[r]);
		ret = min(ret, gen(l, r-1));
		used.erase(a[r]);
	}

	dp[l][r] = ret;
	return dp[l][r];
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	int N;
	cin >> N;
	for (int i=0; i<N; i++) {
		cin >> a[i];
	}
	for (int i=0; i<=N; i++) {
		for (int j=0; j<=N; j++) {
			dp[i][j] = -1;
		}
	}

	cout << gen(0, N-1) << endl;

	return 0;
}
