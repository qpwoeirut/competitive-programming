#include <bits/stdc++.h>
using namespace std;
const int N = 100, M = 5e4;

int h[M], K[N], s[N][M], C[N][M];
pair<int, int> dp[N][M];

int f(int i, int j, int k) { return C[i][k] + h[j+k]; }

int tsearch(int i, int j){
    int lo = -1, hi = K[i];
    while(hi - lo > 1){
        int mid = (hi+lo) >> 1;
        if(f(mid) > f(mid+1)) hi = mid;
        else lo = mid;
    }
    return lo+1;
}

signed main(){
    int n, m; cin >> n >> m;
    for(int i = 0; i < m; i++) cin >> h[i];
    for(int i = 0; i < n; i++){
        int k; cin >> k;
        K[i] = k;
        for(int j = 0; j < k; j++) cin >> s[i][j];
        int pref = 0, sum = 0;
        for(int j = 0; j < k; j++){
            pref += s[i][j];
            sum += pref;
            C[i][j] = sum;
        }
    }
   
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            
        }
    }
}
