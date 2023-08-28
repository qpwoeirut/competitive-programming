/*
 * 6b.cpp
 *
 *  Created on: Oct 11, 2019
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

int R, C;
char grid[100][100];
set<char> adj;
char pres;
bool visited[100][100];


int chr[4] = {1, 0, -1, 0};
int chc[4] = {0, 1, 0, -1};
void dfs(int r, int c) {
	if (r < 0 || r >= R || c < 0 || c >= C || grid[r][c] == '.' || visited[r][c]) return;
	visited[r][c] = true;
	adj.I(grid[r][c]);

	if (grid[r][c] != pres) return;

	for (int i=0; i<4; i++) {
		dfs(r + chr[i], c + chc[i]);
	}
}


int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	cin >> R >> C;
	cin >> pres;

	for (int i=0; i<R; i++) {
		for (int j=0; j<C; j++) {
			cin >> grid[i][j];
			visited[i][j] = false;
		}
	}

	for (int i=0; i<R; i++) {
		for (int j=0; j<C; j++) {
			if (!visited[i][j] && grid[i][j] == pres) {
				dfs(i, j);
			}
		}
	}

	adj.erase(pres);
	cout << adj.size() << endl;

	return 0;
}
