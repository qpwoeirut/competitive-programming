//lightsout.cpp created at 11/12/20 19:01:30

#include <bits/stdc++.h>

using namespace std;

#define x first
#define y second

typedef pair<int,int> point;
typedef long long ll;

const int MN = 205;

const ll BASE = 400009;
const int CT = 3;
ll MOD[3] = {(ll)1e9 + 7, (ll)1e9 + 9, (ll)1e9 + 23};

struct Hash {
    ll val[CT];
    ll len;

    Hash() {
        fill(val, val+CT, 0);
        len = 0;
    }
    void add(int n) {
        for (int i=0; i<CT; ++i) {
            val[i] = (val[i] * BASE) % MOD[i];
            val[i] = (val[i] + n + 200000) % MOD[i];
        }
        ++len;
    }

    inline const bool operator<(const Hash& other) const {
        if (len != other.len) {
            return len < other.len;
        }
        for (int i=0; i<CT; ++i) {
            if (val[i] != other.val[i]) {
                return val[i] < other.val[i];
            }
        }
        return false;
    }
};

int N;
point pt[MN];
int best[MN];

int dist(int i) {
    return abs(pt[i].x - pt[i-1].x) + abs(pt[i].y - pt[i-1].y);
}

int angle(int i) {
    point a = pt[i-1], b = pt[i], c = pt[(i+1)%N];

    int dx1 = a.x - b.x, dy1 = a.y - b.y;
    int dx2 = a.x - c.x, dy2 = a.y - c.y;
    if (dx1*dy2 > dx2*dy1) {
        return 90;
    } else if (dx1*dy2 < dx2*dy1) {
        return 270;
    } else assert(false);
}

map<Hash, int> hashes;

const int TMP = 4000000;
bool prime[TMP];
void sieve() {
    for (int i=3; i<TMP; i+=2) prime[i] = true;
    for (int i=3; i<TMP; ++i) {
        if (!prime[i]) continue;
        for (int j=i*3; j<TMP; j+=i) prime[j] = false;
        cout << i << '\n';
    }
}

int main() {
    freopen("lightsout.in", "r", stdin);
    freopen("lightsout.out", "w", stdout);

    cin.tie(0)->sync_with_stdio(0);

    cin >> N;
    for (int i=0; i<N; ++i) {
        cin >> pt[i].x >> pt[i].y;
    }
    pt[N] = pt[0];

    best[0] = best[N] = 0;
    for (int i=1; i<N; ++i) {
        best[i] = best[i-1] + dist(i);
    }
    for (int i=N-1; i>=0; --i) {
        best[i] = min(best[i], best[i+1] + dist(i+1));
    }

    //cerr << "best: "; for (int i=0; i<N; ++i) { cerr << best[i] << ' '; } cerr << endl;

    for (int i=1; i<N; ++i) {
        Hash cur;
        cur.add(angle(i));
        ++hashes[cur];
        for (int j=i+1; j<N; ++j) {
            cur.add(dist(j));
            cur.add(angle(j));
            ++hashes[cur];
        }
    }

    int ans = 0;
    for (int i=1; i<N; ++i) {
        Hash cur;
        cur.add(angle(i));
        if (hashes[cur] == 1) {
            continue;
        }
        int cur_dist = 0;
        bool found = false;
        for (int j=i+1; j<N; ++j) {
            cur_dist += dist(j);
            cur.add(dist(j));
            cur.add(angle(j));
            if (hashes[cur] == 1) {
                ans = max(ans, best[j] + cur_dist - best[i]);
                found = true;
                break;
            }
        }
        if (!found) {
            cur_dist += dist(N);
            ans = max(ans, cur_dist - best[i]);
        }
    }

    cout << ans << endl;
}
