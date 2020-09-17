/*
 * 1282a.cpp
 *
 *  Created on: Dec 23, 2019
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

const ll MOD = 1e9+7; // 998244353;
const ll INF = 1e18;

void solve() {
	int a, b, c, r;
	cin >> a >> b >> c >> r;

	int L = c-r, R = c+r;
	if (a > b) swap(a, b);

	int ans = 0;
	if (b < L || a > R) {
		ans = 0;
	}
	else if (a <= L && R <= b) {
//		cout << "x1 " << a << " " << b << " " << L << " " << R << endl;
		ans = R - L;
	}
	else if (L <= a && b <= R) {
//		cout << "x2 " << a << " " << b << " " << L << " " << R << endl;
		ans = b - a;
	}
	else if (a <= L && b <= R) {
//		cout << "x3 " << a << " " << b << " " << L << " " << R << endl;
		ans = b - L;
	}
	else if (L <= a && R <= b) {
//		cout << "x4 " << a << " " << b << " " << L << " " << R << endl;
		ans = R - a;
	}

	cout << max(0, (b - a) - ans) << endl;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	int T;
	cin >> T;

	while (T > 0) {
		T--;
		solve();
	}

	return 0;
}
