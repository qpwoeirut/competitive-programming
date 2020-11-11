#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MN = 10001; // maxn for subtask 5
const int MK = 201;

int N, K;
ll A[MN], pref[MN];

ll dp[2][MN];
int path[MK][MN];

bool chmx(ll& a, const ll b) {return (a < b) ? (a=b), true : false;}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> N >> K;
    for (int i=0; i<N; ++i) {
        cin >> A[i];
        pref[i+1] = pref[i] + A[i];
    }

    for (int k=1; k<=K; ++k) {
        for (int i=0; i<N; ++i) {
            dp[k&1][i] = -1;
            ll left = 0, right = pref[N] - pref[i];
            for (int j=i; j+1<N; ++j) {
                left += A[j];
                right -= A[j];
                //cerr << "k,i,j,L,R: " << k << ' ' << i << ' ' << j << ' ' << left << ' ' << right << endl;
                if (chmx(dp[k&1][i], dp[!(k&1)][j+1] + left * right)) {
                    path[k][i] = j+1;
                }
            }
        }
    }

    cout << dp[K&1][0] << endl;
    vector<int> ans;
    ans.push_back(path[K][0]);
    for (int i=K-1; i>0; --i) {
        ans.push_back(path[i][ans.back()]);
    }
    for (int i=0; i<K; ++i) {
        if (i) cout << ' ';
        cout << ans[i];
    }
    cout << endl;
}
/*
7 3
4 1 3 4 0 2 3
*/
