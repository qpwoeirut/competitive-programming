//cubeword.cpp created at 09/13/20 12:22:10

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const ll MOD = 998244353;

int N;
set<string> words;
char corner[8];
int edge[12][2] = {{0, 1}, {0, 2}, {0, 4}, {1, 3}, {1, 5}, {2, 3}, {2, 6}, {3, 7}, {4, 5}, {4, 6}, {5, 7}, {6, 7}};
ll ct[11][256][256];
ll ans;
void prod(int idx) {
    if (idx == 8) {
        for (int wlen=3; wlen<=10; ++wlen) {
            ll cur = 1;
            for (int i=0; i<12; ++i) {
                cur = (cur * ct[wlen][corner[edge[i][0]]][corner[edge[i][1]]]) % MOD;
            }
            ans = (ans + cur) % MOD;
        }
        return;
    }

    for (char i='a'; i<='f'; ++i) {
        corner[idx] = i;
        prod(idx + 1);
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> N;
    for (int i=0; i<N; ++i) {
        string s;
        cin >> s;
        words.insert(s);
        reverse(s.begin(), s.end());
        words.insert(s);
    }

    for (set<string>::iterator it=words.begin(); it!=words.end(); ++it) {
        ++ct[it->size()][it->at(0)][it->back()];
        if (it->at(0) < 'a' || it->at(0) > 'f' || it->back() < 'a' || it->back() > 'f') {
            assert(false);
        }
    }

    ans = 0;
    prod(0);
    ans %= MOD;

    cout << ans << endl;
}
