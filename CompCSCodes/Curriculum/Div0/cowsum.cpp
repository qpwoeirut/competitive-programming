//cowsum.cpp created at 11/12/20 12:15:58

#include <bits/stdc++.h>

using namespace std;

// problem suggests to make a struct, so here it is
struct Cow {
    int attr[4];
};

int N, T;
Cow cow[51];
int ans[4];

int main() {
    freopen("cowsum.in", "r", stdin);
    freopen("cowsum.out", "w", stdout);
    
    fill(ans, ans+4, -1);

    cin >> N >> T;
    for (int i=0; i<N; ++i) {
        int A[4];
        int ti, tj;
        for (int j=0; j<4; ++j) {
            cin >> A[j];
        }
        cin >> ti >> tj;

        if (ti <= T && T < tj) {
            for (int j=0; j<4; ++j) {
                ans[j] = max(ans[j], A[j]);
            }
        }
    }

    for (int i=0; i<4; ++i) {
        cout << ans[i] << endl;
    }
}

