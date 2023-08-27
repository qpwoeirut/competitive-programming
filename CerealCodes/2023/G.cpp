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

int main() {
    iostream::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin >> t;
    while (t--) {
        ll k;
        //cin >> k;
        k = 1e18 - t;

        if (k == 0) {
            cout << "1 1\n1\n1 1\n";
            continue;
        }
        ll sz = 64;
        // while ((1LL << sz) < min(k, LLONG_MAX / 16) * 16) sz *= 2;
        // cerr << sz << "\n";
        vector<vector<bool>> grid(sz, vector<bool>(sz, 0));
        for (int i = 0; i < sz; ++i) {
            for (int j = 0; j < sz; ++j) {
                if (i + j >= sz) {
                    grid[i][j] = 1;
                    continue;
                }
                if (min(i, j) == 0) grid[i][j] = 1;
                else grid[i][j] = grid[i - 1][j] ^ grid[i][j - 1];
            }
        }
        grid[sz - 1][0] = 0;
        grid[0][sz - 1] = 0;
        grid[sz - 2][2] = 0;
        grid[2][sz - 2] = 0;
        grid[sz - 1][1] = 0;
        if (k % 2 == 0) grid[1][sz - 1] = 0;

        // for (int i = 0; i < sz; ++i) {
        //     for (int j = 0; j < sz; ++j) {
        //         cout << (grid[i][j] ? '.' : ' ');
        //     }
        //     cout << "\n";
        // }

        // cerr << "a\n";

        for (int i = 1; i < sz - 2; ++i) {
            if (k & (1LL << i)) {
                if (i % 2) {
                    grid[sz - 2][i + 2] = 1;
                    grid[i + 2][sz - 2] = 0;
                } else {
                    grid[i + 2][sz - 2] = 1;
                    grid[sz - 2][i + 2] = 0;
                }
            } else {
                grid[i + 2][sz - 2] = 0;
                grid[sz - 2][i + 2] = 0;
            }
        }
        // cerr << "b\n";
        for (int i = 2; i < sz; ++i) {
            grid[i][sz - 1] = grid[sz - 1][i] = 1;
        }
        
        // cout << "\n";
        //cout << sz << " " << sz << "\n";
        //for (int i = 0; i < sz; ++i) {
        //    for (int j = 0; j < sz; ++j) {
        //        cout << (grid[i][j] ? '.' : '#');
        //    }
        //    cout << "\n";
        //}
        vector<pair<int, int>> v;
        for (int i = 0; i < sz; ++i) {
            for (int j = 0; j < sz; ++j) {
                if (!grid[i][j]) v.push_back(pair<int, int>{i, j});
            }
        }
        //cout << v.size() << "\n";
        for (pair<int, int> p : v) {
            //cout << p.first + 1 << " " << p.second + 1 << "\n";
        }


        vector<vector<ll>> count(sz, vector<ll>(sz));
        for (int i = 0; i < sz; ++i) {
            for (int j = 0; j < sz; ++j) {
                if (i == j && j == 0) count[i][j] = grid[i][j];
                else if (i == 0) count[i][j] = grid[i][j] ? count[i][j - 1] : 0;
                else if (j == 0) count[i][j] = grid[i][j] ? count[i - 1][j] : 0;
                else count[i][j] = grid[i][j] ? count[i - 1][j] + count[i][j - 1] : 0;
            }
        }
        assert(count[sz-1][sz-1] == k);

        //cout << count << "\n";
        
    }
}
