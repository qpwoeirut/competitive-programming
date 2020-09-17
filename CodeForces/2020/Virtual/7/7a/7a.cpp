/*
 * 7a.cpp
 *
 *  Created on: Oct 12, 2019
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

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	bool board[8][8];
	char c;
	for (int i=0; i<8; i++) {
		for (int j=0; j<8; j++) {
			cin >> c;
			board[i][j] = (c == 'B');
		}
	}

	int rows = 0, cols = 0;
	bool cr, cc;
	for (int i=0; i<8; i++) {
		cr = true;
		cc = true;
		for (int j=0; j<8; j++) {
			cr &= board[i][j];
			cc &= board[j][i];
		}

		if (cr) rows++;
		if (cc) cols++;
	}

	if (rows == 8 && cols == 8) {
		cout << 8 << endl;
	}
	else {
		cout << rows+cols << endl;
	}

	return 0;
}
