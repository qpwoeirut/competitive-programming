/*
 * pump.cpp
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
#define PISET(A) for (set<int>::iterator it=A.B(); it!=A.E(); it++) cout << *it << " ";
#define PSSET(A) for (set<string>::iterator it=A.B(); it!=A.E(); it++) cout << *it << " ";

typedef long long ll;
typedef pair<int,bool> pib;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;

const int MAXN = 1001;
const ll INIT = 1e18;

struct Pipe {
	int u, v;
	int flow;
	int cost;

	Pipe(int a, int b, int c, int d) {
		u = a;
		v = b;
		cost = c;
		flow = d;
	}

	void print() {
		cout << u << " " << v << " " << cost << " " << flow << endl;
	}
};
void print(const Pipe& p) {
	cout << p.u << " " << p.v << " " << p.cost << " " << p.flow << endl;
}

struct comp_pipe {
	inline bool operator() (const Pipe& a, const Pipe& b) {
		return a.flow > b.flow;
	}
};

struct comp_second {
	inline bool operator() (const pii& a, const pii& b) {
		return a.second > b.second;
	}
};

int N, M;
ll dist[MAXN];

vector<multiset<Pipe, comp_pipe> > adj;
ll dijkstra(int mnf) {
//	cout << "\n\nmnf:" << mnf << endl;
	fill(dist, dist+N, INIT);
	priority_queue<pii, vector<pii>, comp_second> pq;
	pq.push(MP(0, 0));
	dist[0] = 0;

	while (pq.size() > 0) {
		pii cur = pq.top();
		pq.pop();
//		cout << cur.first << " " << cur.second << endl;

		for (multiset<Pipe, comp_pipe>::iterator it=adj[cur.first].begin(); it!=adj[cur.first].end(); it++) {
//			print(*it);
			if (it->flow < mnf) break;
			if (dist[it->v] > dist[cur.first] + it->cost) {
				dist[it->v] = dist[cur.first] + it->cost;
				pq.push(MP(it->v, dist[it->v]));
			}
		}
	}

	return dist[N-1];
}

int main() {
	ifstream fin("pump.in");
	ofstream fout("pump.out");

	fin >> N >> M;

	adj = vector<multiset<Pipe, comp_pipe> >(N, multiset<Pipe, comp_pipe>());
	int mxf = 0;
	int mnf = MAXN;
	int u, v, c, f;
	for (int i=0; i<M; i++) {
		fin >> u >> v >> c >> f;
		u--; v--;
		adj[u].insert(Pipe(u, v, c, f));
		adj[v].insert(Pipe(v, u, c, f));
		mxf = max(mxf, f);
		mnf = min(mnf, f);
	}
//	for (int i=0; i<adj.size(); i++) {
//		for (multiset<Pipe, comp_pipe>::iterator it=adj[i].begin(); it!=adj[i].end(); it++) {
//			print(*it);
//		}
//		cout <<endl;
//	}
//	cout << endl;

	ll best = 0;
	for (ll i=mnf; i<=mxf; i++) {
		ll cost = dijkstra(i);
		if (cost == INIT) break;
//		cout << "f,c: " << i << " " << cost << endl;
		ll flow = i * 1e6;
		best = max(best, flow/cost);
	}

	fout << best << endl;
//	cout << best << endl;

	return 0;
}
