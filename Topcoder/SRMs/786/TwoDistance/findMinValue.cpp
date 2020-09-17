/*
 * findMinValue.cpp
 *
 *  Created on: May 15, 2020
 *      Author: Stanley
 */


#include <iostream>
#include <algorithm>
#include <cassert>
#include <queue>
#include <set>
#include <string>
#include <vector>
#include <map>
#include <deque>
#include <cctype>
#include <climits>
#include <cmath>
#include <cstdlib>
#include <iomanip>
#include <utility>
#include <bitset>
#include <stack>

using namespace std;

typedef long long ll;
typedef vector<set<ll> > vsi;
typedef vector<multiset<ll> > vmi;

template <class T> void chmn(T& a, const T& b) {if (a>b) a=b;}
template <class T> void chmx(T& a, const T& b) {if (a<b) a=b;}

class TwoDistance {
private:
	vsi adj;
	vmi two;
	void dfs(int node, int par, const vector<ll>& val) {
		for (set<ll>::iterator it=adj[node].begin(); it!=adj[node].end(); it++) {
			if (*it != par) {
				if (par >= 0) {
					for (set<ll>::iterator iter=adj[par].begin(); iter!=adj[par].end(); iter++) {
						if (*iter != node) {
							two[*it].insert(val[*iter]);
							two[val[*iter]].insert(*it);
						}
					}
				}
				dfs(*it, node, val);
			}
		}
	}
public:
	TwoDistance() {

	}
	long long findMinValue(int N, vector<ll> E, vector<ll> V, int D, int seed) {
		ll X = 1103515245;
		ll Y = 12345;
		ll MOD = 2147483648;
		ll A[400005];
		A[0] = seed;
		for (int i=1; i<2*N; i++) {
			A[i] = (A[i-1] * X + Y) % MOD;
		}
		ll tmp = V.size();
		V.resize(N);
		for (int i=tmp; i<N; i++) {
			V[i] = A[i];
		}

		tmp = E.size();
		E.resize(N);
		for (int i=tmp; i<N; i++) {
			E[i] = A[N+i] % min(i, D);
		}

		adj = vsi(N, set<ll>());
		for (int i=1; i<N; i++) {
			adj[i].insert(E[i]);
			adj[E[i]].insert(i);
		}

		two = vmi(N, multiset<ll>());
		dfs(0, -1, V);

		ll cost = 0;
		for (int i=0; i<N; i++) {
			if (two[i].size() < 2) continue;
			ll best = 1001001001;
			ll prev = -1001001001;
			for (multiset<ll>::iterator it=two[i].begin(); it!=two[i].end(); it++) {
				chmn(best, abs(*it - prev));
				prev = *it;
			}
			cost += best;
		}

		return cost;
	}
};

int main() {
	TwoDistance* obj = new TwoDistance();
	int arr[100] = {-1,0,1};
	int arr2[5] = {1,2,3,4,5};
	vector<ll> v(arr, arr+1);
	vector<ll> v2(arr2, arr2+5);
//	cout << obj->findMinValue(3, v, vector<ll>(), 3, 2) << endl;
	cout << obj->findMinValue(5, v, v2, 3, 4) << endl;

	return 0;
}

#undef debug3
#undef debug2
#undef debug1
#undef debug

#undef UB
#undef LB

#undef rall
#undef all
#undef SE
#undef FI

#undef INS
#undef PB
#undef PF
