#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <cmath>
#include <string>
#include <string.h>
#include <utility>
#include <map>
#include <list>
using namespace std;
typedef pair <int, int> pii;
typedef long long ll;
#define f first
#define s second

const int maxn = 1e6 + 100;

int n, k, m;
int a[maxn], ans[maxn], mq[maxn], l=0, r=1;

int main() {
    scanf("%d%d%d", &n, &m, &k);
    for (int i=0; i<n; ++i)
    {
        scanf("%d", &a[i]);
    }
    for (int i=1; i<=k; ++i)
    {
        for (; r>l && mq[r-1] < a[n-i]; --r); // pop from back of mq until the last number is larger than a[i]
        mq[r++] = a[n-i];
    }
    for (int i=0; i<=k; ++i) ans[n-i] = mq[l];
    for (int i=k+1; i<=n; ++i)
    {
        for (; r>l && mq[r-1] < a[n-i]; --r);
        mq[r++] = a[n-i];
        if (mq[l] == a[n-i+k]) ++l;
        ans[n-i] = mq[l];
    }
    for (int i = 0; i < m; ++i) {
        int x;
        scanf("%d", &x);
        printf("%d\n", ans[x - 1]);
    }
}

