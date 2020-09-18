#include "plants.h"
#include <bits/stdc++.h>
using namespace std;
vector<int> permutation;
static const int n_bits=20;
const pair<int,int> inf = make_pair(1e9,0);
pair<int,int> arr[1<<(n_bits+1)];
int low[1<<(n_bits+1)];
int high[1<<(n_bits+1)];
int lazyadd[1<<(n_bits+1)];
struct segtree {

    segtree(){}
    void build(vector<int> v) {
        assert(v.size()<(1<<n_bits));
        for(int i=0; i<(1<<n_bits); i++) {
            low[i+(1<<n_bits)] = i;
            high[i+(1<<n_bits)] = i;
            arr[i+(1<<n_bits)] = (i<v.size() ? make_pair(v[i],i) : inf);
        }
        for(int i=(1<<n_bits)-1; i>=1; i--) {
            low[i] = min(low[2*i], low[2*i+1]);
            high[i] = max(high[2*i], high[2*i+1]);
            arr[i] = min(arr[2*i], arr[2*i+1]);
        }
        for(int i=0; i<(1<<(n_bits+1)); i++) {
            lazyadd[i] = 0;
        }
    }
    pair<int,int> value(int node) {
        arr[node].first += lazyadd[node];
        if(node<(1<<n_bits)) {
            lazyadd[2*node] += lazyadd[node];
            lazyadd[2*node+1] += lazyadd[node];
        }
        lazyadd[node] = 0;
        return arr[node];
    }
    void update(int node, int left, int right, int change) {
        if(right>=high[node] && left<=low[node]) {
            lazyadd[node] += change;
        } else if(right<low[node] || left>high[node]) {
            return;
        } else {
            update(2*node, left, right, change);
            update(2*node+1, left, right, change);
            arr[node] = min(value(node*2), value(node*2+1));
        }
    }
    pair<int,int> query(int node, int left, int right) {
        value(node);
        if(right>=high[node] && left<=low[node]) {
            return arr[node];
        } else if(right<low[node] || left>high[node]) {
            return inf;
        } else {
            return min(query(node*2, left, right), query(node*2+1, left, right));
        }
    }
    pair<int,int> smallest() {
        return query(1, 0, 1<<n_bits);
    }
    void decr(int left, int right) {
        update(1, left, right, -1);
    }
};

void init(int k, std::vector<int> r) {
    segtree s;
    s.build(r);
    int n = r.size();
    assert(k*2>n);
    permutation.resize(n);
    for(int i=0; i<n; i++) {
        pair<int,int> p = s.smallest();
        assert(p.first==0);
        int x = p.second;
        if(x<k-1) {
            pair<int,int> q = s.query(1, n-k+x+1, n-1);
            if(q.first==0) {
                x = q.second;
            }
        }
        s.update(1, x, x, 1e9);
        permutation[x] = i;
        if(x>=k-1) {
            s.decr(x-k+1, x);
        } else {
            s.decr(0, x);
            s.decr(n-k+x+1, n-1);
        }
    }
}

int compare_plants(int x, int y) {
    return (permutation[x]<permutation[y] ? 1 : -1);
}
