#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;
    vector<int> a(n), b(n);
    for (int i=0; i<n; i++) cin >> a[i];
    for (int i=0; i<n; i++) cin >> b[i];

    map<int,set<int>> mp;
    for (int i=0; i<n; i++) {
        mp[b[i]].insert(i);
    }

    for (auto k: mp) {
        int req = k.first;
        for (auto pos: k.second) {
            int p = pos;
            while (p >= 0 && a[p] != req && a[p] < req && a[p] != b[p]) {
                p--;
            }
            cerr << req << ' ' << p << endl;
            if (p >= 0 && a[p] == req) {
                for (int i=p; i<=pos; i++) {
                    a[i] = req;
                }
            } else {
                p = pos;
                while (p < n && a[p] != req && a[p] < req && a[p] != b[p]) {
                    p++;
                }
                if (p < n && a[p] == req) {
                    for (int i=p; i>=pos; i--) {
                        a[i] = req;
                    }
                }
            }
        }
    }
    for (int i=0; i<n; i++) {
        if (a[i] != b[i]) {
            cout << "no\n";
            return;
        }
    }
    cout << "yes\n";
}

int main() {
    int t;
    cin >> t;
    while (t--) solve();
}

