#include <bits/stdc++.h>
#define low(i) (i<<(__builtin_clz(i)-31+n_bits))-(1<<n_bits)
#define high(i) ((i+1)<<(__builtin_clz(i)-31+n_bits))-(1<<n_bits)-1
#include "testlib.h"
using namespace std;
const int n_bits=18;
const int oo = 1e9;
const int n_max = 2e5;
const int q_max = 5e5;
int arr[1<<(n_bits+1)];
int lazyadd[1<<(n_bits+1)];
int p_lt[n_max+5];
int p_rg[n_max+5];
int stash[n_max+5]; // a manual queue
int tallest[n_max+5];
int shortest[n_max+5];

struct segtree {
    int node = 1;
    int lazy = 0;
    segtree(){}
    void build(vector<int> &v) {
        assert(v.size()<(1<<n_bits));
        for(int i=0; i<(1<<n_bits); i++) {
            arr[i+(1<<n_bits)] = (i<(int)v.size() ? v[i] : oo);
        }
        for(int i=(1<<n_bits)-1; i>=1; i--) {
            arr[i] = min(arr[2*i], arr[2*i+1]);
        }
        for(int i=0; i<(1<<(n_bits+1)); i++) {
            lazyadd[i] = 0;
        }
    }

    void decr(int left, int right) {
        node = 1;
        while(node) {
            if(right>=high(node) && left<=low(node)) {
                lazyadd[node]--;
                while(node%2==0) {
                    arr[node/2] = min(arr[node]+lazyadd[node], arr[node+1]+lazyadd[node+1]);
                    node = node/2;
                }
                node--;
            } else if(right<low(node) || left>high(node)) {
                while(node%2==0) {
                    arr[node/2] = min(arr[node]+lazyadd[node], arr[node+1]+lazyadd[node+1]);
                    node = node/2;
                }
                node--;
            } else {
                node = node*2+1;
            }
        }
    }

    void pt_update(int x) {
        x += (1<<n_bits);
        arr[x] = 1e9;
        while(x) {
            arr[x/2] = min(arr[x]+lazyadd[x], arr[x^1]+lazyadd[x^1]);
            x = x/2;
        }
    }

    int find_zero() {
        node = 1;
        lazy = 0;
        if(lazyadd[1] + arr[1]!=0) return -1;
        while(node < (1<<n_bits)) {
            lazy += lazyadd[node];
            node *= 2;
            if(lazy + lazyadd[node] + arr[node]) node++;
        }
        return node-(1<<n_bits);
    }
};

void lexi_smallest(int k, vector<int> &r, int* ptr, int* ord) {
    segtree s;
    s.build(r);
    int n = r.size();
    stash[0] = n;
    ord[n] = -1;
    int* fr = stash+1;
    int* bk = stash+1;
    for(int i=0; i<(int)r.size(); i++) {
        int p = s.find_zero();
        while(p==-1) {
            s.decr((*fr++)-k+1+n, n-1);
            p = s.find_zero();
        }
        ord[p] = i;
        s.pt_update(p);
        if(p<k-1) {
            s.decr(0, p);
            *bk++ = p;
        } else {
            s.decr(p-k+1, p);
        }
        ptr[p] = ord[*(fr-1)];
    }
}
void init(int k, std::vector<int> r) {
    lexi_smallest(k,r,p_lt, tallest);
    for(int &i: r) i = k-1-i;
    lexi_smallest(k,r,p_rg, shortest);
}

int compare_plants(int x, int y) {
    if(x>y) return -compare_plants(y,x);
    if(tallest[x]>tallest[y] || p_rg[y]>=shortest[x]) return -1;
    if(shortest[x]>shortest[y] || p_lt[y]>=tallest[x]) return 1;
	return 0;
}

int main() {

    registerValidation();
	string secret = inf.readLine();
	const string input_secret = "1b32a07d5f5fc55f21038b12a3655e";
	ensuref(secret == input_secret, "Secret not found!");
	int n = inf.readInt();
	inf.readSpace();
	int k = inf.readInt();
	inf.readSpace();
	int q = inf.readInt();
	inf.readEoln();
	vector<int> r;
	for(int i=0; i<n; i++) {
        if(i) inf.readSpace();
        r.push_back(inf.readInt(0, k-1, "r_i"));
	}
	init(k, r);
	inf.readEoln();
	for(int t=0; t<q; t++) {
        int x = inf.readInt(0, n-1, "x");
        inf.readSpace();
        int y = inf.readInt(0, n-1, "y");
        int z = compare_plants(x,y);
        ensuref(z!=0, "Plants are not comparable!");
        inf.readEoln();
	}
    skip_ok();
}
