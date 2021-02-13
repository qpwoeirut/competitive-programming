//1416c.cpp created at 01/27/21 11:29:34

#include <bits/stdc++.h>

using namespace std;

const int MN = 300005;

int N;
int A[MN];

vector<vector<int>> groups[2];

int main() {
    cin.tie(0)->sync_with_stdio(0);

    groups[0].push_back(vector<int>());

    cin >> N;
    for (int i=0; i<N; ++i) {
        cin >> A[i];
        groups[0][0].push_back(A[i]);
    }

    long long ans = 0, x = 0;
    for (int i=30; i>=0; --i) {
        //cerr << i << ' ' << ans << ' ' << x << endl;
        
        //for (const vector<int>& group: groups[i&1]) { for (const int j: group) { cerr << j << ' '; } cerr << endl; }
        long long ct[2] = {0,0};
        groups[!(i&1)].clear();
        for (const vector<int>& group: groups[i&1]) {
            vector<int> nxt[2];
            for (const int j: group) {
                ct[(j >> i) & 1] += nxt[!((j >> i) & 1)].size();
                nxt[(j >> i) & 1].push_back(j);
            }
            for (int k=0; k<2; ++k) {
                if (nxt[k].size() > 0) {
                    groups[!(i&1)].push_back(nxt[k]);
                }
            }
        }
        if (ct[0] <= ct[1]) {
            ans += ct[0];
        } else {
            ans += ct[1];
            x += (1 << i);
        }
        //cerr << ct[0] << ' ' << ct[1] << endl << endl;
    }

    cout << ans << ' ' << x << endl;
}

