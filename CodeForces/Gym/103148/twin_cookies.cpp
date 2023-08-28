//twin_cookies.cpp created at 08/29/21 17:39:44

#include <bits/stdc++.h>

using namespace std;

using ll=long long;

const ll X = 1e13;
const ll M = 100;

int N;
vector<ll> nums;

const bool DEBUG = false;

mt19937 rng(8);

ll query_range(const ll lo, const ll hi) {
    cout << '?';
    for (ll i=lo; i<hi; ++i) {
        cout << ' ' << i;
    }
    cout << endl;
    ll resp = lo;
    if (!DEBUG) cin >> resp;
    return resp;
}

ll query_list(const set<ll>& nums) {
    cout << '?';
    for (const ll x: nums) {
        cout << ' ' << x;
    }
    cout << endl;
    ll resp = *nums.begin();
    if (!DEBUG) cin >> resp;
    return resp;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> N;
    for (int i=0; i<M; ++i) {
        const ll r = rng() % X;
        nums.push_back(query_range(r, r+N));
    }

    set<ll> candidates;
    for (int i=0; i<M; ++i) {
        for (int j=i+1; j<M; ++j) {
            for (int k=j+1; k<M; ++k) {
                candidates.insert(nums[i] + nums[j] + nums[k]);
                if (candidates.size() == N) break;
            }
            if (candidates.size() == N) break;
        }
        if (candidates.size() == N) break;
    }

    cerr << candidates.size() << endl;

    assert(candidates.size() == N);

    ll ans = query_list(candidates);
    for (int i=0; i<M; ++i) {
        for (int j=i+1; j<M; ++j) {
            for (int k=j+1; k<M; ++k) {
                if (ans == nums[i] + nums[j] + nums[k]) {
                    cout << "! 3 1\n";
                    cout << nums[i] << ' ' << nums[j] << ' ' << nums[k] << '\n';
                    cout << ans << endl;
                    return 0;
                }
            }
        }
    }

    assert(0);
}

