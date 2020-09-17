/*
 * 1263d.cpp
 *
 *  Created on: Nov 28, 2019
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

//const ll MOD = 1e9+7; // 998244353;
//const ll INF = 1e18;

int group[26];
vector<set<int> > adj;
void dfs(int node, int cur) {
	group[node] = cur;
	for (set<int>::iterator it=adj[node].B(); it!=adj[node].E(); it++) {
		if (group[*it] == -1) {
			dfs(*it, cur);
		}
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	int N;
	cin >> N;

	bool in[26];
	fill(in, in+26, false);
	adj = vector<set<int> >(26, set<int>());
	string s;
	for (int i=0; i<N; i++) {
		cin >> s;
		for (int j=0; j<s.size(); j++) {
			in[s[j] - 'a'] = true;
			for (int k=j+1; k<s.size(); k++) {
				if (s[j] == s[k]) continue;
				adj[s[j] - 'a'].insert(s[k] - 'a');
				adj[s[k] - 'a'].insert(s[j] - 'a');
			}
		}
	}

	fill(group, group+26, -1);
	for (int i=0; i<26; i++) {
		if (group[i] == -1) {
			dfs(i, i);
		}
	}

	set<int> ct;
	for (int i=0; i<26; i++) {
		if (group[i] != -1 && in[i]) {
			ct.insert(group[i]);
		}
	}
	cout << ct.size() << endl;

	return 0;
}
