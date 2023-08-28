/*
 * 1208d.cpp
 *
 *  Created on: Aug 25, 2019
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
ll a[200001];
int nums[200002];
int* segtree;

inline int get_mid(int s, int e) {return s + (e - s) / 2;}

int get_sum(int ss, int se, int qs, int qe, int si) {
    if (qs <= ss && se <= qe) return segtree[si];
    if (se < qs || ss > qe) return 0;

    int mid = get_mid(ss, se);
    return get_sum(ss, mid, qs, qe, 2*si+1) + get_sum(mid+1, se, qs, qe, 2*si+2);
}

void update(int ss, int se, int i, int ch, int si) {
    if (i < ss || i > se)
        return;

    segtree[si] -= ch;
    nums[i] = 0;
    if (ss != se) {
        int mid = get_mid(ss, se);
        update(ss, mid, i, ch, 2*si + 1);
        update(mid+1, se, i, ch, 2*si + 2);
    }
}

int gen_helper(int ss, int se, int si) {
    if (ss == se) {
        segtree[si] = nums[ss];
        return nums[ss];
    }

    int mid = get_mid(ss, se);
    segtree[si] = gen_helper(ss, mid, si*2+1) + gen_helper(mid+1, se, si*2+2);
    return segtree[si];
}

void gen() {
    segtree = new int[INT_MAX];
    gen_helper(0, N, 0);
}

int find_idx(const int& v) {
	int lo = 0, hi = N+1;
	while (lo < hi) {
		int mid = get_mid(lo, hi);
		int cur = get_sum(0, N, 0, mid, 0);
		if (nums[mid] != 0 && cur - nums[mid] == v) {
			return mid;
		}
		else if (cur > v) {
			hi = mid;
		}
		else {
			lo = mid + 1;
		}
	}

	return lo;
}


int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	cin >> N;

	nums[0] = 0;
	for (int i=0; i<N; i++) {
		cin >> a[i];
		nums[i+1] = i+1;
	}

	gen();
	
	int arr[200001];
	for (int i=N-1; i>=0; i--) {
		int idx = find_idx(a[i]);
		arr[i] = idx;
		update(0, N, idx, nums[idx], 0);
	}

	for (int i=0; i<N; i++) {
		cout << arr[i] << " ";
	}

	return 0;
}
