#include "plants.h"
#include <bits/stdc++.h>
using namespace std;
const int n_max = 10100;
bitset<n_max> adj[n_max];
vector<int> permutation;
void init(int k, std::vector<int> r) {
    int n = r.size();
    permutation.resize(n);
    for(int i=0; i<n; i++) {
        int streak = -n-1;
        for(int j=n-1; j>=0; j--) {
            if(r[j]==0) {
                streak = 0;
            } else {
                streak++;
            }
            if(streak==k-1) {
               for(int l=j; l<j+k-1; l++) {
                    r[l]--;
               }
               r[j+k-1] = 1e6;
               permutation[j+k-1] = i;
               break;
            }
            if(j==0) {
                for(int l=0; l<=streak; l++) {
                    r[l]--;
                }
                for(int l=n-k+streak+1; l<n; l++) {
                    r[l]--;
                }
                r[streak] = 1e6;
                permutation[streak] = i;
            }
        }
    }

    for(int i=0; i<n; i++) {
        for(int j=(i+n-k+1)%n; j!=i; j=(j+1)%n) {
            if(permutation[i]<permutation[j]) {
                adj[i][j] = true;
            } else {
                adj[j][i] = true;
            }
        }
    }

    for(int l=0; l<n; l++) {
        for(int i=0; i<n; i++) {
            for(int j=0; j<n; j++) {
                adj[i][j] = adj[i][j] || (adj[i][l] && adj[l][j]);
            }
        }
    }
}

int compare_plants(int x, int y) {
    if(adj[x][y]) return 1;
    if(adj[y][x]) return -1;
    return 0;
}
