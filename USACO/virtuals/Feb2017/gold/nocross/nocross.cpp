/*
 * nocross.cpp
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
const int MAXN = 1001;

int N;
int L[MAXN];
int R[MAXN];

int mem[MAXN][MAXN];
int dp(int lidx, int ridx) {
	if (lidx == N || ridx == N) {
		return 0;
	}

	if (mem[lidx][ridx] != -1) {
		return mem[lidx][ridx];
	}

	mem[lidx][ridx] = max(dp(lidx + 1, ridx), dp(lidx, ridx + 1));
	if (abs(L[lidx] - R[ridx]) <= 4) {
		chmx(mem[lidx][ridx], 1 + dp(lidx + 1, ridx + 1));
	}

	return mem[lidx][ridx];
}

int main() {
	ifstream fin("nocross.in");
	ofstream fout("nocross.out");

	fin >> N;

	for (int i=0; i<N; i++) {
		fin >> L[i];
		for (int j=0; j<N; j++) {
			mem[i][j] = -1;
		}
	}
	for (int i=0; i<N; i++) {
		fin >> R[i];
	}

	int ans = dp(0, 0);
	fout << ans << endl;
	cout << ans << endl;


	return 0;
}

