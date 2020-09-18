#include <bits/stdc++.h>
#define low(i) (i<<(__builtin_clz(i)-31+n_bits))-(1<<n_bits)
#define high(i) ((i+1)<<(__builtin_clz(i)-31+n_bits))-(1<<n_bits)-1
#define lt_dist(x,y) (y-x+n)%n
using namespace std;
int n;
const int n_max = 10100;
int permutation[n_max][n_max];
int k_global;

void init(int k, std::vector<int> r) {
    vector<int> r_copy = r;
    n = r.size();
    k_global = k;
    for(int offset=0; offset<n; offset+=k) {
        r = r_copy;
        for(int i=0; i<n; i++) {
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
                   permutation[offset][(j+k-1+offset)%n] = i;
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
                    permutation[offset][(streak+offset)%n] = i;
                }
            }
        }
    }
}

int compare_plants(int x, int y) {
    bool all0 = true;
    bool all1 = true;
    for(int i=0; i<n; i+=k_global) {
        if(permutation[i][x] > permutation[i][y]) {
            all0 = false;
        } else {
            all1 = false;
        }
    }
    if(all0) return 1;
    if(all1) return -1;
    return 0;
}
