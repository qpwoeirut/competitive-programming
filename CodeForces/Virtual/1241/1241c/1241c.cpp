/*
 * 1241c.cpp
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

int gcd(int a, int b) {
	if (a == 0) {
		return b;
	}
	if (b == 0) {
		return a;
	}
	if (a == b) {
		return a;
	}

	if (a > b) {
		return gcd(a-b, b);
	}
	else {
		return gcd(a, b-a);
	}
}

int solve() {
	int N;
	cin >> N;

	int tickets[200001];
	for (int i=0; i<N; i++) {
		cin >> tickets[i];
		tickets[i] /= 100;
	}
	sort(tickets, tickets+N, greater<int>());

	int x, a, y, b;
	cin >> x >> a >> y >> b;
	if (x < y) {
		swap(x, y);
		swap(a, b);
	}
	int c = gcd(a, b);

	int arr[6][3] = {
		{a, b, c},
		{a, c, b},
		{b, a, c},
		{b, c, a},
		{c, a, b},
		{c, b, a}
	};

	ll k;
	cin >> k;

	int order[200001];

	int best = INT_MAX;
	int idx;
	for (int p=0; p<6; p++) {
		idx = 0;
		fill(order, order+N, -1);
		for (int i=0; i<3; i++) {
			for (int j=arr[p][i]-1; j<N; j+=arr[p][i]) {
				if (order[j] == -1) {
					order[j] = tickets[idx];
					idx++;
				}
			}
		}

		ll sum = 0;
		for (int i=0; i<N; i++) {
			if (order[i] > 0) {
				if (((i+1) % a) == 0) {
					sum += x * order[i];
				}
				if (((i+1) % b) == 0) {
					sum += y * order[i];
				}
			}
			if (sum >= k) {
				best = min(best, i+1);
				break;
			}
		}
	}

	return best == INT_MAX ? -1 : best;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	int T;
	cin >> T;
	while (T > 0) {
		T--;
		cout << solve() << endl;
	}

	return 0;
}
