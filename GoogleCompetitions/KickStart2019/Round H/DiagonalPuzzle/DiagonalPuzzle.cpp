/*
 * DiagonalPuzzle.cpp
 *
 *  Created on: Nov 16, 2019
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

struct Item {
	bool dl[200];
	bool dr[200];
	bool grid[101][101];
};

void solve(int cnum) {
	int N;
	cin >> N;

	bool grid[101][101];
	char tmp;
	for (int i=0; i<N; i++) {
		for (int j=0; j<N; j++) {
			cin >> tmp;
			grid[i][j] = tmp == '.';
		}
	}


//	cout << "Case #" << cnum << ": " << moves << endl;
}

int main() {
	int T;
	cin >> T;

	for (int i=0; i<T; i++) {
		solve(i+1);
	}


	return 0;
}
