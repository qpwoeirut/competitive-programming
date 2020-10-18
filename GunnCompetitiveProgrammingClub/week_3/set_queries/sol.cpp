#include <bits/stdc++.h>

using namespace std;

int N, Q;
set<int> s;
int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin >> N >> Q;

    for (int i=0; i<N; ++i) {
        int a;
        cin >> a;
        s.insert(a);
    }

    for (int i=0; i<Q; ++i) {
        int t, x;
        cin >> t;
        if (t == 3) {
            cout << s.size() << '\n';
            continue;
        }
        cin >> x;
        if (t == 1) {
            s.insert(x);
        } else if (t == 2) {
            s.erase(x);
        } else if (t == 4) {
            cout << s.count(x) << '\n';
        } else assert(false);
    }
}
