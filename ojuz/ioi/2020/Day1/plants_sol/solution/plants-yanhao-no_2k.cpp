#include "plants.h"
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

    int query(int node, int left, int right) {
        value(node);
        if(right>=high(node) && left<=low(node)) {
            return arr[node];
        } else if(right<low(node) || left>high(node)) {
            return inf;
        } else {
            return min(query(node*2, left, right), query(node*2+1, left, right));
        }
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
vector<int> inv_ht;
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
    inv_ht.push_back(idx);
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
    vector<int> v(2*n);
    for(int &i: v) i=n;
    inv_ht.push_back(n);
    s.build(v);
    for(int i=n-1; i>=0; i--) {
        lt[inv_ht[i]] = inv_ht[s.query(1,inv_ht[i]+n-k+1, inv_ht[i]+n)];
        rg[inv_ht[i]] = inv_ht[s.query(1,inv_ht[i], inv_ht[i]+k-1)];
        s.update(1, inv_ht[i], inv_ht[i], i-n);
        s.update(1, inv_ht[i]+n, inv_ht[i]+n, i-n);
    }
    permutation[n] = n;

}

bool lt_path(int x, int y) {
    // scam: move right only a fixed number of iterations
    int ctr = 0;
    while(lt_dist(x,y)>=k_global && permutation[x]>permutation[y] && ctr<2000) {
        y=lt[y];
    }
    return permutation[y]<permutation[x];
}


bool rg_path(int x, int y) {
    // scam: move right only a fixed number of iterations
    int ctr = 0;
    while(lt_dist(y,x)>=k_global && permutation[x]>permutation[y] && ctr<2000) {
        ctr++;
        y=rg[y];
    }
    return permutation[y]<permutation[x];
}

bool path(int x, int y) {
    return lt_path(x,y) || rg_path(x,y);
}

int compare_plants(int x, int y) {
    if(path(x,y)) return -1;
    if(path(y,x)) return 1;
    return 0;
}
