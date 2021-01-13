/*
ID: zhongbr1
TASK: shuttle
LANG: C++14
*/

//shuttle.cpp created at 01/02/21 19:35:33

#include <bits/stdc++.h>

using namespace std;

#define fi first
#define se second

typedef long long ll;
typedef pair<int,ll> pii;

const int MN = 12;

int N, M;
int arr[25];

void unpack(ll state) {
    for (int i=M-1; i>=0; --i) {
        arr[i] = state & 3;
        state >>= 2;
    }
}
ll pack() {
    ll state = 0;
    for (int i=0; i<M; ++i) {
        state <<= 2;
        state += arr[i];
    }
    return state;
}
        

map<ll,pii> path;

int main() {
    freopen("shuttle.in", "r", stdin);
    freopen("shuttle.out", "w", stdout);
    cin.tie(0)->sync_with_stdio(0);

    cin >> N;
    M = N + N + 1;

    for (int i=0; i<N; ++i) {
        arr[i] = 0;
    }
    arr[N] = 1;
    for (int i=N+1; i<M; ++i) {
        arr[i] = 2;
    }
    const ll start = pack();

    for (int i=0; i<N; ++i) {
        arr[i] = 2;
    }
    arr[N] = 1;
    for (int i=N+1; i<M; ++i) {
        arr[i] = 0;
    }
    const ll finish = pack();

    queue<ll> q;
    q.push(start);
    path[start] = pii(-1, -1);

    while (q.size() > 0) {
        const ll cur = q.front(); q.pop();
        unpack(cur);
        const int hole = find(arr, arr+M, 1) - arr;

        //cerr << "arr: "; for (int i=0; i<M; ++i) { cerr << arr[i] << ' '; } cerr << endl;
        //cerr << "hole: " << hole << endl;

        for (int i=max(0, hole-2); i<=hole+2 && i<M; ++i) {
            if (i == hole) continue;
            if ((i < hole) ^ (arr[i] < arr[hole])) continue;
            //cerr << i << endl;
            swap(arr[i], arr[hole]);

            const ll state = pack();
            //cerr << state << endl;
            auto it = path.find(state);
            //if (it != path.end()) cerr << "it: " << it->fi << ' ' << it->se.fi << ' ' << it->se.se << endl;
            if (it == path.end() || it->se.fi > i) {
                path[state] = pii(i, cur);
                q.push(state);
            }

            swap(arr[i], arr[hole]);
        }
    }

    ll cur = finish;
    assert(path.count(cur) > 0);
    vector<int> ans;
    while (path[cur].fi != -1) {
        const pii p = path[cur];
        //cerr << cur << ' ' << p.fi << ' ' << p.se << endl;
        ans.push_back(p.fi + 1);
        cur = p.se;
        assert(path.count(cur) > 0);
    }
    reverse(ans.begin(), ans.end());

    for (int i=0; i<ans.size(); ++i) {
        if (i) {
            if (i % 20) {
                cout << ' ';
            } else {
                cout << '\n';
            }
        }

        cout << ans[i];
    }
    cout << endl;
}

