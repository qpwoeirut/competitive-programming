/*
 * 1201c.cpp
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

#define MAX(a, b) a >= b ? a : b;
#define SZ(A) ((int)(A).size());
#define SORT(A) sort(A.begin(), A.end());
#define REV(A) reverse(A.begin(), A.end());

typedef long long ll;
typedef unsigned long long ull;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;

ll N, K;
ll center;
ll a[200001];
ll needed(ll top) {
	ll rem = 0;
	for (ll i=center; i<N; i++) {
		rem += MAX(0, top - a[i]);
	}

	return rem;
}

int main() {
	cin >> N >> K;
	center = N/2;
	for (int i=0; i<N; i++) {
		cin >> a[i];
	}

	sort(a, a+N);

	ll lo = a[center], hi = a[center] + K;
	while (lo < hi) {
		ll mid = ((1 + hi - lo) / 2) + lo;

		if (needed(mid) < K) {
			lo = mid;
		}
		else if (needed(mid) > K) {
			hi = mid-1;
		}
		else {
			cout << mid << endl;
			return 0;
		}
	}

	cout << lo << endl;

	return 0;
}
