#include <bits/stdc++.h>

using namespace std;

const int MN = 301;
const int MX = MN * MN;
const int INIT = 1001001001;

#define FI first
#define SE second

typedef pair<int,int> pii;

int N, M, K;
int A[MN], B[MN];
pii kn[MX];

void chmx(pii& a, const pii& b) {
    a = max(a, b);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> N >> M >> K;

    for (int i=0; i<N; ++i) {
        cin >> A[i];
    }
    for (int i=0; i<M; ++i) {
        cin >> B[i];
    }
    if (M < K) {
        cout << "Impossible" << endl;
        return 0;
    }

    int sum = 0;
    for (int i=0; i<N; ++i) {
        sum += A[i];
        if (A[i] < K) {
            cout << "Impossible" << endl;
            return 0;
        }
    }   


    for (int i=0; i<MX; ++i) {
        kn[i] = pii(-1, -1);
    }

    kn[0] = pii(0, 0);
    for (int i=0; i<M; ++i) {
        for (int j=MX-1; j>=B[i]; --j) {
            if (kn[j - B[i]].FI == -1) continue;

            pii cur = kn[j - B[i]];
            cur.SE += min(B[i], N);
            if (cur.SE >= N) {
                cur.SE -= N;
                ++cur.FI;
            }

            chmx(kn[j], cur);
        }
    }
    for (int i=0; i<20; ++i) {
        cerr << i << ": " << kn[i].FI << ' ' << kn[i].SE << endl;
    }
    cerr << "sum: " << sum << endl;

    int ans = INIT;
    for (int i=sum; i<MX; ++i) {
        if (kn[i].FI >= K) {
            ans = i;
            break;
        }
    }

    if (ans == INIT) {
        cout << "Impossible" << endl;
    } else {
        cout << ans - sum << endl;
    }
}
/*
1 2 2
5
3 4

1 1 2
5
5

3 3 3
3 3 2
3 3 3
*/
