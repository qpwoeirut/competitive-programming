#include <bits/stdc++.h>
#include "game.h"

const int MN = 1501;

using namespace std;

int N;
int rt[MN];
int sz[MN];

int root(int u) {
    if (rt[u] != u) {
        rt[u] = root(rt[u]);
    }
    return rt[u];
}

int ct[MN][MN];
void join(int u, int v) {
    int ru = root(u), rv = root(v);
    if (sz[ru] < sz[rv]) {
        swap(ru, rv);
    }
    for (int i=0; i<N; ++i) {
        //if (root(i) == i)
            ct[ru][i] += ct[rv][i];
            ct[i][ru] = ct[ru][i];
    }
    rt[rv] = ru;
    
    sz[ru] += sz[rv];
    //cerr << "ru,rv: " << ru << ' ' << root(rv) << endl;
}


void initialize(int n) {
    N = n;
    for (int i=0; i<N; ++i) {
        for (int j=0; j<N; ++j) {
            ct[i][j] = 0;
        }
        rt[i] = i;
        sz[i] = 1;
    }
}

int hasEdge(int u, int v) {
    int ru = root(u), rv = root(v);
    ++ct[ru][rv];
    ct[rv][ru] = ct[ru][rv];
    
    int ret = 0;
    if (ct[ru][rv] == sz[ru] * sz[rv] && ct[rv][ru] == sz[ru] * sz[rv]) {
        join(u, v);
        //cerr << "ru,rv: " << root(u) << ' ' << root(v) << endl;
        //cerr << "joined u,v: " << u << ' ' << v << endl;
        ret = 1;
    }

    //cerr << "u,v: " << u << ' ' << v << ' ' << endl << "ru,rv,su,sv,ctu,ctv: " << ru << ' ' << rv << ' ' << sz[ru] << ' ' << sz[rv] << ' ' << ct[ru][rv] << ' ' << ct[rv][ru] << endl;
    //for (int i=0; i<N; ++i) { cerr << root(i) << ' '; } cerr << endl;
    //for (int i=0; i<N; ++i) {for (int j=0; j<N; ++j) cerr << ((root(i) == i && root(j) == j) ? ct[i][j] : 0) << ' '; cerr << endl;} cerr << endl;
    return ret;
}
/*
4
2 3
1 3
0 2
0 1
1 2
0 3


5
0 1
0 2
0 3
1 4
2 4
3 4
0 4
1 2
1 3
2 3

5
0 1
0 2
0 3
0 4
1 2
1 3
1 4
3 4
2 3
2 4

*/
