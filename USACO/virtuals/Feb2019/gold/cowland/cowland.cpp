/*
 * cowland.cpp
 *
 *  Created on: Mar 27, 2020
 *      Author: Stanley
 */


#include <fstream>
#include <iostream>
#include <algorithm>
#include <cassert>
#include <cctype>
#include <climits>
#include <cmath>
#include <cstdlib>
#include <iomanip>
#include <utility>
#include <bitset>
#include <deque>
#include <map>
#include <queue>
#include <string>
#include <set>
#include <vector>

using namespace std;

#define PF push_front
#define PB push_back
#define INS insert

#define FI first
#define SE second
#define BE begin
#define EN end

#define LB lower_bound
#define UB upper_bound

#define PRS(A, N) for (int i=0; i<N; i++) cout << A[i] << " ";
#define PRL(A, N) for (int i=0; i<N; i++) cout << A[i] << endl;
#define PSPR(A, N) for (int i=0; i<N; i++) cout << A[i].FI << "," << A[i].SE << " ";
#define PLPR(A, N) for (int i=0; i<N; i++) cout << A[i].FI << "," << A[i].SE << endl;
#define PSISET(A) for (set<int>::iterator it=A.BE(); it!=A.EN(); it++) cout << *it << " ";
#define PSSSET(A) for (set<string>::iterator it=A.BE(); it!=A.EN(); it++) cout << *it << " ";
#define PLISET(A) for (set<int>::iterator it=A.BE(); it!=A.EN(); it++) cout << *it << endl;
#define PLSSET(A) for (set<string>::iterator it=A.BE(); it!=A.EN(); it++) cout << *it << endl;

typedef long long ll;
typedef unsigned long long ull;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
typedef pair<int,bool> pib;
typedef pair<ll,bool> plb;
typedef vector<set<int> > vsi;
typedef vector<vector<int> > vvi;
typedef vector<set<pii> > vspi;
typedef vector<vector<pii> > vvpi;
typedef map<int,int> mii;
typedef map<ll,ll> mll;
typedef map<char, int> mci;
typedef map<string,int> msi;
typedef map<string,string> mss;

template <class T1, class T2> struct cmpf {
	bool rev;
	inline bool operator() (const pair<T1,T2>& a, const pair<T1,T2>& b) const {return (a.FI<b.FI)^rev;}
	cmpf(bool b=false) {rev=b;}
};
template <class T1, class T2> struct cmps {
	bool rev;
	inline bool operator() (const pair<T1,T2>& a, const pair<T1,T2>& b) const {return (a.SE<b.SE)^rev;}
	cmps(bool b=false) {rev=b;}
};

void setIO(const string& name) {
    ios_base::sync_with_stdio(0);
	cin.tie(nullptr); cout.tie(nullptr);
    freopen((name+".in").c_str(), "r", stdin);
    freopen((name+".out").c_str(), "w", stdout);
}

void chmn(int& a, const int& b) {if (a>b) a=b;}
void chmn(ll& a, const ll& b) {if (a>b) a=b;}
void chmx(int& a, const int& b) {if (a<b) a=b;}
void chmx(ll& a, const ll& b) {if (a<b) a=b;}

int chr[4] = {-1, 0, 1, 0};
int chc[4] = {0, 1, 0, -1};

const ll MOD = 1e9+7; // 998244353;
const ll INF = 1e18;
const int INIT = 1001001001;
const int MN = 100001;

pii range[MN];
bool is_anc(int a, int b) {
	return range[a].FI <= range[b].FI && range[b].SE <= range[a].SE;
}

vsi adj;
int enjoy[MN];
int parent[MN];
int cur = 0;
void dfs(int node, int par) {
	range[node].FI = cur++;
	parent[node] = par;
	for (set<int>::iterator it=adj[node].begin(); it!=adj[node].end(); it++) {
		if (*it == par) continue;
		dfs(*it, node);
	}
	range[node].SE = cur-1;
}

int query(int x, int y) {
	int ret = 0;
	if (is_anc(x, y)) {
		ret = enjoy[x];
		while (x != y) {
			ret ^= enjoy[y];
			y = parent[y];
		}
		return ret;
	}
	while (!is_anc(y, x)) {
		ret ^= enjoy[y];
		y = parent[y];
	}
	ret ^= enjoy[y];
	while (x != y) {
		ret ^= enjoy[x];
		x = parent[x];
	}
	return ret;
}

int main() {
	setIO("cowland");

	int N, Q;
	cin >> N >> Q;

	for (int i=0; i<N; i++) {
		cin >> enjoy[i];
	}

	adj = vsi(N, set<int>());
	int u, v;
	for (int i=0; i<N-1; i++) {
		cin >> u >> v;
		u--; v--;
		adj[u].insert(v);
		adj[v].insert(u);
	}
	dfs(0, -1);

	int t, x, y;
	for (int i=0; i<Q; i++) {
		cin >> t >> x >> y;
		x--;
		if (t == 1) {
			enjoy[x] = y;
		}
		else {
			y--;
			cout << query(x, y) << endl;
		}
	}

	return 0;
}
