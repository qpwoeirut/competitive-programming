#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <string>
#include <string.h>
#include <utility>
#include <map>
#include <list>
#include <queue>
using namespace std;
typedef pair <int, int> pii;
typedef long long ll;
#define f first
#define s second

const int maxn = 1e5 + 10;

int n, k;
ll a[maxn], b[maxn];
int cur[maxn];
priority_queue <pii, vector <pii>, less <pii> > pq;

int main() {
    scanf("%d%d", &n, &k);
    for (int i = 0; i < n; ++i) {
        scanf("%lld%lld", &a[i], &b[i]);
        pq.push({a[i] - b[i], i});
    }
    ll ans = 0;
    for (int i = 0; i < k; ++i) {
        pii t = pq.top();
        pq.pop();
        if (t.f <= 0) break;
        ans += t.f;
        int x = t.s;
        ++cur[x];
        int nv = (a[x] - (cur[x] + 1) * b[x]) * (cur[x] + 1) - (a[x] - cur[x] * b[x]) * cur[x];
        pq.push({nv, x});
    }
    printf("%lld\n", ans);
}

