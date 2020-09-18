#include "plants.h"
#include <bits/stdc++.h>
using namespace std;
vector<int> permutation;
void init(int k, std::vector<int> r) {
    int n = r.size();
    assert(k*2>n);
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
}

int compare_plants(int x, int y) {
    return (permutation[x]<permutation[y] ? 1 : -1);
}
