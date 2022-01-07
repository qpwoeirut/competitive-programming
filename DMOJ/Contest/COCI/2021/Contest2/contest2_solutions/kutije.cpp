#include <bits/stdc++.h>
using namespace std;

#define TRACE(x) cerr << __LINE__ << ": " << #x << " = " << x << endl
#define _ << " _ " <<

template<class> struct is_container : false_type {};
template<class... Ts> struct is_container<vector<Ts...>> : true_type {};
template<class... Ts> struct is_container<map<Ts...>> : true_type {};
template<class... Ts> struct is_container<unordered_map<Ts...>> : true_type {};
template<class... Ts> struct is_container<set<Ts...>> : true_type {};
template<class... Ts> struct is_container<unordered_set<Ts...>> : true_type {};
template<class... Ts> struct is_container<multiset<Ts...>> : true_type {};
template<class... Ts> struct is_container<unordered_multiset<Ts...>> : true_type {};
template<class T, class = typename enable_if<is_container<T>::value>::type>
ostream& operator<<(ostream &o, T x) {
  int f = 1;
  o << "{";
  for (auto y : x) {
    o << (f ? "" : ", ") << y;
    f = 0;
  }
  return o << "}";
}
template<class T, class U>
ostream& operator<<(ostream &o, pair<T, U> x) {
  return o << "(" << x.first << ", " << x.second << ")";
}

#define fi first
#define se second

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
typedef vector<ll> vll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n, m, q;
    cin >> n >> m >> q;
    vector<vi> e(n, vi(m));
    for (int j = 0; j < m; j++)
        for (int i = 0; i < n; i++) {
            cin >> e[i][j];
            e[i][j]--;
        }

    vi comp(n, -1);
    for (int i = 0; i < n; i++) {
        if (comp[i] != -1) continue;
        queue<int> Q({i});
        while (!Q.empty()) {
            int x = Q.front();
            Q.pop();
            if (comp[x] == i) continue;
            comp[x] = i;
            for (int y : e[x]) Q.push(y);
        }
    }

    while (q--) {
        int x, y;
        cin >> x >> y;
        x--; y--;
        if (comp[x] == comp[y]) cout << "DA\n";
        else cout << "NE\n";
    }

    return 0;
}

