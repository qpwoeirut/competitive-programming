/*
 * sort.cpp
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

int N;
int A[MN];

int brute() {
	int ans = 0;
	bool sorted = false;
	while (!sorted) {
		sorted = true;
		for (int i=ans; i+1+ans<N; i++) {
			if (A[i+1] < A[i]) {
				swap(A[i], A[i+1]);
			}
		}
		for (int i=N-2-ans; i>=ans; i--) {
			if (A[i+1] < A[i]) {
				swap(A[i], A[i+1]);
			}
		}
		for (int i=ans; i+1+ans<N; i++) {
			if (A[i+1] < A[i]) {
				sorted = false;
				break;
			}
		}
		ans++;
	}

	return ans;
}
//int tar[MN];
//int apos[MN], tpos[MN];
//map<int,pii> range;
int main() {
	setIO("sort");

//	range.clear();
	cin >> N;

	for (int i=0; i<N; i++) {
		cin >> A[i];
//		tar[i] = A[i];
//		range[tar[i]] = pii(N, 0);
	}
//	sort(tar, tar+N);
//	for (int i=0; i<N; i++) {
//		chmn(range[tar[i]].FI, i);
//		range[tar[i]].SE = 0;
//	}
//	for (int i=0; i<N; i++) {
//		tpos[i] = range[A[i]].FI + range[A[i]].SE++;
//		apos[tpos[i]] = i;
//	}
//	cout << "A:    "; PRS(A, N); cout << endl;
//	cout << "tar:  "; PRS(tar, N); cout << endl;
//	cout << "tpos: "; PRS(tpos, N); cout << endl;

	cout << brute() << endl;

	return 0;
}
