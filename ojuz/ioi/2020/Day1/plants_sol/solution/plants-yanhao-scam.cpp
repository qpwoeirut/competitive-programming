#include <bits/stdc++.h>
#define low(i) (i<<(__builtin_clz(i)-31+n_bits))-(1<<n_bits)
#define high(i) ((i+1)<<(__builtin_clz(i)-31+n_bits))-(1<<n_bits)-1
#define lt_dist(x,y) (y-x+n)%n
using namespace std;
const int total_tries = 5000;
int tries = 0;
const int n_max = 310;
int permutation[total_tries][n_max];
bool adj[n_max][n_max];

void init(int k, std::vector<int> r) {
    vector<int> r_copy = r;
    int n = r.size();
    for(tries=0; tries<total_tries; tries++) {
        r = r_copy;
        for(int i=0; i<n; i++) {
            int offset = rand()%n;
            int streak = -n-1;
            for(int j=n-1; j>=0; j--) {
                if(r[(j+offset)%n]==0) {
                    streak = 0;
                } else {
                    streak++;
                }
                if(streak==k-1) {
                   for(int l=j; l<j+k-1; l++) {
                        r[(l+offset)%n]--;
                   }
                   r[(j+k-1+offset)%n] = 1e6;
                   permutation[tries][(j+k-1+offset)%n] = i;
                   break;
                }
                if(j==0) {
                    for(int l=0; l<=streak; l++) {
                        r[(l+offset)%n]--;
                    }
                    for(int l=n-k+streak+1; l<n; l++) {
                        r[(l+offset)%n]--;
                    }
                    r[(streak+offset)%n] = 1e6;
                    permutation[tries][(streak+offset)%n] = i;
                }
            }
        }
    }
    for(int i=0; i<n; i++) {
        for(int j=0; j<n; j++) {
            adj[i][j] = true;
            for(int l=0; l<total_tries; l++) {
                if(permutation[l][i] > permutation[l][j]) {
                    adj[i][j] = false;
                } else {
                    adj[j][i] = false;
                }
            }
        }
    }

}

int compare_plants(int x, int y) {
    if(adj[x][y]) return 1;
    if(adj[y][x]) return -1;
    return 0;
}
