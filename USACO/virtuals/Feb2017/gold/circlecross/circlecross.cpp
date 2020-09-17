/*
 * circlecross.cpp
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
const int MAXN = 50001;

int pos[MAXN];
struct comp_fp {
	const inline bool operator() (const int& a, const int& b) {
		return pos[a] < pos[b];
	}
};

inline const bool comp_pos(const int& a, const int& b) {
	return pos[a] < pos[b];
}

int main() {
	assert(MAXN != -1);
	ifstream fin("circlecross.in");
	ofstream fout("circlecross.out");

	int N;
	fin >> N;

	int cir[MAXN*2];
	for (int i=0; i<N*2; i++) {
		fin >> cir[i];
		cir[i]--;
	}

	int ans = 0;
	set<int> active;
	deque<int> pairs;
	for (int i=0; i<N*2; i++) {

		set<int>::iterator it = active.find(cir[i]);
		if (it == active.end()) {
			active.insert(cir[i]);
			pos[cir[i]] = i;
		}
		else {
			active.erase(it);
			deque<int>::iterator pit = LB(pairs.BE(), pairs.EN(), pos[cir[i]]);
			ans += (i - pos[cir[i]] - 1) - (2 * int(pairs.end() - pit));
			pairs.insert(pit, pos[cir[i]]);
		}
//		cout << string(10, '-') << i << " " << ans << string(10, '-') << endl;
//		PSISET(active); cout << endl;
//		PRS(pairs, pairs.size()); cout << endl << endl;
	}

	assert((ans % 2) == 0);
	ans /= 2;
	fout << ans << endl;
	cout << ans << endl;

	return 0;
}

