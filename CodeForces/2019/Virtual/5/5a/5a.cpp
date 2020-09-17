/*
 * 5a.cpp
 *
 *  Created on: Aug 31, 2019
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

#define PRS(A) for (int i=0; i<SZ(A); i++) cout << A[i] << " ";
#define PRL(A) for (int i=0; i<SZ(A); i++) cout << A[i] << endl;

typedef long long ll;
typedef unsigned long long ull;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;

typedef map<int,int> mii;
typedef map<ll,ll> mll;
typedef map<string,int> msi;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	set<string> users;
	string cmd;
	int traffic = 0;
	while (getline(cin, cmd)) {
		if (cmd[0] == '+') {
			users.insert(cmd.substr(1));
		}
		else if (cmd[0] == '-') {
			users.erase(cmd.substr(1));
		}
		else {
			traffic += (cmd.size() - cmd.find(':') - 1) * users.size();
		}
	}

	cout << traffic << endl;

	return 0;
}
