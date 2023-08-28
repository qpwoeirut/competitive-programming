/*
 * 1263e.cpp
 *
 *  Created on: Nov 28, 2019
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

#define LB lower_bound
#define UB upper_bound

#define PRS(A, N) for (int i=0; i<N; i++) cout << A[i] << " ";
#define PRL(A, N) for (int i=0; i<N; i++) cout << A[i] << endl;
#define PISET(A) for (set<int>::iterator it=A.B(); it!=A.E(); it++) cout << *it << " ";
#define PSSET(A) for (set<string>::iterator it=A.B(); it!=A.E(); it++) cout << *it << " ";

typedef long long ll;
typedef unsigned long long ull;
typedef pair<int,bool> pib;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;

typedef map<int,int> mii;
typedef map<ll,ll> mll;
typedef map<char, int> mci;
typedef map<string,int> msi;

ll gcd(ll a, ll b) {return b ? gcd(b, a%b) : a;}

//const ll MOD = 1e9+7; // 998244353;
//const ll INF = 1e18;

struct Node {
	int sum;
	int pref;

	Node() {}
	Node(int a, int b) {
		sum = a;
		pref = b;
	}
};

int N;
Node tree[4000005];
void update(int cur, int lo, int hi, int idx, int value) {
	if (lo == hi) {
		tree[cur].sum = value;
		tree[cur].pref = value;
	}
	else {

		int mid = (lo + hi) / 2;

		if (idx <= mid) update(2 * cur + 1, lo, mid, idx, value);
		else update(2 * cur + 2, mid + 1, hi, idx, value);

		tree[cur].sum = tree[2 * cur + 1].sum + tree[2 * cur + 2].sum;
		tree[cur].pref = max(tree[2 * cur + 1].pref,
							 tree[2 * cur + 1].sum + tree[2 * cur + 2].pref);
	}
}

int get_sum(int cur, int start, int end) {
	if (0 <= start && end <= N-1) {
		return tree[cur].sum;
	}
	int mid = (start + end) / 2;
	return get_sum(2 * cur + 1, start, mid) + get_sum(2 * cur + 2, mid+1, end);
}
Node max_sum(int cur, int lo, int hi) {
	if (0 <= lo && hi <= N-1) {
		return tree[cur];
	}
	int mid = (lo + hi) / 2;
	Node right = max_sum(2 * cur + 2, mid+1, hi);
	Node left = max_sum(2 * cur + 1, lo, mid);

	return Node(left.sum + right.sum, max(left.pref, left.sum + right.pref));
}
Node min_sum(int cur, int lo, int hi) {
	if (0 <= lo && hi <= N-1) {
		return tree[cur];
	}
	int mid = (lo + hi) / 2;
	Node right = min_sum(2 * cur + 2, mid+1, hi);
	Node left = min_sum(2 * cur + 1, lo, mid);

	return Node(left.sum + right.sum, min(left.pref, left.sum + right.pref));
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	cin >> N;

	string cmd;
	cin >> cmd;

	int cur = 0;
	int line[1000005];
	for (int i=0; i<cmd.size(); i++) {
		if (cmd[i] == 'L') {
			cur = max(0, cur-1);
		}
		else if (cmd[i] == 'R') {
			cur++;
		}
		else if (cmd[i] == '(') {
			int ch = 1 - line[cur];
			line[cur] = 1;
			update(0, 0, N-1, cur+1, ch);
		}
		else if (cmd[i] == ')') {
			int ch = -1 - line[cur];
			line[cur] = -1;
			update(0, 0, N-1, cur+1, ch);
		}
		else {
			int ch = -line[cur];
			line[cur] = 0;
			update(0, 0, N-1, cur+1, ch);
		}

		int total = get_sum(0, 0, N-1);
		Node mx = max_sum(0, 0, N-1);
		Node mn = min_sum(0, 0, N-1);

		PRS(line, N);
		cout << endl;
		cout << total << " " << mn.pref << " " << mx.pref << endl << endl;
//		if (total != 0 || mn.pref < 0) {
//			cout << -1 << " ";
//		}
//		else {
//			cout << mx.pref << " ";
//		}
	}
	cout << endl;

	return 0;
}
// -1 -1 -1 -1 -1 -1 1 1 -1 -1 -1
// -1 -1 -1 -1 -1 -1 1 1 -1 -1  2
