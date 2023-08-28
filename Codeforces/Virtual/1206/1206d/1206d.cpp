/*
 * 1206d.cpp
 *
 *  Created on: Aug 18, 2019
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

int N;
ll a[100001];
bool visited[100001];
bool dfs(int cur, int parent) {
	visited[cur] = true;
	for (int i=0; i<N; i++) {
		if (cur != i && (a[cur] & a[i])) {
			if (visited[i] == false) {
				if (dfs(i, cur)) return true;
			}
			else if (i != parent) {

			}
		}
	}
}

int main() {
	cin >> N;

	for (int i=0; i<N; i++) {
		cin >> a[i];
		visited[i] = false;
	}

	return 0;
}
