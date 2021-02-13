//robdan.cpp created at 02/07/21 12:07:55
// mmk 3/10 since idk how to do prefix lcm with large numbers
// oh lmao i resubmitted with int128 and got AC
// 1:36:54 remaining
// 1:26pm

#include <bits/stdc++.h>

using namespace std;

#define fi first
#define se second

typedef __int128 ll;
typedef pair<ll,ll> pii;
typedef pii pll;

const int MN = 100005;

int N;
int A[MN];

int par[MN];
int sz[MN];
int root(const int u) {
    return u == par[u] ? u : par[u] = root(par[u]);
}
void join(const int u, const int v) {
    int ru = root(u), rv = root(v);
    if (ru == rv) return;

    if (sz[ru] < sz[rv]) swap(ru, rv);
    par[u] = par[v] = par[rv] = par[ru];
    sz[ru] += sz[rv];
}

void chmn(pll& a, const pll& b) {
    if (a.fi * b.se > a.se * b.fi) a=b;
}
void chmn(ll& a, const ll& b) {
    if (a > b) a=b;
}

ll gcd(const ll a, const ll b) {
    return b ? gcd(b, a%b) : a;
}
ll gcd(const ll a, const ll b, const ll c) {
    return gcd(a, gcd(b, c));
}
ll lcm(const ll a, const ll b) {
    return (a / gcd(a, b)) * b;
}

int main() {
    freopen("robdan.in", "r", stdin);
    freopen("robdan.out", "w", stdout);
    cin.tie(0)->sync_with_stdio(0);

    cin >> N;
    for (int i=0; i<N; ++i) {
        cin >> A[i];
        --A[i];
    }
    for (int i=0; i<N; ++i) {
        par[i] = i;
        sz[i] = 1;
    }

    for (int i=0; i<N; ++i) {
        join(i, A[i]);
    }

    set<int> roots;
    for (int i=0; i<N; ++i) {
        roots.insert(root(i));
    }

    map<ll,ll> mct;
    for (const int r: roots) {
        ++mct[sz[r]];
    }
    vector<pll> ct;
    for (const pii& p: mct) ct.push_back(p);
    assert(ct.size() > 0);
    assert(ct.size() < 1e3);
    // should be around sqrt(N)

    //cerr << "roots:"; for (const int r: roots) { cerr << ' ' << r; } cerr << endl;
    //cerr << "ct:"; for (const pii& p: ct) { cerr << " (" << p.fi << ' ' << p.se << ')'; } cerr << endl;

    //vector<ll> pgcd, sgcd;
    //pgcd.push_back(ct[0].fi);
    //sgcd.push_back(ct.back().fi);
    //for (int i=0; i<ct.size(); ++i) {
    //    pgcd.push_back(gcd(pgcd.back(), ct[i].fi));
    //}
    //for (int i=ct.size() - 1; i>=0; --i) {
    //    sgcd.push_back(gcd(sgcd.back(), ct[i].fi));
    //}
    //reverse(sgcd.begin(), sgcd.end());
    //assert(pgcd.size() == sgcd.size());
    //cerr << "pgcd:"; for (const ll x: pgcd) { cerr << ' ' << x; } cerr << endl;
    //cerr << "sgcd:"; for (const ll x: sgcd) { cerr << ' ' << x; } cerr << endl;
    ll old = 1; // partials
    for (int i=0; i<ct.size(); ++i) {
        old = lcm(old, ct[i].fi);
    }

    ll best = old;
    // split
    for (int i=0; i<ct.size(); ++i) {
        if (ct[i].se > 1) continue;
        for (ll x=1; x<ct[i].fi; ++x) {
            const ll y = ct[i].fi - x;

            ll cur = lcm(x, y);
            for (const pll& p: ct) {
                if (ct[i] == p) continue;
                cur = lcm(cur, p.fi);
            }

            chmn(best, cur);
        }
    }

    // merge
    for (int i=0; i<ct.size(); ++i) {
        for (int j=i; j<ct.size(); ++j) {
            ll cur = ct[i].fi + ct[j].fi;
            for (const pll& p: ct) {
                if (p == ct[i] && p.se == 1) continue;
                if (p == ct[j] && p.se == 1) continue;
                cur = lcm(cur, p.fi);
            }
            chmn(best, cur);
        }
    }

    ll g = gcd(best, old);
    best /= g;
    old /= g;

    long long y = best;
    long long x = old;
    cout << y << ' ' << x << endl;
}

/*
Merge cycles
Split cycles

2 2 2 9 11 11 11

Try merging all cycle lengths

WRONG: We should only deal with cycles of unique lengths
Splitting duplicate won't decrease LCM
Merging 2 dupes won't decrease
Merging 1 dupe and 1 unique is never more optimal than splitting the unique
    If the sum is unique, we would have been better off doing nothing
*/

