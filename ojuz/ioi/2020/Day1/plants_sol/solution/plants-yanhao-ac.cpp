#include "plants.h"
#include <bits/stdc++.h>
#define low(i) (i<<(__builtin_clz(i)-31+n_bits))-(1<<n_bits)
#define high(i) ((i+1)<<(__builtin_clz(i)-31+n_bits))-(1<<n_bits)-1
using namespace std;
vector<int> tallest;
vector<int> shortest;
int n_global;
const int n_bits=20;
const int inf = 1e9;
int arr[1<<(n_bits+1)];
int lazyadd[1<<(n_bits+1)];

struct segtree {
    segtree(){}
    void build(vector<int> v) {
        assert(v.size()<(1<<n_bits));
        for(int i=0; i<(1<<n_bits); i++) {
            arr[i+(1<<n_bits)] = (i<(int)v.size() ? v[i] : inf);
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

    int find_zero(int node) {
        if(value(node)!=0) {
            return -1;
        }
        if(node >= (1<<n_bits)) {
            return arr[node]==0 ? node-(1<<n_bits) : -1;
        }
        int x = find_zero(node*2);
        if(x!=-1) return x;
        return find_zero(node*2+1);
    }
};

// gives you the lexi smallest ordering given the doubled array r
vector<int> lexi_smallest(int k, vector<int> r) {
    segtree s;
    s.build(r);
    vector<int> ret;
    ret.resize(r.size());
    queue<int> stash;
    for(int i=0; i<(int)r.size(); i++) {
        int p = s.find_zero(1);
        while(p==-1) {
            s.decr(stash.front(), 2*n_global-1);
            p = s.find_zero(1);
            stash.pop();
        }
        ret[p] = i;
        s.update(1, p, p, 1e9);

        s.decr(max(0, p-k+1), p);
        if(p<k-1) {
            stash.push(p-k+1+2*n_global);
        }
    }
    return ret;
}
void init(int k, std::vector<int> r) {
    n_global = r.size();
    for(int i=0; i<n_global; i++) {
        r.push_back(r[i]);
    }
    tallest = lexi_smallest(k,r);
    for(int &i: r) i = k-1-i;
    shortest = lexi_smallest(k,r);
}

int compare_plants(int x, int y) {
    if(x>y) return -compare_plants(y,x);
    if(tallest[x]>tallest[y] || shortest[y]>shortest[x+n_global]) return -1;
    if(shortest[x]>shortest[y] || tallest[y]>tallest[x+n_global]) return 1;
	return 0;
}
