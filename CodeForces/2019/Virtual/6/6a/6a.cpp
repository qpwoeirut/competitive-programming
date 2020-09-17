/*
 * 6a.cpp
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

	int a[4];
	for (int i=0; i<4; i++) {
		cin >> a[i];
	}
	sort(a, a+4);

	bool seg = false;
	for (int i=0; i<4; i++) {
		for (int j=i+1; j<4; j++) {
			for (int k=j+1; k<4; k++) {
				if (a[i] + a[j] > a[k]) {
					cout << "TRIANGLE" << endl;
					return 0;
				}
				else if (a[i] + a[j] == a[k]) {
					seg = true;
				}
			}
		}
	}

	if (seg) {
		cout << "SEGMENT" << endl;
	}
	else {
		cout << "IMPOSSIBLE" << endl;
	}

	return 0;
}
