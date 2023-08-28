//factorial.cpp created at 08/06/21 10:40:34
// should not get full score, only got AC b/c of polygon partial scoring limitation

#include <bits/stdc++.h>

using namespace std;

using ll = long long;

#define pb push_back

const int MN = 40051; //1000000001;

int fac[MN];

int Q = 0;

const int PN = 25;

ll PRIMES[PN] = {
    999999937, 999999929, 999999893, 999999883, 999999797,
    999999761, 999999757, 999999751, 999999739, 999999733,
    999999677, 999999667, 999999613, 999999607, 999999599,
    999999587, 999999541, 999999527, 999999503, 999999491,
    999999487, 999999433, 999999391, 999999353, 999999337,
    //999999323, 999999229, 999999223, 999999197, 999999193,
    //999999191, 999999181, 999999163, 999999151, 999999137,
    //999999131, 999999113, 999999107, 999999103, 999999067,
    //999999059, 999999043, 999999029, 999999017, 999999001,
    //999998981, 999998971, 999998959, 999998957, 999998929,
    //999998921, 999998917, 999998903, 999998869, 999998863,
    //999998843, 999998801, 999998789, 999998777
};

ll f[MN][PN];

int SECRET = -1;

bool query(const int a, const int b) {
    ++Q;
    assert(Q <= 100); // smol brane moment

    cout << "? " << a << ' ' << b << endl;
    if (SECRET != -1) {
        ll x = 1;
        for (int i=2; i<=SECRET; ++i) x = (x * i) % b;
        return (x + a) % b == 0;
    }

    string answer;
    cin >> answer;

    assert(answer != "ERROR");
    return answer == "SI";
}

vector<int> primes;
void init() {
    fill(fac, fac+MN, 1);
    for (ll i=2; i<MN; ++i) {
        if (fac[i] == 1) {
            for (ll j=i*i; j<MN; j+=i) {
                fac[j] = i;
            }
        }
    }

    for (int i=1; i<MN; ++i) {
        if (fac[i] == 1) primes.pb(i);
    }

    assert(primes.size() > 0);

    for (int i=0; i<PN; ++i) {
        f[0][i] = f[1][i] = 1;
    }
    for (int i=2; i<MN; ++i) {
        for (int j=0; j<PN; ++j) {
            f[i][j] = (f[i-1][j] * i) % PRIMES[j];
        }
    }
}

int solve() {
    int lo = 0, hi = primes.size() - 1;
    while (lo < hi) {
        int mid = (lo + hi + 1) >> 1;
        if (query(primes[mid], primes[mid])) {
            lo = mid;
        } else {
            hi = mid - 1;
        }
    }

    set<int> possible;
    for (int i=primes[lo]; i<primes[lo+1]; ++i) {
        possible.insert(i);
    }
    //cerr << "lo,p,p+1: " << lo << ' ' << primes[lo] << ' ' << primes[lo+1] << endl;

    int pi = 0;
    while (possible.size() > 1) {
        const ll cur = *possible.begin();
        //cerr << "cur,sz: " << cur << ' ' << possible.size() << endl;

        bool ok = query(PRIMES[pi] - f[cur][pi], PRIMES[pi]);
        if (ok) {
            for (auto it = possible.begin(); it!=possible.end();) {
                if (f[*it][pi] != f[cur][pi]) it = possible.erase(it);
                else ++it;
            }
            pi = (pi + 1) % PN;
        } else {
            possible.erase(cur);
        }
    }

    assert(possible.size() == 1);

    return *possible.begin();
}

void test() {
    for(SECRET=19656; SECRET<=40000; ++SECRET) {
        Q = 0;
        const int x = solve();
        if ((x & 2047) == 0 || 1) cerr << x << endl;
        assert(SECRET == x);
    }
}

int main() {
    init();
    //test();
    ll ans = solve();  // even more smol brane moment
    cout << "! " << ans << endl;
}

