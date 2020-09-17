/*
 * dishes.cpp
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

bool comp_front(const vector<int>& a, const vector<int>& b) {
	return a[0] < b[0];
}

int N;
int dishes[MN];
bool check(int len) {
	if (len <= 2) {
		return true;
	}
//	cout << "checking: " << len << endl;
	int cur[MN];
	for (int i=0; i<len; i++) {
		cur[i] = dishes[i];
	}
	sort(cur, cur+len);

	deque<vector<int> > stacks;
	int nxt = 0;
	for (int i=0; i<len && nxt<len; i++) {
//		cout << "i: " << i << endl;
		while (stacks.size() > 0 && stacks.front().size() > 0 && nxt<len && stacks.front().back() == cur[nxt]) {
			if (stacks.front().size() == 1) {
				stacks.pop_front();
			}
			else {
				stacks.front().pop_back();
			}
			nxt++;
		}
		if (stacks.empty()) {
			stacks.push_back(vector<int>(1, dishes[i]));
		}
		else if (dishes[i] > stacks.front().back()) {
			if (dishes[i] < stacks.front()[0]) {
//				cout << len << ": 0" << endl;
				return false;
			}
			deque<vector<int> >::iterator it=lower_bound(stacks.begin(), stacks.end(), vector<int>(1, dishes[i]), comp_front);
			if (it == stacks.end()) {
				stacks.push_back(vector<int>());
				stacks.back().push_back(dishes[i]);
			}
			else {
				it->push_back(dishes[i]);
			}
		}
		else {
//			assert(stacks.size() > 0 && stacks[0].size() > 0);
			stacks.front().push_back(dishes[i]);
		}
	}
	while (stacks.size() > 0 && stacks.front().size() > 0 && nxt<len && stacks.front().back() == cur[nxt]) {
		if (stacks.front().size() == 1) {
			stacks.pop_front();
		}
		else {
			stacks.front().pop_back();
		}
		nxt++;
	}

//	cout << len << ": " << (nxt == len) << endl;
	return nxt == len;
}

int main() {
	setIO("dishes");

	cin >> N;

	for (int i=0; i<N; i++) {
		cin >> dishes[i];
	}

	int lo = 0, hi = N;
	while (lo < hi) {
		int mid = (lo + hi + 1) / 2;
		if (check(mid)) {
			lo = mid;
		}
		else {
			hi = mid - 1;
		}
	}

	cout << lo << endl;

	return 0;
}
