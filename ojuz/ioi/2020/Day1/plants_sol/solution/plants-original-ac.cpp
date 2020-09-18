#include<cstdio>
#include<algorithm>
#include<cassert>
#include<set>
#define N_ 251000
#define SZ 262144
#include <vector>
using namespace std;
int n, K, Rank[N_], w[N_], V[N_];
struct Tree {
	int K[SZ + SZ], Mn[SZ + SZ];
	void UDT(int nd) {
		Mn[nd] = min(Mn[nd * 2], Mn[nd * 2 + 1]);
	}
	void init(int nd, int b, int e) {
		K[nd] = 0;
		if (b == e) {
			Mn[nd] = Rank[b] - 1;
			return;
		}
		int m = (b + e) >> 1;
		init(nd * 2, b, m);
		init(nd * 2 + 1, m + 1, e);
		UDT(nd);
	}
	void Add2(int nd, int x) {
		K[nd] += x;
		Mn[nd] += x;
	}
	void Spread(int nd) {
		Add2(nd * 2, K[nd]);
		Add2(nd * 2 + 1, K[nd]);
		K[nd] = 0;
	}
	void Add(int nd, int b, int e, int s, int l, int x) {
		if (s > l)return;
		if (s <= b && e <= l) {
			Add2(nd, x);
			return;
		}
		Spread(nd);
		int m = (b + e) >> 1;
		if (s <= m)Add(nd * 2, b, m, s, l, x);
		if (l > m)Add(nd * 2 + 1, m + 1, e, s, l, x);
		UDT(nd);
	}
	void Put(int nd, int b, int e, int x, int y) {
		if (b == e) {
			Mn[nd] = y;
			return;
		}
		Spread(nd);
		int m = (b + e) >> 1;
		if (x <= m)Put(nd * 2, b, m, x, y);
		else Put(nd * 2 + 1, m + 1, e, x, y);
		UDT(nd);
	}
	int FZ(int nd, int b, int e) {
		if (b == e)return b;
		Spread(nd);
		int m = (b + e) >> 1;
		if (!Mn[nd * 2])return FZ(nd * 2, b, m);
		return FZ(nd * 2 + 1, m + 1, e);
	}
	int FindZero() {
		if (Mn[1])return 0;
		return FZ(1, 1, n);
	}
}IT;
set<int>Set, Good;
void Ins(int a) {
	Set.insert(a);
	auto it = Set.find(a);
	int nxt, prv;
	if (next(it) != Set.end())nxt = *(next(it));
	else nxt = (*Set.begin()) + n;
	if (it != Set.begin())prv = *(prev(it));
	else prv = (*prev(Set.end())) - n;
	if (nxt - a >= K) {
		int t = (nxt - 1) % n + 1;
		Good.insert(t);
	}
	else {
		int t = (nxt - 1) % n + 1;
		if (Good.find(t) != Good.end()) Good.erase(t);
	}
	if (a - prv >= K) {
		Good.insert(a);
	}
}
void Del(int a) {
	auto it = Set.find(a);
	int nxt, prv;
	if (next(it) != Set.end())nxt = *(next(it));
	else nxt = (*Set.begin()) + n;
	if (it != Set.begin())prv = *(prev(it));
	else prv = (*prev(Set.end())) - n;
	Set.erase(a);

	if (Good.find(a) != Good.end())Good.erase(a);

	if (!Set.empty() && nxt - prv >= K) {
		Good.insert((nxt - 1) % n + 1);
	}
}


int BIT[N_];
void Add(int a, int b) {
	while (a < N_) {
		BIT[a] += b;
		a += (a&-a);
	}
}
int Sum(int a) {
	int r = 0;
	while (a) {
		r += BIT[a];
		a -= (a&-a);
	}
	return r;
}

long long Right[N_][20], Left[N_][20], INF = 1e9;

bool RightPath(int a, int b) {
	int d = (b - a + n) % n;
	int i;
	for (i = 17; i >= 0; i--) {
		if (d >= Right[a][i]) {
			d -= Right[a][i];
			a = (a + Right[a][i] - 1) % n + 1;
		}
	}
	if ((b - a + n) % n < K && V[a] <= V[b])return true;
	return false;
}


bool LeftPath(int a, int b) {
	int d = (a - b + n) % n;
	int i;
	for (i = 17; i >= 0; i--) {
		if (d >= Left[a][i]) {
			d -= Left[a][i];
			a = (a - Left[a][i] - 1 + n) % n + 1;
		}
	}
	if ((a - b + n) % n < K && V[a] <= V[b])return true;
	return false;
}

bool Path(int a, int b) {
	return RightPath(a, b) || LeftPath(a, b);
}

int compare_plants(int a, int b) {
	a++;
	b++;
	if (Path(a, b)) return 1;
	else if (Path(b, a)) return -1;
	else return 0;
}

void Do() {
	int i, j;
	for (i = 0; i < N_; i++)BIT[i] = 0;
	for (i = 1; i <= K; i++) {
		Add(V[i], 1);
	}

	for (i = 1; i <= n; i++) {

		int b = V[i] + 1, e = n, mid, r = 0, s = Sum(V[i]);
		while (b <= e) {
			mid = (b + e) >> 1;
			if (Sum(mid) > s) {
				r = mid;
				e = mid - 1;
			}
			else b = mid + 1;
		}
		if (r) {
			r = w[r];
			Right[i][0] = (r - i + n) % n;
		}
		else Right[i][0] = INF;

		Add(V[i], -1);
		Add(V[(i + K - 1) % n + 1], 1);
	}

	for (i = 0; i < N_; i++)BIT[i] = 0;

	for (i = n; i > n - K; i--) {
		Add(V[i], 1);
	}
	for (i = n; i >= 1; i--) {


		int b = V[i] + 1, e = n, mid, r = 0, s = Sum(V[i]);
		while (b <= e) {
			mid = (b + e) >> 1;
			if (Sum(mid) > s) {
				r = mid;
				e = mid - 1;
			}
			else b = mid + 1;
		}
		if (r) {
			r = w[r];
			Left[i][0] = (i - r + n) % n;
		}
		else Left[i][0] = INF;

		Add(V[i], -1);
		Add(V[(i - K + n - 1) % n + 1], 1);
	}
	for (i = 0; i < 18; i++) {
		for (j = 1; j <= n; j++) {
			if (Right[j][i] >= INF) {
				Right[j][i + 1] = INF;
			}
			else {
				int t = (j + Right[j][i] - 1) % n + 1;
				Right[j][i + 1] = min(INF, Right[t][i] + Right[j][i]);
			}
			if (Left[j][i] >= INF) {
				Left[j][i + 1] = INF;
			}
			else {
				int t = (j - Left[j][i] % n - 1 + n) % n + 1;
				Left[j][i + 1] = min(INF, Left[t][i] + Left[j][i]);
			}
		}
	}
}

void init(int k, vector<int> r) {
	n = r.size();
	K = k;
	int i;
	for(i=0; i<n; i++) {
		Rank[i+1] = r[i]+1;
	}
	IT.init(1, 1, n);
	for (i = 1; i <= n; i++) {

		int t;
		while ((t = IT.FindZero())) {
			Ins(t);
			IT.Put(1, 1, n, t, INF);
		}
		assert(!Good.empty());
		int a = *Good.begin();
		w[i] = a;
		V[a] = i;
		IT.Add(1, 1, n, max(a - K + 1, 1), a - 1, -1);
		IT.Add(1, 1, n, a - K + 1 + n, min(a - 1 + n, n), -1);
		Del(a);
	}
	for (i = 1; i <= K; i++) Add(V[i], 1);
	for (i = 1; i <= n; i++) {
		assert(Sum(V[i]) == Rank[i]);
		Add(V[i], -1);
		Add(V[(i + K - 1) % n + 1], 1);
	}
	Do();
}
