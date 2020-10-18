#include <bits/stdc++.h>

using namespace std;

typedef pair<int,bool> pib;

int N;
set<pib> events;

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> N;
    for (int i=0; i<N; ++i) {
        int x;
        cin >> x;
        events.emplace(x, true);
        cin >> x;
        events.emplace(x, false);
    }

    int ans = 0;
    int cur = 0;
    for (auto it=events.begin(); it!=events.end(); ++it) {
        if (it->second) ++cur;
        else --cur;

        ans = max(ans, cur);
    }
    cout << ans << endl;
}
