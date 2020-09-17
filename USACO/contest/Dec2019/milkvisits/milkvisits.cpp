/*
 * milkvisits.cpp
 *
 *  Created on: Dec 15, 2019
 *      Author: Stanley
 */


#include <fstream>
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
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <vector>

using namespace std;

#define MP make_pair
#define LB lower_bound
#define UB upper_bound

#define PRS(A, N) for (int i=0; i<N; i++) cout << A[i] << " ";
#define PRL(A, N) for (int i=0; i<N; i++) cout << A[i] << endl;

typedef long long ll;
typedef pair<int,bool> pib;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
typedef pair<int,set<int> > psi;

struct Item {
	int node;
	set<int> milk;

	Item(int a) {
		node = a;
		milk = set<int>();
	}
	Item(int a, set<int>& s) {
		node = a;
		milk = s;
	}
};

const int MAXN = 100001;

int N, M;
int milk[MAXN];
bool V[MAXN];
vector<set<int> > adj;
bool bfs(int n1, int n2, int fav) {
//	cout << n1 << " " << n2 << " " << fav << endl;
	fill(V, V+N, false);
	if (milk[n1] == fav || milk[n2] == fav) return true;
	queue<Item> q;
	q.push(Item(n1));
	V[n1] = true;
	while (q.size() > 0) {
		Item cur = q.front();
		q.pop();
//		cout << cur.node << " ";

		if (cur.node == n2) {
//			cout << endl;
//			for (set<int>::iterator it=cur.milk.begin(); it!=cur.milk.end(); it++) {
//				cout << *it << " ";
//			}
//			cout << endl << endl;
			return cur.milk.find(fav) != cur.milk.end();
		}

		for (set<int>::iterator it=adj[cur.node].begin(); it!=adj[cur.node].end(); it++) {
			if (V[*it]) continue;
			V[*it] = true;
			Item nxt(*it, cur.milk);
			nxt.milk.insert(milk[*it]);
			q.push(nxt);
		}
	}

	cout << endl;
	return false;
}

int main() {
	ifstream fin("milkvisits.in");
	ofstream fout("milkvisits.out");

	fin >> N >> M;

	for (int i=0; i<N; i++) {
		fin >> milk[i];
	}
	adj = vector<set<int> >(N, set<int>());

	int u, v;
	for (int i=0; i<N-1; i++) {
		fin >> u >> v;
		u--; v--;

		adj[u].insert(v);
		adj[v].insert(u);
	}

	int a, b, c;
	for (int i=0; i<M; i++) {
		fin >> a >> b >> c;
		a--; b--;

		bool ans = bfs(a, b, c);
		fout << ans;
//		cout << ans;
	}
	fout << endl;
//	cout << endl;

	return 0;
}
