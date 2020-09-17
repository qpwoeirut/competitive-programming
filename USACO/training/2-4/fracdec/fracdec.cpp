/*
ID: zhongbr1
TASK: fracdec
LANG: C++11
*/

#include <bits/stdc++.h>

using namespace std;

const int MN = 100001;

int idx[MN];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    freopen("fracdec.in", "r", stdin);
    freopen("fracdec.out", "w", stdout);

    int N, D;
    cin >> N >> D;

    int whole = N / D;
    N %= D;

    set<int> seen;
    string cur = "";

    while (N != 0 && seen.find(N) == seen.end()) {
        seen.insert(N);

        idx[N] = cur.size();

        N *= 10;
        cur.push_back((char)(N/D) + '0');
        N %= D;
    }

    string ans;
    if (seen.find(N) != seen.end()) {
        ans = to_string(whole) + '.' + (cur.substr(0, idx[N]) + '(' + cur.substr(idx[N]) + ')');
    }
    else {
        ans = to_string(whole) + '.' + cur;
    }
    if (ans.back() == '.') {
        ans.push_back('0');
    }

    for (int i=0; i<ans.size(); i+=76) {
        cout << ans.substr(i, 76) << endl;
    }
}
