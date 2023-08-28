/*
 * 1206a.cpp
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
	set<int> a,b;
	int tmp;

	int N, M;
	cin >> N;
	for (int i=0; i<N; i++) {
		cin >> tmp;
		a.insert(tmp);
	}
	cin >> M;
	for (int i=0; i<M; i++) {
		cin >> tmp;
		b.insert(tmp);
	}

	for (set<int>::iterator ai=a.begin(); ai!=a.end(); ai++) {
		for (set<int>::iterator bi=b.begin(); bi!=b.end(); bi++) {
			int cur = *ai + *bi;
			if (a.find(cur) == a.end() && b.find(cur) == b.end()) {
				cout << *ai << " " << *bi << endl;
				return 0;
			}
		}
	}

	return 0;
}
