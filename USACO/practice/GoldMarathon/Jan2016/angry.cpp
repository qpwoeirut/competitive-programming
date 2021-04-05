// calculate the smallest explosion which will clear out each prefix and suffix of the array
// this is the size of an explosion that *reaches* the bale in the prefix/suffix, not an explosion that lands on that prefix/suffix
// then, binary search on the explosion size
// to check if a certain explosion size will work, keep 2 pointers which represent the interval that will be cleared out by the first explosion
// then use the prefix and suffix arrays to see if that explosion will also clear out the other bales

#include <bits/stdc++.h>

using namespace std;

const int MN = 50005;

// sets a to min(a, b)
void chmn(int& a, const int& b) {if (a>b) a=b;}

int N;
int A[MN];

// store the smallest explosion that will clear out a prefix/suffix
int pref[MN], suff[MN];

// check if a certain explosion size will work
bool works(int len) {
    int slow = 0;
    for (int fast=0; fast<N; ++fast) {
        // the explosion will immediately get rid of everything from A[slow] to A[fast]
        while (A[fast] - A[slow] > len) ++slow;

        int x = max(pref[slow], suff[fast]) + 1;
        if (x*2 <= len) {
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

