/*
 * maze1.cpp
 *
 *  Created on: Apr 27, 2020
 *      Author: Stanley
 */


/*
ID: zhongbr1
TASK: maze1
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
const int MN = 205;

void setIO(const string& name) {
    ios_base::sync_with_stdio(0);
	cin.tie(nullptr); cout.tie(nullptr);
    freopen((name+".in").c_str(), "r", stdin);
    freopen((name+".out").c_str(), "w", stdout);
}

pii s1, s2;
void update_start(int r, int c) {
	if (s1.first == -1) {
		s1 = pii(r, c);
	}
	else {
		s2 = pii(r, c);
	}
}

struct Item {
	int r, c;
	int dist;

	Item(int _r, int _c, int _dist) {
		r = _r;
		c = _c;
		dist = _dist;
	}
};

int W, H;
char maze[MN][MN];
inline const bool valid(const Item& a) {
	return 0 <= a.r && a.r < H && 0 <= a.c && a.c < W && maze[a.r][a.c] == ' ';
}

int main() {
	setIO("maze1");

	cin >> W >> H;
	W = 2*W + 1;
	H = 2*H + 1;

	cin >> noskipws;
	char newline;
	for (int i=0; i<H; i++) {
		cin >> newline;
		for (int j=0; j<W; j++) {
			cin >> maze[i][j];
		}
//		cin >> newline;
	}

	s1 = pii(-1,-1);
	s2 = pii(-1,-1);
	for (int i=0; i<H; i++) {
		if (maze[i][0] == ' ') {
			update_start(i, 0);
		}
		if (maze[i][W-1] == ' ') {
			update_start(i, W-1);
		}
	}
	for (int i=0; i<W; i++) {
		if (maze[0][i] == ' ') {
			update_start(0, i);
		}
		if (maze[H-1][i] == ' ') {
			update_start(H-1, i);
		}
	}

	int dist[MN][MN];
	for (int i=0; i<H; i++) {
		for (int j=0; j<W; j++) {
			dist[i][j] = INIT;
		}
	}

	queue<Item> q;
	q.push(Item(s1.first, s1.second, 1));
	dist[s1.first][s1.second] = 1;
	q.push(Item(s2.first, s2.second, 1));
	dist[s2.first][s2.second] = 1;

	while (q.size() > 0) {
		Item cur = q.front();
		q.pop();
//		cout << cur.r << " " << cur.c << " " << cur.dist << endl;

		for (int i=0; i<4; i++) {
			Item next(cur.r + chr[i], cur.c + chc[i], cur.dist + 1);
			if (valid(next) && dist[next.r][next.c] > next.dist) {
				dist[next.r][next.c] = next.dist;
				q.push(next);
			}
		}
	}
//	debug(s1);
//	debug(s2);
	int ans = 0;
	for (int i=0; i<H; i++) {
		for (int j=0; j<W; j++) {
//			cout << maze[i][j];
			if (maze[i][j] == ' ') {
				chmx(ans, dist[i][j]);
			}
		}
//		cout << endl;
	}

//	debug2(dist, H, W);

	cout << ans/2 << endl;

	return 0;
}
