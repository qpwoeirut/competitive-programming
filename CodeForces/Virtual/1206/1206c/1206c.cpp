/*
 * 1206c.cpp
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

int main() {
	int N;
	cin >> N;

	if ((N % 2)== 0) {
		cout << "NO" << endl;
		return 0;
	}

	int seq[200002];
	int num = 1;
	for (int i=0; i<N; i++, num+=2) {
		if ((i % 2) == 0) {
			seq[i] = num;
			seq[i+N] = num+1;
		}
		else {
			seq[i] = num+1;
			seq[i+N] = num;
		}
	}

	cout << "YES" << endl;
	for (int i=0; i<2*N; i++) {
		cout << seq[i] << " ";
	}
	cout << endl;

	return 0;
}
