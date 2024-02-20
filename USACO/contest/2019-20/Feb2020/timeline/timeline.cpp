/*
 * timeline.cpp
 *
 *  Created on: Feb 22, 2020
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
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
typedef vector<set<pii> > vsi;

typedef unsigned long long ull;
typedef pair<int,bool> pib;
typedef pair<ll,bool> plb;
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
template <class T> struct cmps {
	bool rev;
	inline bool operator() (const T& a, const T& b) const {return (a.SE<b.SE)^rev;}
	cmps(bool b=false) {rev=b;}
};

struct comp_se {
	inline const bool operator() (const pii& a, const pii& b) {
		return a.SE > b.SE;
	}
};

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

int main() {
	ifstream fin("timeline.in");
	ofstream fout("timeline.out");

	int N, M, C;
	fin >> N >> M >> C;

	int S[MN];
	int in[MN];
	for (int i=0; i<N; i++) {
		fin >> S[i];
		in[i] = 0;
	}

	vsi adj(N, set<pii>());
	int u, v, d;
	for (int i=0; i<C; i++) {
		fin >> u >> v >> d;
		u--; v--;
		adj[u].insert(pii(v, d));
		in[v]++;
	}

	int dist[MN];
	queue<int> q;
	for (int i=0; i<N; i++) {
		dist[i] = S[i];
		if (in[i] == 0) {
			q.push(i);
		}
	}

	while (q.size() > 0) {
		int cur = q.front();
		q.pop();

		for (set<pii>::iterator it=adj[cur].begin(); it!=adj[cur].end(); it++) {
			chmx(dist[it->FI], dist[cur] + it->SE);
			if (--in[it->FI] == 0) {
				q.push(it->FI);
			}
		}
	}

	PRL(dist, N);
	for (int i=0; i<N; i++) {
		fout << dist[i] << endl;
	}

	return 0;
}

