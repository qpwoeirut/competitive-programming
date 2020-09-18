#include "plants.h"
#include <bits/stdc++.h>
using namespace std;
const int n_max = 10100;
bitset<n_max> adj[n_max];
void init(int k, std::vector<int> r) {
    int n = r.size();
    vector<int> cpy = r;
    for(int i=0; i<n; i++) {
        for(int j=0; j<n; j++) adj[i][j] = true;
        for(int l=0; l<n; l++) {
            int streak = -5*n-1;
            for(int m=2*n-1; m>=0; m--) {
                int j=m%n;
                if(r[j]==0) {
                    streak = (i==j ? -5*n-1 : 0);
                } else {
                    streak++;
                }
                if(streak==k-1) {
                    for(int l=j; l!=(j+k-1)%n; l=(l+1)%n) {
                        r[l]--;
                        assert(r[l]>=0);
                    }
                    r[(j+k-1)%n] = 1e6;
                    adj[i][(j+k-1)%n] = false;
                   break;
                }
                if(m==0) streak = (1<<30);
            }
            if(streak==(1<<30)) break;
        }
        r = cpy;
    }
}

int compare_plants(int x, int y) {
    if(adj[x][y]) return 1;
    if(adj[y][x]) return -1;
    return 0;
}
