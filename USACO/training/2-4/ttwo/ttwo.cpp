/*
 * ttwo.cpp
 *
 *  Created on: Apr 27, 2020
 *      Author: Stanley
 */


/*
ID: zhongbr1
TASK: ttwo
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

#define debug(obj) cout << #obj << ": " << to_string(obj) << endl;
#define debug1(obj, sz) cout << #obj << ": " << to_string(obj, sz) << endl;
#define debug2(obj, sz1, sz2) cout << "-----" << #obj << "-----\n"; for (int i=0; i<sz1; i++) cout << to_string(obj[i], sz2) << " "; cout << endl;
#define debug3(obj, sz1, sz2, sz3) cout << "-----" << #obj << "-----\n"; for (int i=0; i<sz1; i++) {for (int j=0; j<sz2; j++) cout << to_string(obj[i][j], sz3) << " "; cout << endl;} cout << endl;

template <class T> void chmn(T& a, const T& b) {if (a>b) a=b;}
template <class T> void chmx(T& a, const T& b) {if (a<b) a=b;}

int chr[4] = {-1, 0, 1, 0};
int chc[4] = {0, 1, 0, -1};

const ll MOD = 1e9+7; // 998244353;
const int INIT = 1001001001;
const int MN = 11;

void setIO(const string& name) {
    ios_base::sync_with_stdio(0);
	cin.tie(nullptr); cout.tie(nullptr);
    freopen((name+".in").c_str(), "r", stdin);
    freopen((name+".out").c_str(), "w", stdout);
}



struct State {
	int r, c;
	int dir;

	State() {
		r = -1;
		c = -1;
		dir = -1;
	}
	State(int _r, int _c, int _dir) {
		r = _r;
		c = _c;
		dir = _dir;
	}

	inline const bool operator==(const State& other) {
		return r == other.r && c == other.c;
	}

	inline void print() {
		cout << r << " " << c << " " << dir << endl;
	}
};

bool V[MN][MN][4][MN][MN][4];
bool visited(const State& cow, const State& fj) {
	bool ret = V[cow.r][cow.c][cow.dir][fj.r][fj.c][fj.dir];
	V[cow.r][cow.c][cow.dir][fj.r][fj.c][fj.dir] = true;
	return ret;
}

string grid[MN];

int N = 10;
bool valid(const State& state) {
	return 0 <= state.r && state.r < N && 0 <= state.c && state.c < N && grid[state.r][state.c] != '*';
}

void move(State& state) {
	State forward(state.r + chr[state.dir], state.c + chc[state.dir], state.dir);
	if (valid(forward)) {
		state = forward;
	}
	else {
		state.dir = (state.dir + 1) % 4;
	}
}

int main() {
	setIO("ttwo");

	State cow, fj;
	for (int i=0; i<N; i++) {
		cin >> grid[i];
		for (int j=0; j<grid[i].size(); j++) {
			if (grid[i][j] == 'C') {
				cow = State(i, j, 0);
			}
			else if (grid[i][j] == 'F') {
				fj = State(i, j, 0);
			}
		}
	}
	assert(cow.dir != -1);
	assert(fj.dir != -1);

	visited(cow, fj);
	int answer = 0;
	for (int i=1; i<=N*N*N*N*16; i++) {
		move(cow);
		move(fj);
//		cow.print();
//		fj.print();

		if (cow == fj) {
			answer = i;
			break;
		}
		if (visited(cow, fj)) {
			break;
		}
	}

	cout << answer << endl;

	return 0;
}
