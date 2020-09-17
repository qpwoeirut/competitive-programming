#include <iostream>
#include <algorithm>
#include <map>

using namespace std;

typedef long long ll;

const ll MOD = 1000000007;
const ll MAXN = 100005;

ll deg(const ll& n) {
    ll k = MOD - 2;
    ll res = 1;
    ll cur = n;
    
    while (k > 0) {
        if (k & 1) {
            res = (res * cur) % MOD;
        }
        k >>= 1;
        cur = (cur * cur) % MOD;
    }
  
    return res;
}

void solve() {
    int N;
    cin >> N;
    
    int a = 0, b = 0;
    
    char tmp;
    for (int i=0; i<N; i++) {
        cin >> tmp;
        if (tmp == '1') a++;
    }
    for (int i=0; i<N; i++) {
        cin >> tmp;
        if (tmp == '1') b++;
    }
    
    int lo = max(a, b) - min(a, b);
    int hi = a + b;
    if (hi == 2*N) {
        hi = 0;
    }
    else if (hi > N) {
        hi = N - (hi % N);
    }
    // cout << "a,b: " << a << " " << b << endl;
    // cout << "l,h: " << lo << " " << hi << endl;
    
    ll ans = 0;
    ll numer = 1, denom = 1;
    ll pvn = N, pvd = 1;
    for (int k=lo; k<=hi; k+=2) {
        for (; pvn>N-k; pvn--) numer = (numer * pvn) % MOD;
        for (; pvd<=k; pvd++) denom = (denom * pvd) % MOD;
        ans += (numer * deg(denom)) % MOD;
        ans %= MOD;
    }
    
    cout << ans << endl;
    return;
}

int main() {
    int T;
    cin >> T;
    
    while (T > 0) {
        T--;
        solve();
    }
    
    return 0;
}
