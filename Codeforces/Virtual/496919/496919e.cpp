#include <bits/stdc++.h>
using namespace std;
#define int long long

signed main(){
    int n; cin >> n;
    vector<int> c(2*n), inds(2*n), done(2*n);
    for(int i = 0; i < 2*n; i++) cin >> c[i];
    iota(begin(inds), end(inds), 0);
    sort(begin(inds), end(inds), [&](int x, int y){
        return c[x] > c[y];
    });

    int ans = 0;
    for(int i = 0; i < 2*n; i++){
        if(done[i]) continue;
        cout << i << " " << c[inds[i]] << endl;
        if(inds[i] == inds[i+1]^1){
            done[i+2] = true;
            ans += c[inds[i]] - c[inds[i+2]];
        } else{
            done[i+1] = true;
            ans += c[inds[i]] - c[inds[i+1]];
        }
    }

    cout << ans << endl;
}
