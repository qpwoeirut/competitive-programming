/*
 * 6c.cpp
 *
 *  Created on: Oct 11, 2019
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

#define PF push_front
#define PB push_back
#define I insert

#define F first
#define S second
#define B begin
#define E end

#define SZ(A) ((int)(A).size());
#define SORT(A) sort(A.begin(), A.end());
#define REV(A) reverse(A.begin(), A.end());

#define PRS(A, N) for (int i=0; i<N; i++) cout << A[i] << " ";
#define PRL(A, N) for (int i=0; i<N; i++) cout << A[i] << endl;
#define PRSSET(A) for (set<int>::iterator it=A.B(); it!=A.E(); it++) cout << *it << " ";
#define PRLSET(A) for (set<int>::iterator it=A.B(); it!=A.E(); it++) cout << *it << endl;

typedef long long ll;
typedef unsigned long long ull;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;

typedef map<int,int> mii;
typedef map<ll,ll> mll;
typedef map<char, int> mci;
typedef map<string,int> msi;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	int N;
	cin >> N;

	int a[100001];
	for (int i=0; i<N; i++) {
		cin >> a[i];
	}

	int t1[100002], t2[100002];
	t1[0] = 0;
	for (int i=1; i<=N; i++) {
		t1[i] = t1[i-1] + a[i-1];
	}

	t2[N] = 0;
	for (int i=N-1; i>=0; i--) {
		t2[i] = t2[i+1] + a[i];
	}

	int l=0, r=N;
	while (l < r) {
		while (l < r && t1[l] <= t2[r]) {
			l++;
		}
		while (l < r && t1[l] > t2[r]) {
			r--;
		}
	}

	cout << l << " " << N-r << endl;

	return 0;
}
