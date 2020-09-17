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
const int MN = 100001;

int N;
vsi adj;
int mn;
int get_size(int node, int par) {
//	cout << node << " " << par << endl;
	if (adj[node].size() == 1 && *adj[node].begin() == par) return 1;

	vector<int> sizes;
	int sz = 1;
	for (set<int>::iterator it=adj[node].begin(); it!=adj[node].end(); it++) {
		if (*it == par) continue;
		int cur = get_size(*it, node);
		sizes.push_back(cur);
		sz += cur;
	}
	sizes.push_back(N - sz - 1);

	sort(sizes.begin(), sizes.end());

	int L = 0, R = sizes.size() - 1;
	if (sizes.size() & 1) {
		chmn(mn, sizes[R]);
		R--;
	}
	while (L < R) {
		chmn(mn, sizes[L] + sizes[R]);
		L++; R--;
	}

	return sz;
}

int main() {
	ifstream fin("deleg.in");
	ofstream fout("deleg.out");

	fin >> N;

	adj = vsi(N, set<int>());
	int a, b;
	for (int i=0; i<N-1; i++) {
		fin >> a >> b;
		a--; b--;

		adj[a].insert(b);
		adj[b].insert(a);
	}
	int leaf = -1;
	for (int i=0; i<N; i++) {
		if (adj[i].size() == 1) {
			leaf = i;
			break;
		}
	}
	assert(leaf != -1);

	mn = N;
	get_size(leaf, -1);
//	cout << "mn: " << mn << endl;

	string ans(N-1, '0');
	for (int i=1; i<=mn; i++) {
		if ((((N-1) % i) == 0)) {
			ans[i-1] = '1';
		}
	}

//	cout << ans << endl;
	fout << ans << endl;

	return 0;
}
