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

    int n;
    cin >> n;

    vector<vi> e(n + 1);
    for (int i = 0; i < n; i++) {
        int x, y;
        cin >> x >> y;
        e[x].push_back(y);
        e[y].push_back(x);
    }


    vi ord(n + 1, -1), p(n + 1);
    int t = 0;
    queue<int> Q({0});
    ord[0] = t++;
    while (!Q.empty()) {
        int x = Q.front();
        Q.pop();

        for (int y : e[x]) {
            if (ord[y] != -1) continue;
            ord[y] = t++;
            p[ord[y]] = ord[x];
            Q.push(y);
        }
    }

    
    vector<vi> sol = {{0, 1}};
    for (int i = 1; i < n; i++) {
        int k = sol.size();
        for (int j = 0; j < k; j++) {
            sol.push_back(sol[j]);
            for (auto& x : sol.back())
                x ^= 1 ^ (1 << i);
        }

        for (auto& v : sol)
            v.push_back(v[p[i + 1]] ^ (1 << i));
    }


    cout << sol.size() << '\n';
    for (auto& v : sol) {
        for (int i = 0; i <= n; i++)
            cout << v[ord[i]] << ' ';
        cout << '\n';
    }

    return 0;
}

