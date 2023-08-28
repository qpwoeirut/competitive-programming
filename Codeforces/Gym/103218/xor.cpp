//xor.cpp created at 08/14/21 15:28:35

#include <bits/stdc++.h>

using namespace std;

#define fi first
#define se second

using pii=pair<int,int>;

int N, Q;
int BITS = 30;
set<int> ans;

vector<int> SECRET(1);

int query(const int y) {
    ++Q;

    cout << "? " << y << endl;
    if (!SECRET.empty()) {
        pii ret(1<<BITS, 0);
        for (const int x: SECRET) {
            ret = min(ret, pii(x ^ y, x));
        }
        return ret.se;
    }

    int x;
    cin >> x;
    assert(x != -1);
    return x ^ y;
}

int get_bit(const int x) {
    for (int i=0; i<30; ++i) {
        if (x & (1 << i)) return i;
    }
    assert(false);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> N;

    if (N > 600) BITS = 15;

    if (!SECRET.empty()) {
        set<int> nums;
        while (nums.size() < N) nums.insert(rand() % (1 << BITS));
        SECRET = vector<int>(nums.begin(), nums.end());
        for (const int x: SECRET) { cerr << x << ' '; } cerr << endl;
    }

    Q = 0;
    const int min_val = query(0);
    ans.insert(min_val);

    queue<pii> q;
    for (int i=0; i<BITS; ++i) {
        int resp = query(1 << i);
        if (resp != min_val) {
            ans.insert(resp);
            q.emplace(1 << i, resp);
        }
    }

    while (q.size() > 0 && ans.size() < N) {
        const pii cur = q.front(); q.pop();

        int bit = get_bit(cur.fi);

        while (bit > 0) {
            const int x = query(cur.fi | ((1 << bit) - 1));
            if (x == cur.se) {
                break;
            }

            while (bit > 0 && (cur.fi >> (bit + 0)) == (x >> (bit + 0))) --bit;

            ans.insert(x);
            const int y = query(cur.fi | (1 << bit));
            if (x != y) {
                ans.insert(y);
                q.emplace(cur.fi | (1 << bit), y);
            }

            --bit;
        }
    }

    cout << '!';
    for (const int x: ans) {
        cout << ' ' << x;
    }
    cout << endl;

    if (!SECRET.empty()) {
        for (const int x: SECRET) assert(ans.count(x) == 1);
        cerr << Q << endl;
        assert(Q <= 20000);
    }
}

