#include <bits/stdc++.h>

using namespace std;

const int MX = 1100;

int T;
int B, M;
int C;
string s, t;
int ct[2][MX];
int cur[MX];

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> T;
    cin >> B >> M;
    const int space = (B >> 1) / M;
    while (true) {
        cin >> C;
        if (C == 0) break;

        for (int j=0; j<=M; ++j) {
            ct[0][j] = ct[1][j] = 0;
        }

        cin >> s;
        for (int i=0; i<B; ++i) {
            if (s[i] == '1') {
                ++ct[i+i >= B][i % M];
            }
        }

        for (int j=0; j<M; ++j) {
            cur[j] = ct[0][j] - ct[1][j];
        }

        for (int j=0; j<M; ++j) {
            if (cur[j] < 0) {
                cur[j+1] += (cur[j] - 1) / 2;
                cur[j] %= 2;
                cur[j] += 2;
                cur[j] %= 2;
            } else if (cur[j] > 1) {
                cur[j+1] += cur[j] >> 1;
                cur[j] %= 2;
            }
        }
        assert(cur[M] == 0);
        
        vector<char> ans;
        if (T == 0) {
            cin >> t;
            
            ans = vector<char>(B, '0');

            for (int j=0; j<M; ++j) {
                if (cur[j] < t[j] - '0') {
                    if (j > 0 && ct[0][j] + t[j] - '0' - cur[j] > space) {
                        ct[0][j-1] += (t[j] - '0' - cur[j]) << 1;
                    } else {
                        ct[0][j] += t[j] - '0' - cur[j];
                    }
                } else if (cur[j] > t[j] - '0') {
                    if (j>0 && ct[1][j] - (t[j] - '0' - cur[j]) > space) {
                        ct[1][j-1] -= (t[j] - '0' - cur[j]) << 1;
                    } else {
                        ct[1][j] -= t[j] - '0' - cur[j];
                    }
                }
            }
            //for (int j=0; j<M; ++j) cerr << ct[1][j]; cerr << endl;

            for (int j=0; j<M; ++j) {
                if (ct[0][j] > space) {
                    ans.clear();
                    break;
                }
                for (int k=0, i=j; k<ct[0][j]; ++k, i+=M) {
                    ans[i] = '1';
                }
                if (ct[1][j] > space) {
                    ans.clear();
                    break;
                }
                for (int k=0, i=j; k<ct[1][j]; ++k, i+=M) {
                    ans[i+B/2] = '1';
                }
            }

            if (ans.empty()) {
                cout << 0 << endl;
            } else {
                cout << "1\n";
                for (int i=0; i<ans.size(); ++i) {
                    cout << ans[i];
                }
                cout << endl;
            }
        } else {
            for (int j=0; j<M; ++j) {
                cout << cur[j];
            }
            cout << endl;
        }
    }
}
/*
0
8 4
1
11010000 1101
1
01000000 0100
1
11010000 0001
1
01000000 1011
0

1
8 4
1
11010000
1
01000000
1
11011100
1
11110100
0
*/
