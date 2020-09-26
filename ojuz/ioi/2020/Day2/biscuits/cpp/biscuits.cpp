#include "biscuits.h"
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

ll sub2(ll x, vector<ll> a) {
    //cerr << "a: "; for (int i=0; i<a.size(); ++i) cerr << a[i] << ' '; cerr << endl;

    ll ans = 1;
    for (int i=0; i<a.size(); ++i) {
        if (a[i] >= x) ans <<= 1;
    }
    //cerr << "base: " << ans << endl;

    int cur = 0;
    for (int i=0; i<a.size(); ++i) {
        if (a[i] > x) {
            ++cur;
            a[i+1] += a[i] >> 1;
            a[i] = 0;
        }
        else {
            if (cur > 0) {
                ans += ans >> cur;
            }
            cur = 0;
        }
    }

	return ans;
}

long long count_tastiness(long long x, std::vector<long long> a) {
    a.resize(128, 0);
    //cerr << "a: "; for (int i=0; i<a.size(); ++i) cerr << a[i] << ' '; cerr << endl;
    ll add = 0;
    for (int i=0; i<a.size(); ++i) {
        a[i] += add;
        add = max(0LL, (a[i] - x) >> 1);
        a[i] -= add << 1;
    }
    if (x == 1) {
        return sub2(x, a);
    }

    ll ans = 0;
    for (int y=0; y<=100000; ++y) {
        ll carry = 0;
        bool ok = true;
        for (int i=0; i<62; ++i) {
            ll cur = a[i] + carry;
            if (y & (1LL << i)) {
                if (cur < x) {
                    ok = false;
                    break;
                }
                cur -= x;
            }
            carry = cur >> 1;
        }
        if (ok) {
            ++ans;
            //cerr << "y: " << y << '\n';
        }
    }
    
    return ans;
}

/*
2
3 3
5 2 1
3 2
2 1 2

1
5 1
0 1 1 1 2

1
4 1
1 5 2 9

1
5 1
0 0 0 1 0

1
1 1
128
*/
