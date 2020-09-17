/*
 * 6d.cpp
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

int N, a, b;
vector<int> ord, ans;
void shots(int arr[]) {
//	cout << ord.back() << ": ";
//	PRS(arr, N);
//	cout << endl;
	for (int i=1; i<N-1; i++) {
		if (arr[i] >= 0) {
//			cout << i << " " << arr[i] << endl;
			arr[i-1] -= b;
			arr[i] -= a;
			arr[i+1] -= b;
			ord.PB(i);
			shots(arr);

			arr[i-1] += b;
			arr[i] += a;
			arr[i+1] += b;
			ord.pop_back();


			if (i+1 < N-1 && (arr[i+1] >= 0 || arr[i+2] >= 0)) {
				arr[i] -= b;
				arr[i+1] -= a;
				arr[i+2] -= b;

				ord.PB(i+1);
				shots(arr);

				arr[i] += b;
				arr[i+1] += a;
				arr[i+2] += b;

				ord.pop_back();
			}

			return;
		}
	}

//	PRS(ord, ord.size());
//	cout << endl;
	if (ans.size() > ord.size()) {
		ans = ord;
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	cin >> N >> a >> b;

	int arr[10];
	for (int i=0; i<N; i++) {
		cin >> arr[i];
	}

	ord = vector<int>();
	while (arr[0] >= 0) {
		arr[0] -= b;
		arr[1] -= a;
		arr[2] -= b;
		ord.PB(1);
	}

	while (arr[N-1] >= 0) {
		arr[N-1] -= b;
		arr[N-2] -= a;
		arr[N-3] -= b;
		ord.PB(N-2);
	}

	ans = vector<int> (2000);
	shots(arr);

	cout << ans.size() << endl;
	for (int i=0; i<ans.size(); i++) {
		cout << ans[i]+1 << " ";
	}
	cout << endl;


	return 0;
}
