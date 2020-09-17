/*
ID: zhongbr1
TASK: agrinet
LANG: C++11
*/

#include <bits/stdc++.h>

using namespace std;

#define FI first
#define SE second

typedef pair<int,int> pii;

struct cmpf {
    inline const bool operator()(const pii& a, const pii& b) {
        return a.FI > b.FI;
    }
};

int mat[101][101];
bool in[101];
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    freopen("agrinet.in", "r", stdin);
    freopen("agrinet.out", "w", stdout);

    int N;
    cin >> N;

    for (int i=0; i<N; i++) {
        for (int j=0; j<N; j++) {
            cin >> mat[i][j];
        }
    }

    priority_queue<pii, vector<pii>, cmpf> pq;
    pq.push(pii(0,0));

    int ans = 0;
    while (pq.size() > 0) {
        pii cur = pq.top();
        pq.pop();
        
        if (in[cur.SE]) {
            continue;
        }
        ans += cur.FI;
        in[cur.SE] = true;

        for (int i=0; i<N; i++) {
            if (!in[i]) {
                pq.push(pii(mat[cur.SE][i], i));
            }
        }
    }

    cout << ans << endl;
}
