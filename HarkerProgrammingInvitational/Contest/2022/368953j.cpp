#include <bits/stdc++.h>

using namespace std;
typedef pair<int, int> pii;
const int MAXN = 1e5 + 5;
vector<int> adj[MAXN];
int tm = 0, s[MAXN], e[MAXN], p[MAXN], et[2 * MAXN];

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


int mn (int l, int r){
    if (l == -1)
    {
        return r;
    } 
    if (r == -1)
    {
        return l;
    }
    return (p[l] < p[r] ? l : r);
}

struct Segmn{

    int n;
    int t[8 * MAXN];
    
    Segmn (int _n){
        n = _n;
    }
    
    void build(int u = 1, int l = 0, int r = tm-1){
        if (l == r)
        {
            t[u] = et[l];
        } else
        {
            int m = (l + r)/2;
            build(u * 2, l, m);
            build(u * 2 + 1, m + 1, r);
            t[u] = mn(t[u * 2], t[u * 2 + 1]);
        }
        
    }

    int query (int x, int y, int u = -1, int l = 0, int r = tm - 1){
        if (l > y || r < x)
        {
            return -1;
        }
        if (l >= x && r <= y)
        {
            return t[u];
        }
        int m = (l + r)/2;
        return mn(query(x, y, u * 2, l, m), query(x, y, u * 2 + 1, m + 1, r));
    }
    
    int lca (int l, int r){
        if (p[l] > p[r])
        {
            swap(l, r);
        }
        return query(p[l], p[r]);
    }
};


void dfs2(int u, int f){
    p[u] = tm;
    et[tm++] = u;
    for (int x : adj[u]){
       if (x != f)
       {
           dfs2(x, u);
           et[tm++] = u;
       }
    }
}

void dfs(int u, int p){
    s[u] = tm++;
    for (int x : adj[u]){
       if (x != p)
       {
           dfs(x, u);
       }
    }
    e[u] = tm-1;
}





int main()
{
    int n, m;
    cin >> n >> m;
    Seg st(n);
    Segmn tree(n);
    for (int i = 0; i < n-1; i++)
    {
        int l, r;
        cin >> l >> r;
        l--, r--;
        adj[l].push_back(r);
        adj[r].push_back(l);
        
    }
    
    dfs(0, -1);
    tm = 0;
    dfs2(0, -1);
    tree.build();
    while (m--)
    {
        int q;
        cin >> q;
        if (q == 1)
        {
            int l, r, w;
            cin >> l >> r >> w;
            l--, r--;
            int z = tree.lca(l, r);
            cout << l << " " << r << " " << "lca " << z << "\n";
            st.inc(s[z], e[z] + 1, w);
            //in the subtree
            
        } else
        {
            int z;
            cin >> z;
            z--;
            cout << st.query(s[z], e[z] + 1) << "\n";
        }
    }
 return 0;
}
