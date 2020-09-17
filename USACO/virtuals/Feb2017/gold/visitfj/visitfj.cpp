/*
 * visitfj.cpp
 *
 *  Created on: Jan 18, 2020
 *      Author: Stanley
 *
 *  Virtual Contest of Feb 2017 Gold Contest
 *  Starting at 11:45am on Jan 18, 2020
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

#include <forward_list>
#include <list>
#include <stack>
#include <unordered_map>
#include <unordered_set>

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
typedef vector<set<int> > vsi;

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

const ll MOD = 1e9+7; // 998244353;
const ll INF = 1e18;
const int INIT = 1001001001;
const int MAXN = 101;

struct Item {
	int r, c;
	ll dist;

	Item(int _r, int _c, ll _dist) {
		r = _r;
		c = _c;
		dist = _dist;
	}
};

struct comp_item {
	const bool operator() (const Item& a, const Item& b) {
		return a.dist > b.dist;
	}
};

ll grid[MAXN][MAXN];
bool vis[MAXN][MAXN];
//int dist[MAXN][MAXN];

int main() {
	ifstream fin("visitfj.in");
	ofstream fout("visitfj.out");

	int N, T;
	fin >> N >> T;

	for (int i=0; i<N; i++) {
		for (int j=0; j<N; j++) {
			fin >> grid[i][j];
			vis[i][j] = false;
//			dist[i][j] = INIT;
		}
	}

	priority_queue<Item, vector<Item>, comp_item> pq;
//	queue<Item> pq;
	pq.push(Item(0, 0, 0));
	vis[0][0] = true;
//	dist[0][0] = 0;

	ll best = INIT;
	while (pq.size() > 0) {
		Item cur = pq.top();
//		Item cur = pq.front();
		pq.pop();
//		cout << cur.r << " " << cur.c << " " << cur.dist << endl;

		if (cur.dist >= best) continue;
		if (cur.r == N-1 && cur.c == N-1) {
			chmn(best, cur.dist);
			continue;
		}

		queue<Item> q;
		q.push(Item(cur.r, cur.c, 0));
		while (q.size() > 0) {
			Item in_cur = q.front();
			q.pop();
			if (in_cur.dist == 3) {
				if (!vis[in_cur.r][in_cur.c]) {
					vis[in_cur.r][in_cur.c] = true;
//				if (dist[in_cur.r][in_cur.c] > cur.dist + (T*3) + grid[in_cur.r][in_cur.c]) {
//					dist[in_cur.r][in_cur.c] = cur.dist + (T*3) + grid[in_cur.r][in_cur.c];
					pq.push(Item(in_cur.r, in_cur.c, cur.dist + (T*3) + grid[in_cur.r][in_cur.c]));
				}
				continue;
			}
			if (in_cur.r == N-1 && in_cur.c == N-1) {
				chmn(best, cur.dist + (T*in_cur.dist));
				continue;
			}
			for (int i=0; i<4; i++) {
				Item nxt(in_cur.r + chr[i], in_cur.c + chc[i], in_cur.dist + 1);
				if (nxt.r < 0 || nxt.r >= N || nxt.c < 0 || nxt.c >= N) continue;
				q.push(nxt);
			}
		}
	}

	fout << best << endl;
	cout << best << endl;
	assert(best < INIT);

	return 0;
}

