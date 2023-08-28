/*
 * 1206b.cpp
 *
 *  Created on: Aug 18, 2019
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
	int N;
	cin >> N;

	ll a[100001];
	for (int i=0; i<N; i++) {
		cin >> a[i];
	}

	ll cost = 0;
	int zeroes = 0;
	for (int i=0; i<N; i++) {
		if (a[i] <= -1) {
			cost += -a[i] - 1;
			a[i] = -1;
		}
		else if (a[i] >= 1) {
			cost += a[i] - 1;
			a[i] = 1;
		}
		else {
			zeroes++;
		}
	}

	if (zeroes > 0) {
		cost += zeroes;
	}
	else {
		int prod = a[0];
		for (int i=1; i<N; i++) {
			prod *= a[i];
		}
		if (prod == -1) {
			cost += 2;
		}
	}
	cout << cost << endl;

	return 0;
}
