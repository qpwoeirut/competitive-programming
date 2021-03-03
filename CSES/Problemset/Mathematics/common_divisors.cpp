//common_divisors.cpp created at 12/19/20 12:51:01

#include <bits/stdc++.h>

using namespace std;

const int MX = 1000005;

int N;
int pf[MX];
int div_ct[MX];

map<int,int> ct;
void gen(int n, int cur) {
    auto it = ct.upper_bound(n);
    if (it == ct.end()) {
        ++div_ct[cur];
        return;
    }

    for (int i=0, x=1; i<=it->second; ++i, x*=it->first) {
        gen(it->first, cur*x);
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    pf[1] = 1;
    for (int i=2; i<MX; ++i) {
        if (pf[i] != 0) continue;
        for (int j=i; j<MX; j+=i) {
            pf[j] = i;
        }
    }

    cin >> N;
    for (int i=0; i<N; ++i) {
        int x;
        cin >> x;

        ct.clear();
        while (x > 1) {
            ++ct[pf[x]];
            x /= pf[x];
        }

        gen(0, 1);
    }

    div_ct[1] = N;
    for (int i=MX-1; i>=1; --i) {
        if (div_ct[i] >= 2) {
            cout << i << endl;
            return 0;
        }
    }
    assert(false);
}
        
