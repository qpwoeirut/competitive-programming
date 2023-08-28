/*
 * 4b.cpp
 *
 *  Created on: Aug 19, 2019
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

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	int D, sum;
	cin >> D >> sum;

	int mn[31], mx[31];
	int mns = 0, mxs = 0;
	for (int i=0; i<D; i++) {
		cin >> mn[i] >> mx[i];
		mns += mn[i];
		mxs += mx[i];
	}

	if (mns > sum || mxs < sum) {
		cout << "NO" << endl;
		return 0;
	}

	if (mns == sum || mxs == sum) {
		cout << "YES" << endl;
		return 0;
	}

	int diff = mxs - sum;

	while (diff > 0) {
		for (int i=0; diff > 0 && i<D; i++) {
			if (mx[i] - 1 >= mn[i]) {
				mx[i]--;
				diff--;
			}
		}
	}

	for (int i=0; i<D; i++) {
		cout << mx[i] << " ";
	}
	cout << endl;

	return 0;
}
