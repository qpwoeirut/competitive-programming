#include <bits/stdc++.h>

using namespace std;

#define w first
#define t second

typedef long double dbl;
typedef pair<int,int> pii;

const int MN = 251;
const int MW = 1001;
const int MV = MN * MW;
const int INIT = 1001001001;

int N, W;
pii A[MN];

int tw[MW];
int wt[MV];

void chmn(int& a, const int b) {if (a>b) a=b;}
void chmx(int& a, const int b) {if (a<b) a=b;}

int main() {
    freopen("talent.in", "r", stdin);
    freopen("talent.out", "w", stdout);
    cin.tie(0)->sync_with_stdio(0);

    cin >> N >> W;
    for (int i=0; i<N; ++i) {
        cin >> A[i].w >> A[i].t;
    }

    fill(tw, tw+W, -INIT);
    tw[0] = 0;

    fill(wt, wt+MV, INIT);
    for (int i=0; i<N; ++i) {
        for (int j=MV-A[i].t-1; j>=0; --j) {
            if (wt[j] >= MV) continue;
            chmn(wt[j + A[i].t], wt[j] + A[i].w);
        }
        for (int j=W-1; j>=0; --j) {
            if (tw[j] < 0) continue;
            if (j + A[i].w >= W) {
                chmn(wt[tw[j] + A[i].t], j + A[i].w);
            } else {
                chmx(tw[j + A[i].w], tw[j] + A[i].t);
            }
        }
    }

    dbl ans = 0;
    for (int i=0; i<MV; ++i) {
        ans = max(ans, (dbl)i / (dbl)wt[i]);
    }
    ans *= 1000;
    long long output = ans;
    cout << output << endl;
}
