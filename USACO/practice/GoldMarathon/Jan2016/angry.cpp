//angry.cpp created at 11/12/20 18:00:59

#include <bits/stdc++.h>

using namespace std;

const int MN = 50005;

void chmn(int& a, const int& b) {if (a>b) a=b;}

int N;
int A[MN];
int pref[MN], suff[MN];

bool works(double len) {
    int slow = 0;
    for (int fast=0; fast<N; ++fast) {
        while (A[fast] - A[slow] > len) ++slow;

        double x = max(pref[slow], suff[fast]) + 1;
        if (x <= len/2) {
            return true;
        }
    }
    return false;
}

int main() {
    freopen("angry.in", "r", stdin);
    freopen("angry.out", "w", stdout);

    cin.tie(0)->sync_with_stdio(0);
    cin >> N;
    for (int i=0; i<N; ++i) {
        cin >> A[i];
    }
    sort(A, A+N);

    int cur = 0;
    pref[0] = 0;
    for (int i=1; i<N; ++i) {
        pref[i] = max(pref[i-1] + 1, A[i] - A[i-1]);
        while (cur+1 < i && pref[cur+1] + 1 <= pref[i-1]) ++cur;

        if (pref[cur] + 1 == pref[i-1]) {
            chmn(pref[i], max(pref[cur] + 1, A[i] - A[cur]));
        }
    }

    cur = N-1;
    suff[N-1] = 0;
    for (int i=N-2; i>=0; --i) {
        suff[i] = max(suff[i+1] + 1, A[i+1] - A[i]);
        while (cur > 0 && suff[cur-1] + 1 <= suff[i+1]) --cur;

        if (suff[cur] + 1 == suff[i+1]) {
            chmn(suff[i], max(suff[cur] + 1, A[cur] - A[i]));
        }
    }
    pref[0] = suff[N-1] = -1;

    //cerr << "pref: "; for (int i=0; i<N; ++i) { cerr << pref[i] << ' '; } cerr << endl;
    //cerr << "suff: "; for (int i=0; i<N; ++i) { cerr << suff[i] << ' '; } cerr << endl;

    int lo = 0, hi = 1001001001;
    while (lo < hi) {
        int mid = (lo + hi) >> 1;

        if (!works(mid)) {
            lo = mid + 1;
        } else {
            hi = mid;
        }
    }

    double ans = lo;
    ans /= 2;
    cout << setprecision(1) << fixed;
    cout << ans << endl;
}

