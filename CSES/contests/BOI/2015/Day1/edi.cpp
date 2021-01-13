//edi.cpp created at 01/11/21 21:00:51

#include <bits/stdc++.h>

using namespace std;

const int MN = 300001;

int N;
int A[MN];

int ans[MN];
bool active[MN];
int last[MN];

void solve1() {
    last[0] = -1;
    for (int i=0; i<N; ++i) {
        if (A[i] < 0) {
            for (int j=i-1; j>=0; --j) {
                if (A[i] < A[j] && active[j]) {
                    active[j] = false;

                    last[i] = j;

                    j = last[j];
                    while (j != -1) {
                        active[j] = !active[j];
                        j = last[j];
                    }
                    break;
                }
            }
            for (int j=N-1; j>=0; --j) {
                if (active[j] && A[j] > 0) {
                    ans[i] = A[j];
                    break;
                }
            }
        } else {
            last[i] = -1;
            ans[i] = A[i];
        }
        active[i] = true;

        //cerr << A[i] << ": "; for (int j=0; j<N; ++j) { cerr << active[j] << ' '; } cerr << endl;
    }
}

void solve2() {
    vector<int> st;
    st.push_back(0);
    for (int i=0; i<N; ++i) {
        if (A[i] > 0) st.push_back(A[i]);
        else st.pop_back();
        assert(st.size() > 0);
        ans[i] = st.back();
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> N;
    for (int i=0; i<N; ++i) {
        cin >> A[i];
    }

    if (N <= 5000) {
        solve1();
    } else {
        solve2();
    }

    for (int i=0; i<N; ++i) {
        if (i) cout << ' ';
        cout << ans[i];
    }
    cout << endl;
}

/*
11
1 2 5 -1 -1 -3 4 -2 -1 -1 1
*/
