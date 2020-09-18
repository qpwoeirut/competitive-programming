#include <bits/stdc++.h>
using namespace std;

const int n_max = 200000;
#define low(i) (i<<(__builtin_clz(i)-31+n_bits))-(1<<n_bits)
#define high(i) ((i+1)<<(__builtin_clz(i)-31+n_bits))-(1<<n_bits)-1

int BIT[2*n_max+1];
const int n_bits=__lg(n_max)+2;

int arr[1<<(n_bits+1)];
int lazyadd[1<<(n_bits+1)];

int n = 200000;
int k = 2;
int q = 5e5;
int subtask = 0;

int per[n_max*2];

struct segtree {
    segtree(){}
    void build(vector<int> v) {
        assert(v.size()<(1<<n_bits));
        for(int i=0; i<(1<<n_bits); i++) {
            arr[i+(1<<n_bits)] = (i<(int)v.size() ? v[i] : (int)1e9);
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

struct plant {
    vector<int> tallest;
    vector<int> shortest;
    int n_global;

    // gives you the lexi smallest ordering given the doubled array r
    vector<int> lexi_smallest(vector<int> r) {
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
    void init(std::vector<int> r) {
        n_global = r.size();
        for(int i=0; i<n_global; i++) {
            r.push_back(r[i]);
        }
        tallest = lexi_smallest(r);
        for(int &i: r) i = k-1-i;
        shortest = lexi_smallest(r);
    }

    bool comparable(int x, int y) {
        bool b = unsigned(tallest[y]-tallest[x]) > unsigned(tallest[x+n]-tallest[x]) ||
                    unsigned(shortest[y]-shortest[x]) > unsigned(shortest[x+n]-shortest[x]);
        return b;
    }

    unordered_set<long long> past_queries;
    void gen_query() {
        int x,y;
        long long z;
        do {
            x = rnd.next(n);
            y = rnd.next(n);
            z = ((long long)x<<20)+y;
            if(x>y) swap(x,y);
        } while(x==y || past_queries.find(z)!=past_queries.end());
        past_queries.insert(z);
        printf("%d %d\n", x, y);
    }
    int reject = 0;
    void gen_query(bool b) {
        int x,y;
        long long z;
        do {
            reject++;
            //assert(reject<300*q);
            x = rnd.next(n);
            y = rnd.next(n);
            z = ((long long)x<<20)+y;
            if(x>y) swap(x,y);
        } while(x==y || comparable(x,y)==b || past_queries.find(z)!=past_queries.end());
        past_queries.insert(z);
        printf("%d %d\n", x, y);
    }
    void gen_queries() {
        if(subtask==6) {
            int queries[n-1];
            for(int i=1; i<n; i++) {
                queries[i-1] = i;
            }
            shuffle(queries, queries+n-1);
            for(int i=0; i<q; i++) {
                printf("%d %d\n", 0, queries[i]);
            }
        } else if(subtask==5) {
            pair<int,int> queries[n*(n-1)/2];
            int ctr = 0;
            for(int i=0; i<n; i++) {
                for(int j=i+1; j<n; j++) {
                    queries[ctr] = make_pair(i, j);
                    ctr++;
                }
            }
            shuffle(queries, queries+n*(n-1)/2);
            for(int i=0; i<q; i++) {
                printf("%d %d\n", queries[i].first, queries[i].second);
            }
        } else if(subtask==4) {
            for(int i=0; i<q; i++) {
                gen_query(false);
            }
            assert(past_queries.size() == q);
        } else {
            for(int i=0; i<q; i++) {
                gen_query();
            }
            assert(past_queries.size() == q);
        }
    }
};

// we actually need a solution to do this
struct fenwick {
    void add(int a, int b) {
        while (a < n_max) {
            BIT[a] += b;
            a += (a&-a);
        }
    }
    int sum(int a) {
        int r = 0;
        while (a) {
            r += BIT[a];
            a -= (a&-a);
        }
        return r;
    }
};

void gen() {
    plant pl;
    for(int i=0; i<k; i++) {
        per[i+n] = per[i];
    }
    fenwick f;
    for(int i=0; i<k; i++) {
        f.add(per[i]+1,1);
    }
    vector<int> v;
    for(int i=0; i<n; i++) {
        if(i) printf(" ");
        printf("%d", f.sum(per[i]));
        v.push_back(f.sum(per[i]));
        f.add(per[i]+1,-1);
        f.add(per[i+k]+1,1);
    }

    pl.init(v);
    printf("\n");
    pl.gen_queries();
}
