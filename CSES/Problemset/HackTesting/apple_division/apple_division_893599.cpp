// https://cses.fi/problemset/hack/1623/entry/893599/

/*
 *   Author: TH Huang
 *
 *   Compile:
 *       docker run --rm -it -v $(pwd):/app tzuhsuanhuang/cp g++ -std=c++17 -O2 -Wall -o main -x c++ main.cpp
 *   Execute:
 *       docker run --rm -it -v $(pwd):/app tzuhsuanhuang/cp ./main
 *
 */

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define MOD 1000000007LL
#define EPS 1e-9
#define PI 3.1415926535897932384626433832795

inline void solve() {
    int n;
    cin >> n;

    int x;
    unordered_set<ll> dp = {0};
    for (int i = 0; i < n; ++i) {
        cin >> x;
        unordered_set<ll> s;
        for (auto v : dp) {
            s.insert(v + x);
            s.insert(v - x);
        }
        dp = s;
    }
    ll ans = abs(*dp.begin());
    for (auto v : dp) {
        ans = min(ans, abs(v));
    }
    cout << ans << endl;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    solve();

    return 0;
}

