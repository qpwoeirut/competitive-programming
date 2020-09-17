/*
 * 6e.cpp
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
#define RB rbegin

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

	int N, K;
	cin >> N >> K;

	int h[100001];
	for (int i=0; i<N; i++) {
		cin >> h[i];
	}

	mii cur;
	set<pii> pers;
	int start = 0;
	int best = 1;
	for (int i=0; i<N; i++) {
		cur[h[i]]++;
		while (start < i && cur.RB()->first - cur.B()->first > K) {
			mii::iterator it = cur.find(h[start]);
			if (it->second == 1) {
				cur.erase(it);
			}
			else {
				it->second--;
			}

			start++;
		}

		if (i - start + 1 > best) {
			best = i - start + 1;
			pers.clear();
			pers.I(MP(start+1, i+1));
		}
		else if (i - start + 1 == best) {
			pers.I(MP(start+1, i+1));
		}
	}

	cout << best << " " << pers.size() << endl;
	for (set<pii>::iterator it=pers.B(); it!=pers.E(); it++) {
		cout << it->first << " " << it->second << endl;
	}

	return 0;
}
