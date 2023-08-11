#define print_debug true

#include "bits/stdc++.h"

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

const long long MOD = 1000000007;

using namespace __gnu_pbds;
using namespace std;

typedef tree<int, null_type, less<int>, rb_tree_tag,
             tree_order_statistics_node_update>
    indexed_set;

typedef long long ll;

template<typename T> istream& operator>>(istream& in, vector<T>& a) {for(auto &x : a) in >> x; return in;};
template<typename T1, typename T2> istream& operator>>(istream& in, pair<T1, T2>& x) {return in >> x.first >> x.second;}

template<typename T1, typename T2> ostream& operator<<(ostream& out, const pair<T1, T2>& x) {return out << x.first << ' ' << x.second;}
template<typename T> ostream& operator<<(ostream& out, vector<T>& a) {for(auto &x : a) out << x << ' '; return out;};
template<typename T> ostream& operator<<(ostream& out, vector<vector<T>>& a) {for(auto &x : a) out << x << '\n'; return out;};
template<typename T1, typename T2> ostream& operator<<(ostream& out, vector<pair<T1, T2>>& a) {for(auto &x : a) out << x << '\n'; return out;};

void fileIO(string name) {
    freopen((name + ".in").c_str(), "r", stdin);
    freopen((name + ".out").c_str(), "w", stdout);
}

bool good = true;
int ind = 0;
map<int, int> m;
vector<vector<int>> new_adj;
bool dfs(int node, int p, vector<vector<int>>& adj) {
    int uncovered = -1;
    for (int ne : adj[node]) {
        if (ne == p) continue;
        if (dfs(ne, node, adj)) {
            if (uncovered == -1) {
                uncovered = ne;
            }
            else {
                good = false;
            }
        }
    }

    if (uncovered == -1) return true;
    else {
        m[node] = ind;
        for (int ne : adj[uncovered]) {
            if (ne == node) continue;
            new_adj[ind].push_back(m[ne]);
            new_adj[m[ne]].push_back(ind);
        }
        ind++;
        return false;
    }
}

bool check_good(vector<vector<int>> adj) {
    // cerr << adj << "\n";
    if (adj.size() == 1) return true;
    good = true;
    new_adj.clear();
    new_adj.resize(adj.size() / 2);
    m.clear();
    ind = 0;
    dfs(0, -1, adj);
    if (!good) return false;
    adj = new_adj;
    // cerr << new_adj << "\n";
    return check_good(adj);
}

int main() {
    iostream::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while (t--) {
        vector<vector<int>> adj = {{}};
        int q;
        cin >> q;
        for (int i = 0; i < q; ++i) {
            int a;
            cin >> a;
            a--;
            adj.push_back({});
            adj[a].push_back(i + 1);
            adj[i + 1].push_back(a);
            // check if i + 2 is power of 2
            int r = 1;
            while (r < i + 2) r *= 2;
            if (r == i + 2) {
                cout << (check_good(adj) ? "YES\n" : "NO\n");
            } else {
                cout << "NO\n";
            }
        }
    }

}
