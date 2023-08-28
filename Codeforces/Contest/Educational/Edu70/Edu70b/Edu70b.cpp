/*
 * Edu70b.cpp
 *
 *  Created on: Aug 7, 2019
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

#define PB push_back
#define F first
#define S second
#define B begin
#define E end

#define SZ(A) ((int)(A).size());
#define SORT(A) sort(A.begin(), A.end());
#define REV(A) reverse(A.begin(), A.end());

#define PR(a) cout << a << " ";
#define PR1(a) cout << a << endl;
#define PR2(a,b) cout << a << " " << b << endl;
#define PR3(a,b,c) cout << a << " " << b << " " << c << endl;
#define PR4(a,b,c,d) cout << a << " " << b << " " << c << " " << d << endl;

typedef long long ll;
typedef unsigned long long ull;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;

int dist(int val, int tar, int a, int b) {
	if (val == tar) return 0;
	if ((a == 0 && b == 0) || (((a & 1) == 0) && ((b & 1) == 0) && (10+val-tar) % 2 == 1)) return -1;
	bool v[10] = {};
	queue<pii> q;
	v[val] = true;
	q.push(MP(val, 0));

	pii cur;
	while (q.size() > 0) {
		cur = q.front();
		q.pop();

		if (cur.first == tar) {
			return cur.second - 1;
		}

		if (v[(cur.first + a) % 10] == false) {
			v[(cur.first + a) % 10] = true;
			q.push(MP((cur.first + a) % 10, cur.second + 1));
		}
		if (v[(cur.first + b) % 10] == false) {
			v[(cur.first + b) % 10] = true;
			q.push(MP((cur.first + b) % 10, cur.second + 1));
		}
	}

	return -1;
}

string s;
int ct(int x, int y) {
	int add = 0;
	int tmp;
	for (int i=1; i<s.size(); i++) {
		tmp = dist(s[i-1] - '0', s[i] - '0', x, y);
		if (tmp == -1) return -1;
		add += tmp;
	}

	return add;
}

int main() {
	cin >> s;
	for (int i=0; i<10; i++) {
		for (int j=0; j<10; j++) {
			cout << ct(i, j) << " ";
		}
		cout << endl;
	}

	return 0;
}
