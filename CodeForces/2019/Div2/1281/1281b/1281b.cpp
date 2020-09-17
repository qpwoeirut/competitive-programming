/*
 * 1281b.cpp
 *
 *  Created on: Dec 14, 2019
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

#define LB lower_bound
#define UB upper_bound

#define PRS(A, N) for (int i=0; i<N; i++) cout << A[i] << " ";
#define PRL(A, N) for (int i=0; i<N; i++) cout << A[i] << endl;
#define PISET(A) for (set<int>::iterator it=A.B(); it!=A.E(); it++) cout << *it << " ";
#define PSSET(A) for (set<string>::iterator it=A.B(); it!=A.E(); it++) cout << *it << " ";

typedef long long ll;
typedef unsigned long long ull;
typedef pair<int,bool> pib;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;

typedef map<int,int> mii;
typedef map<ll,ll> mll;
typedef map<char, int> mci;
typedef map<string,int> msi;

ll gcd(ll a, ll b) {return b ? gcd(b, a%b) : a;}

const ll MOD = 1e9+7; // 998244353;
const ll INF = 1e18;

inline bool lex(const string& a, const string& b) {
	int N = min(a.size(), b.size());
	for (int i=0; i<N; i++) {
		if (a[i] != b[i]) {
			return a[i] < b[i];
		}
	}
	return a.size() < b.size();
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	int T;
	cin >> T;

	string s, c;
	for (int t=0; t<T; t++) {
		cin >> s >> c;
		bool found = false;
		if (lex(s, c)) {
			cout << s << endl;
			found = true;
		}

		int pos[26];
		fill(pos, pos+26, -1);
		for (int i=0; i<s.size(); i++) {
			pos[s[i] - 'A'] = i;
		}

		for (int i=0; !found && i<s.size() && i<c.size(); i++) {
			if (s[i] == 'A' && c[i] == 'A') {
				continue;
			}

			for (int j=0; j+'A'<c[i]; j++) {
				if (pos[j] != -1 && pos[j] > i) {
					swap(s[i], s[pos[j]]);
					cout << s << endl;
					found = true;
					break;
				}
			}
			if (s[i] > c[i]) {
				if (pos[c[i] - 'A'] != -1 && pos[c[i] - 'A'] > i) {
					swap(s[i], s[pos[c[i] - 'A']]);
					if (lex(s, c)) {
						cout << s << endl;
						found = true;
					}
				}
				break;
			}
		}

		if (!found) {
			cout << "---" << endl;
		}
	}

	return 0;
}
