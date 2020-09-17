/*
 * 3c.cpp
 *
 *  Created on: Aug 17, 2019
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

char grid[3][3];
char check() {
	char ret = '.';
	int r = 0, c = 0;
	for (int i=0; i<3; i++) {
		if (grid[i][0] == grid[i][1] && grid[i][1] == grid[i][2] && grid[i][2] != '.') {
			ret = grid[i][2];
			r++;
		}
		if (grid[0][i] == grid[1][i] && grid[1][i] == grid[2][i] && grid[2][i] != '.') {
			ret = grid[2][i];
			c++;
		}
	}
	if (r > 1 || c > 1) {
		return '!';
	}
	if (r == 1 || c == 1) {
		return ret;
	}

	if (grid[0][0] == grid[1][1] && grid[1][1] == grid[2][2] && grid[2][2] != '.') {
		return grid[2][2];
	}
	if (grid[0][2] == grid[1][1] && grid[1][1] == grid[2][0] && grid[2][0] != '.') {
		return grid[2][0];
	}

	return ret;
}

int main() {
	int X = 0, O = 0;
	for (int i=0; i<3; i++) {
		for (int j=0; j<3; j++) {
			cin >> grid[i][j];
			if (grid[i][j] == 'X') {
				X++;
			}
			else if (grid[i][j] == '0') {
				O++;
			}
		}
	}
	if (X < O || O+1 < X) {
		cout << "illegal" << endl;
		return 0;
	}

	char res = check();
	if (res == '!') {
		cout << "illegal" << endl;
		return 0;
	}
	if (res == 'X') {
		if (X == O) {
			cout << "illegal" << endl;
			return 0;
		}
		cout << "the first player won" << endl;
		return 0;
	}
	if (res == '0') {
		if (X-1 == O) {
			cout << "illegal" << endl;
			return 0;
		}
		cout << "the second player won" << endl;
		return 0;
	}

	if (X + O == 9) {
		cout << "draw" << endl;
		return 0;
	}

	cout << (X <= O ? "first" : "second") << endl;

	return 0;
}
