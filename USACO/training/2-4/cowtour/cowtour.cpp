/*
 * cowtour.cpp
 *
 *  Created on: Apr 27, 2020
 *      Author: Stanley
 */


/*
ID: zhongbr1
TASK: cowtour
LANG: C++11
*/

#include <iostream>
#include <algorithm>
#include <cassert>
#include <queue>
#include <set>
#include <string>
#include <vector>
#include <map>
#include <deque>
#include <iomanip>
#include <cmath>

using namespace std;

#define PB push_back
#define INS insert

#define FI first
#define SE second
#define all(obj) begin(obj), end(obj)

typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
typedef vector<set<int> > vsi;
typedef pair<int,bool> pib;

template <class T1,class T2> struct cmpf {
	bool rev;
	inline bool operator()(const pair<T1,T2>& a, const pair<T1,T2>& b) const {return (a.first<b.first)^rev;}
	cmpf(bool b=false) {rev=b;}
};
template <class T1,class T2> struct cmps {
	bool rev;
	inline bool operator()(const pair<T1,T2>& a, const pair<T1,T2>& b) const {return (a.second<b.second)^rev;}
	cmps(bool b=false) {rev=b;}
};

string to_string(const char& c){return string(1, c);}
string to_string(const string& s){return '"'+s+'"';}
string to_string(const bool& b){return (b?"true":"false");}
template <class T1,class T2> string to_string(const pair<T1, T2>& p, const string& sep=",");
template <class T> string to_string(const T& v, const string& sep=" ") {
	bool first = true; string s = "{";
	for (const auto &x: v) {
		if (!first) s += sep;
		else first = false;
		s += to_string(x);
	}
	return s + "}";
}
template <class T> string to_string(const T& v, const int& sz, const string& sep=" ") {
	string s = "[";
	for (int i=0; i<sz; i++) {if (i){s += sep;} s += to_string(v[i]);}
	return s + "]";
}
template <class T1,class T2> string to_string(const pair<T1,T2>& p, const string& sep) {return "(" + to_string(p.first) + sep + to_string(p.second) + ")";}

#define debug(obj) cerr << #obj << ": " << to_string(obj) << endl;
#define debug1(obj, sz) cerr << #obj << ": " << to_string(obj, sz) << endl;
#define debug2(obj, sz1, sz2) cerr << "-----" << #obj << "-----\n"; for (int i=0; i<sz1; i++) cerr << to_string(obj[i], sz2) << " "; cerr << endl;
#define debug3(obj, sz1, sz2, sz3) cerr << "-----" << #obj << "-----\n"; for (int i=0; i<sz1; i++) {for (int j=0; j<sz2; j++) cerr << to_string(obj[i][j], sz3) << " "; cerr << endl;} cerr << endl;

template <class T> void chmn(T& a, const T& b) {if (a>b) a=b;}
template <class T> void chmx(T& a, const T& b) {if (a<b) a=b;}

int chr[4] = {-1, 0, 1, 0};
int chc[4] = {0, 1, 0, -1};

const ll MOD = 1e9+7; // 998244353;
const int INIT = 1001001001;
const int MN = 151;

void setIO(const string& name) {
    ios_base::sync_with_stdio(0);
	cin.tie(nullptr); cout.tie(nullptr);
    freopen((name+".in").c_str(), "r", stdin);
    freopen((name+".out").c_str(), "w", stdout);
}


int N;
pair<double,double> pastures[MN];

double get_dist(const int& a, const int& b) {
	double x = pastures[a].FI - pastures[b].FI;
	double y = pastures[a].SE - pastures[b].SE;
	return sqrt((x*x) + (y*y));
}

double dist[MN][MN];
double mxdist[MN];
int main() {
	setIO("cowtour");

	cin >> N;

	for (int i=0; i<N; i++) {
		cin >> pastures[i].first >> pastures[i].second;
	}

	for (int i=0; i<N; i++) {
		for (int j=0; j<N; j++) {
			char c;
			cin >> c;
			if (c == '1') {
				dist[i][j] = get_dist(i, j);
			}
			else {
				dist[i][j] = INIT;
			}
		}
		dist[i][i] = 0;
	}

	for (int k=0; k<N; k++) {
		for (int i=0; i<N; i++) {
			for (int j=0; j<N; j++) {
				chmn(dist[i][j], dist[i][k] + dist[k][j]);
			}
		}
	}

	for (int i=0; i<N; i++) {
		for (int j=0; j<N; j++) {
			if (dist[i][j] == INIT) {
				dist[i][j] = -1;
			}
//			cerr << dist[i][j] << ' ';
		}
//		cerr << endl;
	}

	double original = 0;
	for (int i=0; i<N; i++) {
		mxdist[i] = -1;
		for (int j=0; j<N; j++) {
			chmx(mxdist[i], dist[i][j]);
		}
		chmx(original, mxdist[i]);
	}

//	debug1(mxdist, N);

	double ans = INIT;
	for (int i=0; i<N; i++) {
		for (int j=i+1; j<N; j++) {
			if (dist[i][j] == -1) {
//				cerr << i << ' ' << j << ' ' << mxdist[i] + get_dist(i, j) + mxdist[j] << endl;
				chmn(ans, mxdist[i] + get_dist(i, j) + mxdist[j]);
			}
		}
	}

	chmx(ans, original);

	cout << fixed << setprecision(6);
	cout << ans << endl;

	return 0;
}
