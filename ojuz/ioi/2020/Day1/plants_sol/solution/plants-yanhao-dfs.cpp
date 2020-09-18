#include <bits/stdc++.h>
#define low(i) (i<<(__builtin_clz(i)-31+n_bits))-(1<<n_bits)
#define high(i) ((i+1)<<(__builtin_clz(i)-31+n_bits))-(1<<n_bits)-1
#define lt_dist(x,y) (y-x+n)%n
using namespace std;
vector<int> permutation;
int n_global;
const int n_bits=20;
const int inf = 1e9;
const int n_max = 2e5;
int arr[1<<(n_bits+1)];
int lazyadd[1<<(n_bits+1)];
int lt[n_max+5];
int rg[n_max+5];
int k_global;

struct segtree {
    segtree(){}
    void build(vector<int> v) {
        assert(v.size()<(1<<n_bits));
        for(int i=0; i<(1<<n_bits); i++) {
            arr[i+(1<<n_bits)] = (i<v.size() ? v[i] : inf);
        }
        for(int i=(1<<n_bits)-1; i>=1; i--) {
            arr[i] = min(arr[2*i], arr[2*i+1]);
        }
        for(int i=0; i<(1<<(n_bits+1)); i++) {
            lazyadd[i] = 0;
        }
    }
    int value(int node) {
        arr[node] += lazyadd[node];
        if(node<(1<<n_bits)) {
            lazyadd[2*node] += lazyadd[node];
            lazyadd[2*node+1] += lazyadd[node];
        }
        lazyadd[node] = 0;
        return arr[node];
    }
    void update(int node, int left, int right, int change) {
        if(right>=high(node) && left<=low(node)) {
            lazyadd[node] += change;
        } else if(right<low(node) || left>high(node)) {
            return;
        } else {
            update(2*node, left, right, change);
            update(2*node+1, left, right, change);
            arr[node] = min(value(node*2), value(node*2+1));
        }
    }

    void decr(int left, int right) {
        update(1, left, right, -1);
    }

    int find_zero(int node, int lt, int rg) {
        if(rg<low(node) || lt>high(node)) {
            return -1;
        }
        if(value(node)!=0) {
            return -1;
        }
        if(node >= (1<<n_bits)) {
            return arr[node]==0 ? node-(1<<n_bits) : -1;
        }
        int x = find_zero(node*2, lt, rg);
        if(x!=-1) return x;
        return find_zero(node*2+1, lt, rg);
    }
};

segtree s;
int ctr = 0;
int n;
int blocking(int rg, int k) {
    int lt = rg - k + 1;
    if(lt<0) {
        int p = s.find_zero(1, lt+n, n-1);
        if(p!=-1) {
            return p;
        }
        return s.find_zero(1,0,rg);
    } else {
        return s.find_zero(1,max(0,lt),rg);
    }
}

void pull(int idx, int k) {
    int x;
    while((x=blocking(idx,k))!=idx) {
        pull(x,k);
    }
    permutation[idx] = ctr;
    ctr++;
    // decrement the k values before it, and push value in
    if(idx >= k-1) {
        s.update(1, idx-(k-1), idx, -1);
    } else {
        s.decr(0, idx);
        s.decr(idx-(k-1)+n, n-1);
    }
    s.update(1, idx, idx, 1e9);
}

int ans[n_max];

void dfs1(int x) {
    if(lt[x]!=-1 && ans[lt[x]]==0) {
        ans[lt[x]] = 1;
        dfs1(lt[x]);
    }
    if(rg[x]!=-1 && ans[rg[x]]==0) {
        ans[rg[x]] = 1;
        dfs1(rg[x]);
    }
}

vector<int> rev[n_max+5]; // the reverse graph
void dfs2(int x) {
    for(int i: rev[x]) {
        if(ans[i]==0) {
            ans[i] = -1;
            dfs2(i);
        }
    }
}

void init(int k, std::vector<int> r) {
    k_global = k;
    s.build(r);
    n = r.size();
    permutation.resize(n);
    while(ctr<n) {
        int p = s.find_zero(1,0,n-1);
        assert(p!=-1);
        pull(p,k);
    }

    map<int,int> m; // store the lt mappings
    //key: the global rank, value: the index
    for(int i=0; i<k; i++) {
        m[permutation[i]] = i;
    }
    m[(int)1e6] = n;
    for(int i=0; i<n; i++) {
        auto it = m.upper_bound(permutation[i]);
        rg[i] = it->second;
        it = m.upper_bound(permutation[(i+k-1)%n]);
        lt[(i+k-1)%n] = it->second;
        m.erase(permutation[i]);
        m[permutation[(i+k)%n]] = (i+k)%n;
    }

    dfs1(0);

    for(int i=0; i<n; i++) {
        rev[lt[i]].push_back(i);
        rev[rg[i]].push_back(i);
    }
    dfs2(0);
}

int compare_plants(int x, int y) {
    return ans[y];
}
