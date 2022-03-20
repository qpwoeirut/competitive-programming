#include <bits/stdc++.h>

using namespace std;
const int MAXN = 1e5 + 5, SQRT = 320;
typedef pair<int, int> pii;

struct Query {
    int type;
    int a, b;
    int c;
};

map<int, array<int, MAXN>> dp; // we want node # and each value
vector<int> adj[MAXN];
vector<int> a;
int dep[MAXN];
Query query[MAXN];


#define tm tmmm

//lca
int tm = 0, p[MAXN], et[2 * MAXN], par[MAXN], sqp[MAXN];
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

    int query (int x, int y, int u = 1, int l = 0, int r = tm - 1){
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


void dfs(int u, int f){
    p[u] = tm;
    et[tm++] = u;
    for (int x : adj[u]){
       if (x != f)
       {
           dfs(x, u);
           et[tm++] = u;
       }
    }
}


int cur = 0;

void calc (int u, int f, int d = 0, int sq = -1){
    cout << "got here" << "\n";
    bool ok = 0;
    par[u] = f;
    sqp[u] = sq;
    dep[u] = d;
    if (d % SQRT == 0)
    {
        int cur = u;
        int z = 0;
        while (par[cur] != -1 && z < SQRT){
            dp[u][a[cur]]++;
            cur = par[cur];
            z++;
        }
        cout << "got past loop" << "\n";
        
        ok = 1;
    }
    
    for (auto x : adj[u])
    {
        if (x != f)
        {
            calc(x, u, d+1, (ok? u : sq));
        }
    }
}



void upd (int x, int y, int o){
    if (dp.count(x))
    {
        dp[x][o]--;
        dp[x][y]++;
        return;
    }
    
    for (auto u : adj[x])
    {
        upd(u, y, o);
    }
}




void solve (){
    fill(par, par + MAXN, -1);
    int n, q;
    cin >> n >> q;
    Segmn tree(n);
    a = vector<int>(n);
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
    }
    
    for (int i = 0; i < n-1; i++)
    {
        int l, r;
        cin >> l >> r;
        l--, r--;
        adj[l].push_back(r);
        adj[r].push_back(l);
        
    }
    
    
    for (int i = 0; i < SQRT; i++)
    {
        for (int j = 0; j < MAXN; j++)
        {
            dp[i][j] = 0;
        }
        
    }
    
    calc(0, -1);
    dfs(0,-1);
    tree.build();
    
    
    
    dfs(0, -1);
    
     for (int i=0; i<q; ++i) {
        cin >> query[i].type >> query[i].a >> query[i].b;
        query[i].a--;
        
        if (query[i].type == 2) {
            query[i].b--;
            cin >> query[i].c;
        }
    }
    
    
    
    
    
    for (auto x : query)
    {
        
        if (x.type == 1)
        {
            upd(x.a, x.b, a[x.a]);
        } else
        {
            int z = tree.lca(x.a, x.b);
            int cur = x.a;
            int res =0 ;
            while (!dp.count(cur) && dep[par[cur]] >= dep[z]){
                if (a[cur] == x.b)
                {
                    res++;
                }
                cur = par[cur];
                if (cur == z)
                {
                    break;
                }
            }
            
            while (cur != z && dep[sqp[cur]] >= dep[z]){
                res += dp[sqp[cur]][x.b];
                cur = sqp[cur];
            }
            
            cout << res << "\n";
        }
    }
}
int main()
{
    cin.tie(0)->sync_with_stdio(0);
    int t = 1;
    //cin >> t;
    while (t--){
        solve();
    }
    cout << "done!" << endl;
 return 0;
}
