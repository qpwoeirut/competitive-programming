#include "testlib.h"
#include <bitset>
#define low(i) (i<<(__builtin_clz(i)-31+n_bits))-(1<<n_bits)
#define high(i) ((i+1)<<(__builtin_clz(i)-31+n_bits))-(1<<n_bits)-1
using namespace std;

const int MAXN = 200000;
const int MINN = 2;
const int MAXK = MAXN;
const int MINK = MINN;
const int MAXQ = 200000;
const int MINQ = 1;

const string input_secret = "1b32a07d5f5fc55f21038b12a3655e";
const int n_bits=20;
int arr[1<<(n_bits+1)];
int lazyadd[1<<(n_bits+1)];
vector<int> permutation;
bitset<MAXN> visited;

struct segtree {
    segtree(){}
    void build(vector<int> v) {
        for(int i=0; i<(1<<n_bits); i++) {
            arr[i+(1<<n_bits)] = (i<(int)v.size() ? v[i] : 1e9);
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

    void decr(int left, int right) {
        int node = 1;
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

segtree st;
int ctr = 0;
int blocking(int rg, int k, int n) {
    int lt = rg - k + 1;
    if(lt<0) {
        int p = st.find_zero(1, lt+n, n-1);
        if(p!=-1) {
            return p;
        }
        return st.find_zero(1,0,rg);
    } else {
        return st.find_zero(1,max(0,lt),rg);
    }
}

bool pull(int idx, int k, int n) {
    ensuref(!visited[idx], "Invalid ranks, cannot pull 0!");
    visited[idx] = true;
    int x;
    while((x=blocking(idx,k,n))!=idx) {
        pull(x,k,n);
    }
    permutation[idx] = ctr;
    ctr++;
    // decrement the k values before it, and push value in
    if(idx >= k-1) {
        st.decr(idx-(k-1), idx);
    } else {
        st.decr(0, idx);
        st.decr(idx-(k-1)+n, n-1);
    }
    st.pt_update(idx);
    return true;
}
int BIT[2*MAXN+1];
struct fenwick {
    void add(int a, int b) {
        while (a < MAXN) {
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

void verify_permutation(int k, vector<int> r) {
    int n = r.size();
    for(int i=0; i<k; i++) {
        permutation[i+n] = permutation[i];
    }
    fenwick f;
    for(int i=0; i<k; i++) {
        f.add(permutation[i]+1,1);
    }
    for(int i=0; i<n; i++) {
        ensuref(r[i]==f.sum(permutation[i]), "Bug in validator!");
        f.add(permutation[i]+1,-1);
        f.add(permutation[i+k]+1,1);
    }
}

void verify_ranks(int k, vector<int> r) {
    int n = r.size();
    permutation.resize(n+k);
    st.build(r);
    while(ctr<n) {
        int p = st.find_zero(1,0,n-1);
        ensuref(p!=-1, "Invalid ranks, no zero found!");
        pull(p,k,n);
    }
    verify_permutation(k, r);
}

int main() {
    registerValidation();
	string secret = inf.readLine();
	ensuref(secret == input_secret, "Secret not found!");
	int n = inf.readInt(MINN, MAXN, "n");
	inf.readSpace();
	int k = inf.readInt(MINK, n, "k");
	inf.readSpace();
	int q = inf.readInt(MINQ, MAXQ, "q");
	inf.readEoln();
	vector<int> r;
	for(int i=0; i<n; i++) {
        if(i) inf.readSpace();
        r.push_back(inf.readInt(0, k-1, "r_i"));
	}
	inf.readEoln();
	verify_ranks(k,r);
	// todo: ensure that the input is actually valid, need to use part (a) from author solution
	for(int t=0; t<q; t++) {
        int x = inf.readInt(0, n-1, "x");
        inf.readSpace();
        int y = inf.readInt(0, n-1, "y");
        ensuref(x<y, "First plant should have smaller id than second plant!");
        inf.readEoln();
	}
	inf.readEof();
	return 0;
}
