/*
 * 7b.cpp
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

int Q, N;
ll mem[100];
ll ids = 1;
ll INIT = 1e12;
void defrag() {
	int idx = 0;
	for (int i=0; i<N; i++) {
		if (mem[i] != INIT) {
			mem[idx] = mem[i];
			idx++;
		}
	}
	for (; idx<N; idx++) {
		mem[idx] = INIT;
	}
}

void alloc() {
	int val;
	cin >> val;

	int start = 0;
	bool success = false;
	for (int i=0; i<N; i++) {
		if (mem[i] != INIT) {
			start = i+1;
		}
		else if (i - start + 1 >= val) {
			for (int j=0; j<val; j++) {
				mem[start+j] = ids;
			}
			success = true;
			break;
		}
	}
	if (success) {
		cout << ids << endl;
		ids++;
	}
	else {
		cout << "NULL" << endl;
	}
}

void erase() {
	int id;
	cin >> id;

	bool found = false;
	for (int i=0; i<N; i++) {
		if (mem[i] == id) {
			mem[i] = INIT;
			found = true;
		}
	}

	if (!found) {
		cout << "ILLEGAL_ERASE_ARGUMENT" << endl;
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	cin >> Q >> N;
	for (int i=0; i<N; i++) {
		mem[i] = INIT;
	}

	string op;
	for (int i=0; i<Q; i++) {
		cin >> op;
		if (op == "defragment") {
			defrag();
		}
		else if (op == "alloc") {
			alloc();
		}
		else {
			erase();
		}
	}

	return 0;
}