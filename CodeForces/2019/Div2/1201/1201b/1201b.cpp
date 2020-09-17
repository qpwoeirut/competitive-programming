/*
 * 1201b.cpp
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
	int N;
	cin >> N;

	ll sum = 0;
	ll a[100001];
	for (int i=0; i<N; i++) {
		cin >> a[i];
		sum += a[i];
	}

	if (sum & 1) {
		cout << "NO" << endl;
		return 0;
	}

	for (int i=0; i<N; i++) {
		if (a[i] * 2 > sum) {
			cout << "NO" << endl;
			return 0;
		}
	}

	cout << "YES" << endl;

	return 0;
}
