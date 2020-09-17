/*
 * 1260d.cpp
 *
 *  Created on: Nov 27, 2019
 *      Author: Stanley
 */


#include <iostream>
#include <algorithm>
#include <cctype>
#include <climits>
#include <cmath>
#include <cstdlib>
#include <iomanip>
#include <utility>
#include <bitset>
#include <deque>
#include <forward_list>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

#define MP make_pair

#define PF push_front
#define PB push_back
#define I insert

#define F first
#define S second
#define B begin
#define E end

#define SZ(A) ((int)(A).size());
#define SORT(A) sort(A.begin(), A.end());
#define REV(A) reverse(A.begin(), A.end());

#define PRS(A, N) for (int i=0; i<N; i++) cout << A[i] << " ";
#define PRL(A, N) for (int i=0; i<N; i++) cout << A[i] << endl;
#define PRSSET(A) for (set<int>::iterator it=A.B(); it!=A.E(); it++) cout << *it << " ";
#define PRLSET(A) for (set<int>::iterator it=A.B(); it!=A.E(); it++) cout << *it << endl;

typedef long long ll;
typedef unsigned long long ull;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;

typedef map<int,int> mii;
typedef map<ll,ll> mll;
typedef map<char, int> mci;
typedef map<string,int> msi;


struct Point {
	int pos;
	int danger;
	bool is_pos;
	int idx;

	Point(int a, int b, bool c, int d) {
		pos = a;
		danger = b;
		is_pos = c;
		idx = d;
	}

	void print() {
		cout << idx << " " << pos << " " << danger << " " << is_pos << endl;
	}
};

bool comp_pt(const Point& a, const Point& b) {
	return a.pos < b.pos;
}

int S, N, K, T;
int dist(int ts, int te) {
//	cout << "s,e,d: " << ts << " " << te << " " << N + 1 + (2 * (te - ts + 1)) << endl;
	return N + 1 + (2 * (te - ts + 1));
}

deque<Point> pts;
int check(int num) {
	int s = 0, e = 0;
	for (int i=0; i<pts.size(); i++) {
		if (pts[i].danger > num) {
			s = i;
			break;
		}
	}
	for (int i=pts.size()-1; i>=0; i--) {
		if (pts[i].danger > num) {
			e = i;
			break;
		}
	}

	cout << num << ": " << dist(s,e) << endl;
	return dist(s, e);
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	cin >> S >> N >> K >> T;

	mii a;
	int tmp;
	for (int i=0; i<S; i++) {
		cin >> tmp;
		a[tmp]++;
	}

	pts.clear();
	int l, r, d;
	for (int i=0; i<K; i++) {
		cin >> l >> r >> d;
		pts.push_front(Point(l, d, true, i));
		pts.push_back(Point(r, d, false, i));
	}
	sort(pts.begin(), pts.end(), comp_pt);

	int lo = 0, hi = S;
	while (lo < hi) {
		cout << lo << " " << hi << endl;
		int mid = (lo + hi) / 2;

		if (check(mid) > T) {
			lo = mid + 1;
		}
		else {
			hi = mid;
		}
	}

	int ans = 0;
	for (mii::iterator it=a.lower_bound(lo); it!=a.end(); it++) {
		ans += it->second;
	}

	cout << lo << endl;
	cout << ans << endl;

	return 0;
}
