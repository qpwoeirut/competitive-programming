#include<bits/stdc++.h>

using namespace std;

typedef long long llint;
typedef pair <int, int> pi;

const int MAXN = 200005;
const int LOG = 18;

int n, q;
int lef[MAXN], rig[MAXN];
int par[MAXN][LOG];
set <pi> st;

bool can_insert (int ind) {
    if (st.empty()) return 1;

    auto it = st.lower_bound({lef[ind], 0});
    int nxt = it -> second;
    if (lef[ind] <= lef[nxt] && lef[nxt] <= rig[ind]) return 0;

    if (it != st.begin()) {
        it--;
        int prv = it -> second;
        if (lef[prv] <= lef[ind] && lef[ind] <= rig[prv]) return 0;
    }

    return 1;
}

void precompute () {
    int lim = 0;
    for (int i = 1; i <= n; i++) {
        if (lim < i) {
            st.clear();
            lim = i;
            st.insert({lef[i], i});
        }

        while (lim + 1 <= n && can_insert(lim + 1)) {
            lim++;
            st.insert({lef[lim], lim});
        }
        par[i][0] = lim + 1;

        st.erase({lef[i], i});
    }
    par[n + 1][0] = n + 1;

    for (int i = 1; i < LOG; i++) {
        for (int j = 1; j <= n + 1; j++) {
            par[j][i] = par[par[j][i - 1]][i - 1];
        }
    }
}

int upit (int a, int b) {
    int res = 0;
    for (int i = LOG - 1; i >= 0; i--) {
        if (par[a][i] <= b) {
            a = par[a][i];
            res += 1 << i;
        }
    }
    return res + 1;
}

int main () {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> lef[i] >> rig[i];
    }
    precompute();
    cin >> q;
    for (int i = 1; i <= q; i++) {
        int a, b;
        cin >> a >> b;
        cout << upit(a, b) << '\n';
    }
    return 0;
}
