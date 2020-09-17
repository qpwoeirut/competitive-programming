/*
 * milkorder.cpp
 *
 *  Created on: Mar 28, 2020
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
const int MN = 100001;

int N, M;
vector<mii> adj;
vector<int> ans, cur;
int in[MN];
bool topo_sort(int x) {
	cur.clear();
	fill(in, in+N, 0);
	for (int i=0; i<N; i++) {
		for (mii::iterator it=adj[i].begin(); it!=adj[i].end(); it++) {
			if (it->second < x) {
				in[it->first]++;
			}
		}
	}
	priority_queue<int, vector<int>, greater<int> > pq;
	for (int i=0; i<N; i++) {
		if (in[i] == 0) {
			pq.push(i);
		}
	}

	while (pq.size() > 0) {
		int node = pq.top();
		pq.pop();
		cur.PB(node+1);

		for (mii::iterator it=adj[node].begin(); it!=adj[node].end(); it++) {
			if (it->second >= x) continue;
			if (--in[it->first] == 0) {
				pq.push(it->first);
			}
		}
	}

//	PRS(cur, cur.size()); cout << endl << endl;
	return cur.size() == N;
}

int main() {
	setIO("milkorder");

	cin >> N >> M;

	adj = vector<mii>(N, mii());
	int ct, tmp, prev;
	for (int i=0; i<M; i++) {
		cin >> ct;
		for (int j=0; j<ct; j++) {
			cin >> tmp;
			tmp--;
			if (j > 0) {
				adj[prev].insert(pii(tmp, i));
			}
			prev = tmp;
		}
	}

	int lo = 0, hi = M;
	while (lo < hi) {
		int mid = (lo + hi + 1) / 2;
//		cout << lo << " " << mid << " " << hi << endl;
		if (topo_sort(mid)) {
			ans = cur;
			lo = mid;
		}
		else {
			hi = mid-1;
		}
	}

	assert(ans.size() == N);
	for (int i=0; i<ans.size(); i++) {
		cout << ans[i];
		if (i+1<N) cout << ' ';
		else cout << endl;
	}

	return 0;
}
