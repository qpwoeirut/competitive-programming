/*
 * 101853a.cpp
 *
 *  Created on: Aug 29, 2019
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

void solve() {
	int N, Q;
	cin >> N >> Q;

	int a[100001];
	mii ct;
	for (int i=0; i<N; i++) {
		cin >> a[i];
		ct[a[i]]++;
	}

	int t;
	int p, v;
	for (int i=0; i<Q; i++) {
		cin >> t;
		if (t == 1) {
			cin >> p >> v;
			p--;

			mii::iterator it = ct.find(a[p]);
			if (it->second == 1) {
				ct.erase(it);
			}
			else {
				it->second--;
			}
			a[p] = v;
			ct[a[p]]++;
		}
		else {
			cout << ct.size() << endl;
		}
	}
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
