/*
 * fcolor.cpp
 *
 *  Created on: Mar 30, 2020
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

void chmn(int& a, const int& b) {if (a>b) a=b;}
void chmn(ll& a, const ll& b) {if (a>b) a=b;}
void chmx(int& a, const int& b) {if (a<b) a=b;}
void chmx(ll& a, const ll& b) {if (a<b) a=b;}

int chr[4] = {-1, 0, 1, 0};
int chc[4] = {0, 1, 0, -1};

void setIO(const string& name) {
    ios_base::sync_with_stdio(0);
	cin.tie(nullptr); cout.tie(nullptr);
    freopen((name+".in").c_str(), "r", stdin);
    freopen((name+".out").c_str(), "w", stdout);
}

const ll MOD = 1e9+7; // 998244353;
const ll INF = 1e18;
const int INIT = 1001001001;
const int MN = 200001;


int par[MN];
int sz[MN];
int adm[MN];
int root(int node) {
	if (par[node] != node) {
		par[node] = root(par[node]);
	}
	return par[node];
}
bool join(int n1, int n2) {
//	cout << "joining: " << n1 << " " << n2 << endl;
	int r1 = root(n1);
	int r2 = root(n2);
	if (r1 == r2) return false;

	if (sz[r1] > sz[r2]) {
		par[r2] = r1;
		sz[r1] += sz[r2];
		adm[r2] = adm[r1];
	}
	else {
		par[r1] = r2;
		sz[r2] += sz[r1];
		adm[r1] = adm[r2];
	}
	return true;
}


int N, M;
vsi adj;
int mark[MN];

int main() {
	setIO("fcolor");

	cin >> N >> M;
	adj = vsi(N, set<int>());
	int u, v;
	for (int i=0; i<M; i++) {
		cin >> u >> v;
		u--; v--;

		adj[u].insert(v);
	}

	for (int i=0; i<N; i++) {
		par[i] = i;
		sz[i] = 1;
		adm[i] = -1;
	}

	bool change = true;
	while (change) {
		change = false;
		for (int i=0; i<N; i++) {
//			cout << i << " " << root(i) << endl;
//			cout << "adj: ";
			for (set<int>::iterator it=adj[i].BE(); it!=adj[i].EN(); it++) {
//				cout << *it << " ";
				if (adm[root(i)] == -1) {
					adm[root(i)] = root(*it);
				}
				else {
					change |= join(adm[root(i)], *it);
				}
			}
//			cout << endl;
//			PRS(adm, N); cout << endl;
//			cout << i << ": ";
//			for (int j=0; j<N; j++) {
//				cout << root(j) << " ";
//			}
//			cout << endl << endl;
		}
	}

	int cur = 1;
	for (int i=0; i<N; i++) {
		if (mark[root(i)] == 0) {
			mark[root(i)] = cur++;
		}
		mark[i] = mark[root(i)];

		cout << mark[i] << endl;
	}

	return 0;
}
