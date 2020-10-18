//movie_festival.cpp created at 10/16/20 21:28:54

#include <bits/stdc++.h>

using namespace std;

#define FI first
#define SE second

typedef pair<int,int> pii;

int N;
pii event[200001];

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> N;
    for (int i=0; i<N; ++i) {
        cin >> event[i].FI >> event[i].SE;
    }
    sort(event, event+N, [](const pii& a, const pii& b) {
        if (a.SE == b.SE) return a.FI > b.FI;
        return a.SE < b.SE;
    });

    int ans = 0;
    int pos = 0;
    for (int i=0; i<N; ++i) {
        if (pos > event[i].FI) continue;
        pos = event[i].SE;
        ++ans;
    }

    cout << ans << endl;
}
