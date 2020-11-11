#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int T, K;
string table[10001];
ll ct(string s) {
    set<string> ans;
    const int N = s.size();
    for (int i=1; i<(1 << N); ++i) {
        string t;
        for (int j=0; j<N; ++j) {
            if ((i >> j) & 1) t += s[j];
        }
        ans.emplace(t);
    }
    return ans.size();
}

int L;
void gen(const string s) {
    if (s.size() == L) {
        table[ct(s)] = s;
        return;
    }
    gen(s + '0');
    gen(s + '1');
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin >> T;

    for (L=6; L>0; --L) {
        gen("");
    }

    for (int i=0; i<T; ++i) {
        cin >> K;

        if (table[K].size()) {
            cout << "-1\n" << table[K] << '\n';
        } else {
            cout << "-1\n-1\n";
        }
    }
}
