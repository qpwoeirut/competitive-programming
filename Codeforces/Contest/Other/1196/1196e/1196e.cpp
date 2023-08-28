/*
 * 1196e.cpp
 *
 *  Created on: Jul 24, 2019
 *      Author: Stanley
 */

#include <iostream>
#include <algorithm>
#include <queue>
#include <set>

using namespace std;

typedef long long LL;

void solve() {
	LL B, W;
	cin >> B >> W;

	if (max(B, W) > 1 + (min(B, W) * 3)) {
		cout << "NO" << endl;
		return;
	}

	set<pair<int, int> > wv, bv;
	queue<pair<int,int> > w, b;
	if (W >= B) {
		w.push(make_pair(10000000, 10000000));
		wv.insert(w.front());
	}
	else {
		b.push(make_pair(10000000, 10000001));
		bv.insert(b.front());
	}

	int r, c;
	while ((w.size() > 0 || b.size() > 0) && (wv.size() < W || bv.size() < B)) {
		if (w.size() > 0) {
			r = w.front().first;
			c = w.front().second;
			cout << r << " " << c << endl;
			w.pop();

			if (bv.size() < B && bv.find(make_pair(r+1, c)) == bv.end()) {
				bv.insert(make_pair(r+1, c));
				b.push(make_pair(r+1, c));
			}
			if (bv.size() < B && bv.find(make_pair(r, c+1)) == bv.end()) {
				bv.insert(make_pair(r, c+1));
				b.push(make_pair(r, c+1));
			}
			if (bv.size() < B && bv.find(make_pair(r-1, c)) == bv.end()) {
				bv.insert(make_pair(r-1, c));
				b.push(make_pair(r-1, c));
			}
			if (bv.size() < B && bv.find(make_pair(r, c-1)) == bv.end()) {
				bv.insert(make_pair(r, c-1));
				b.push(make_pair(r, c-1));
			}
		}
		else {
			r = b.front().first;
			c = b.front().second;
			cout << r << " " << c << endl;
			b.pop();

			if (wv.size() < W && wv.find(make_pair(r+1, c)) == wv.end()) {
				wv.insert(make_pair(r+1, c));
				w.push(make_pair(r+1, c));
			}
			if (wv.size() < W && wv.find(make_pair(r, c+1)) == wv.end()) {
				wv.insert(make_pair(r, c+1));
				w.push(make_pair(r, c+1));
			}
			if (wv.size() < W && wv.find(make_pair(r-1, c)) == wv.end()) {
				wv.insert(make_pair(r-1, c));
				w.push(make_pair(r-1, c));
			}
			if (wv.size() < W && wv.find(make_pair(r, c-1)) == wv.end()) {
				wv.insert(make_pair(r, c-1));
				w.push(make_pair(r, c-1));
			}
		}
	}

	cout << wv.size() << " " << bv.size() << endl;
	if (wv.size() < W || bv.size() < B) {
		cout << "NO" << endl;
		return;
	}

	cout << "YES" << endl;
	for (set<pair<int,int> >::iterator it=wv.begin(); it!=wv.end(); it++) {
		cout << it->first << " " << it->second << endl;
	}
	for (set<pair<int,int> >::iterator it=bv.begin(); it!=bv.end(); it++) {
		cout << it->first << " " << it->second << endl;
	}
}

int main() {
	int T;
	cin >> T;
	while (T > 0) {
		T--;
		solve();
	}

	return 0;
}
