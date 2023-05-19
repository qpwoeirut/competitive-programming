#include <bits/stdc++.h>

using namespace std;

const int MAXN = 4e5 + 5;

struct Seg{

    int n, h;
    int t[2 * MAXN];
    int d[MAXN];
    Seg (int _n) {
        n = _n;
        h = sizeof(int) * 8 - __builtin_clz(n);
    }
    
    void apply (int p, int v){
        t[p] += v;
        if (p < n)
        {
            d[p] += v;
        }
    }
    
    void build(int p){
        while (p > 1)
        {
            p /= 2;
            t[p] = max(t[p * 2], t[p * 2 + 1]) + d[p];
        }
    }
    
    void push(int p){
        for (int s = h; s > 0; s--)
        {
            int i = p >> s;
            if (d[i] != 0){
                apply(i * 2, d[i]);
                apply(i * 2 + 1, d[i]);
                d[i] = 0;
            }
        }
    }
    void inc (int l, int r, int v){
        l += n, r += n;
        int lp = l, rp = r;
        for (; l < r; l /= 2, r /= 2)
        {
            if (l % 2) apply(l++, v);
            if (r % 2) apply(--r, v);
        }
        build(lp);
        build(rp-1);
    }
    
    int query (int l, int r){
        l += n, r += n;
        push(l);
        push(r-1);
        int res = 0;
        for (; l < r; l /= 2, r /= 2)
        {
            if (l % 2) res = max(res, t[l++]);
            if (r % 2) res = max(res, t[--r]);
        }
        return res;
    }
};

int main()
{
    int n;
    cin >> n;
 return 0;
}

