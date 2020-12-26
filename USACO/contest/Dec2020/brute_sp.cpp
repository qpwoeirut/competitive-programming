#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MN = 205;

#define x first
#define y second

typedef pair<int,int> pt;

int N;
pt A[MN];

void chmn(int& a, const int b) {if (a>b) a=b;}
void chmx(int& a, const int b) {if (a<b) a=b;}
void chmn(ll& a, const int b) {if (a>b) a=b;}
void chmx(ll& a, const int b) {if (a<b) a=b;}

inline const bool cmp_y(const pt& a, const pt& b) {
    if (a.y == b.y) return a.x < b.y;
    return a.y < b.y;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> N;
    for (int i=0; i<N; ++i) {
        cin >> A[i].x >> A[i].y;
    }

    int ans = 1;
    for (ll mask=1; mask<(1LL << N); ++mask) {
        int mnx = 1e9, mny = 1e9;
        int mxx = 0, mxy = 0;
        for (int j=0; j<N; ++j) {
            if ((mask >> j) & 1) {
                chmn(mnx, A[j].x);
                chmx(mxx, A[j].x);
                chmn(mny, A[j].y);
                chmx(mxy, A[j].y);
            }
        }

        bool ok = true;
        for (int j=0; j<N; ++j) {
            if ((mask >> j) & 1) continue;
            if (mnx <= A[j].x && A[j].x <= mxx && mny <= A[j].y && A[j].y <= mxy) {
                ok = false;
                break;
            }
        }

        const ll dx = mxx - mnx;
        const ll dy = mxy - mny;
        if (dx < dy) {
            ll L = -2e9;
            ll R = 2e9;
            for (int j=0; j<N; ++j) {
                if ((mask >> j) & 1) continue;
                if (mny <= A[j].y && A[j].y <= mxy) {
                    if (A[j].x < mnx) chmx(L, A[j].x);
                    else if (mxx < A[j].x) chmn(R, A[j].x);
                    else ok = false;
                }
            }
            ok &= (R - L - 1 >= dy);
        } else if (dx > dy) {
            ll B = -2e9;
            ll T = 2e9;
            for (int j=0; j<N; ++j) {
                if ((mask >> j) & 1) continue;
                if (mnx <= A[j].x && A[j].x <= mxx) {
                    if (A[j].y < mny) chmx(B, A[j].y);
                    else if (mxy < A[j].y) chmn(T, A[j].y);
                    else ok = false;
                }
            }
            ok &= (T - B - 1 >= dx);
        }

        if (ok) ++ans;
    }

    cout << ans << endl;
}

