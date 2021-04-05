#include <iostream>
 
using namespace std;
 
#define MAXN 3010
#define ll long long
#define MOD 1000000007ll
#define INV 500000004
 
int n, m, k, q;
int bstart, stsize;
int norm[MAXN][MAXN * 2];
int sqs[MAXN][MAXN * 2];
 
void upd(int ind, int *c, ll val) {
	ind += bstart;
	c[ind] += val;
	c[ind] %= MOD;
	while (ind >= 0) {
		ind = (ind - 1) / 2;
		c[ind] = (c[ind * 2 + 1] + c[ind * 2 + 2] + MOD) % MOD;
		if (ind == 0) break;
	}
}
 
void updbit(int r, int c, int v, bool dsq) {
	while (r <= n) {
		upd(c - 1, dsq ? sqs[r] : norm[r], v);
		r += (r & (-r));
	}
}
 
ll query(int c, int cmin, int cmax, int maxb, int *uwu) {
	if (cmin > maxb) return 0;
	if (cmax <= maxb) return uwu[c];
	return (query(c*2+1, cmin, (cmin+cmax)/2, maxb, uwu) +
			query(c*2+2, 1+(cmin+cmax)/2, cmax, maxb, uwu) + MOD) % MOD;
}
 
ll query(int r, int c, bool dsq) {
	ll res = 0;
	while (r > 0) {
		res += query(0, 0, bstart, c - 1, dsq ? sqs[r] : norm[r]);
		res %= MOD;
		r -= (r & (-r));
	}
	return res;
}
 
ll getrange(ll r1, ll c1, ll r2, ll c2, bool dsq) {
	ll res = query(r2, c2, dsq) - query(r1 - 1, c2, dsq) - query(r2, c1 - 1, dsq) + query(r1 - 1, c1 - 1, dsq);
	return (res + MOD * 5) % MOD;
}
 
int main() {
 
	scanf(" %d%d%d", &n, &m, &k);
 
	bstart = 1;
	while (bstart < n) bstart *= 2;
	stsize = bstart * 2 - 1; bstart--;
 
	for (int i = 0; i <= n; i++)
		for (int j = 0; j < stsize; j++)
			norm[i][j] = 0, sqs[i][j] = 0;
 
	scanf("%d", &q);
 
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			int v; scanf("%d", &v);
			updbit(i+1, j+1, v, false);
			updbit(i+1, j+1, (v*v+MOD)%MOD, true);
		}
	}
 
	for (int i = 0; i < q; i++) {
		int type; scanf(" %d", &type);
		if (type == 1) {
			int r1, c1, r2, c2;
			scanf(" %d%d%d%d", &r1, &c1, &r2, &c2);
			ll res = getrange(r1, c1, r2, c2, false);
			ll sqv = getrange(r1, c1, r2, c2, true);
 
			res = (res * res - sqv + MOD) % MOD;
			res = (res * INV + MOD) % MOD;
			
			printf("%lld\n", res);
		}
		else {
			int r, c, v;
			scanf(" %d%d%d", &r, &c, &v);
			ll cval = getrange(r, c, r, c, false);
			//ll diff = v - cval;
			updbit(r, c, -cval, false);
			updbit(r, c, -((cval*cval + MOD) % MOD), true);
			updbit(r, c, v, false);
			updbit(r, c, (v*v + MOD) % MOD, true);
		}
	}
 
 
}
