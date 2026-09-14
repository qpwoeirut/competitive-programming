#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using pll = pair<ll, ll>;

ll sq(ll n) {
    return n * n;
}

ll count_triples(const vector<pll>& points) {
    int ct = 0;
    for (int i=0; i<points.size(); ++i) {
        for (int j=i+1; j<points.size(); ++j) {
            ll dx = sq(points[i].first - points[j].first);
            ll dy = sq(points[i].second - points[j].second);
            ll lo = 0, hi = 2e9;
            while (lo < hi) {
                ll mid = (lo + hi) / 2;
                if (mid * mid < dx + dy) lo = mid + 1;
                else hi = mid;
            }
            ct += lo * lo == dx + dy;
        }
    }
    return ct;
}

mt19937 rng(8);
vector<pll> random_points(int N) {
    set<pll> pts;
    pts.emplace(0, 0);
    while (pts.size() < N) {
        pts.emplace(rng() % 8, rng() % 8);
    }
    return vector<pll>(pts.begin(), pts.end());
}

ll pairs(ll n) {
    return n * (n - 1) / 2;
}

vector<pll> solve(int N, int K) {
    if (N <= 6) {
        vector<pll> pts;
        do {
            pts = random_points(N);
        } while (count_triples(pts) != K);
        return pts;
    }
    vector<int> stacks({1});
    int n = 1, k = 0;
    while (n < N) {
        if (k + pairs(stacks.back() + 1) - pairs(stacks.back()) <= K) {
            k += pairs(stacks.back() + 1) - pairs(stacks.back());
            ++stacks.back();
            ++n;
        }
        else {
            stacks.push_back(1);
            ++n;
        }
    }
    vector<pll> pts;
    int y = 0;
    for (int x=0; x<stacks.size(); ++x) {
        for (int y_i=0; y_i<stacks[x]; ++y_i, ++y) {
            pts.emplace_back(x, y);
        }
        y += 1000;
    }
    
    return pts;
}

void test() {
    for (int N=1; N<=100; ++N) {
        cout << N << endl;
        for (int K=0; K <= N * (N - 1) / 2 && K<=N; ++K) {
            vector<pll> ans = solve(N, K);
            assert(ans.size() == N);
            ll ct = count_triples(ans);
            if (ct != K) {
                cout << "-----\n";
                cout << N << ' ' << K << '\n';
                cout << ct << '\n';
                for (const pll& p: ans) {
                    cout << p.first << ' ' << p.second << '\n';
                }
                cout << endl;
                assert(false);
            }
        }
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    //test(); return 0;
    
    int N, K;
    cin >> N >> K;
    vector<pll> ans = solve(N, K);
    for (const pll& p: ans) {
        cout << p.first << ' ' << p.second << '\n';
    }
}
