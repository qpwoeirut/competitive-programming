/*
 * boards.cpp
 *
 *  Created on: Jan 20, 2020
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
const int MP = 100001;

struct Board {
	int r1, c1;
	int r2, c2;
	int dist;

	Board(int a, int b, int c, int d) {
		r1 = a;
		c1 = b;
		r2 = c;
		c2 = d;
		dist = r1 + c1;
	}
	Board() {
		r1 = c1 = r2 = c2 = -1;
		dist = INIT;
	}
};

inline const bool comp_r2(const Board& a, const Board& b) {
	if (a.r2 == b.r2) {
		return a.c2 < b.c2;
	}
	return a.r2 < b.r2;
}

int N, P;
int to_end(const Board& b) {
	return (N - b.r2) + (N - b.c2);
}

int dist_to(const Board& a, const Board& b) {
	return (a.r1 - b.r2) + (a.c1 - b.c2);
}

int main() {
	ifstream fin("boards.in");
	ofstream fout("boards.out");

	fin >> N >> P;

	Board boards[MP];
	int ta, tb, tc, td;
	for (int i=0; i<P; i++) {
		fin >> ta >> tb >> tc >> td;
		boards[i] = Board(ta, tb, tc, td);
	}
	sort(boards, boards+P, comp_r2);

	for (int i=0; i<P; i++) {
		for (int j=0; j<i; j++) {
			if (boards[j].r2 > boards[i].r1) {
				break;
			}
			if (boards[j].c2 > boards[i].c1) {
				continue;
			}

			chmn(boards[i].dist, boards[j].dist + dist_to(boards[i], boards[j]));
		}
	}

	int best = INIT;
	for (int i=0; i<P; i++) {
		chmn(best, boards[i].dist + to_end(boards[i]));
	}

	fout << best << endl;
	cout << best << endl;

	return 0;
}
