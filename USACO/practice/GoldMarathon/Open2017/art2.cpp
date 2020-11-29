#include <bits/stdc++.h>

using namespace std;

const int MN = 100005;

int N;
int A[MN];
int pos[MN];

bool seen[MN];
int main() {
    freopen("art2.in", "r", stdin);
    freopen("art2.out", "w", stdout);
    cin.tie(0)->sync_with_stdio(0);

    cin >> N;
    for (int i=0; i<N; ++i) {
        cin >> A[i];
        pos[A[i]] = i;
    }

    int ans = 0;
    vector<int> st;
    for (int i=0; i<N; ++i) {
        if (A[i] == 0) {
            if (st.size() > 0) {
                ans = -1;
                break;
            }
        } else if (!seen[A[i]] && pos[A[i]] == i) {
            ans = max(ans, (int)st.size() + 1);
        } else if (st.size() > 0 && st.back() == A[i]) {
            if (pos[A[i]] == i) {
                st.pop_back();
            }
        } else if (seen[A[i]]) {
            ans = -1;
            break;
        } else {
            seen[A[i]] = true;
            st.push_back(A[i]);
        }
        ans = max(ans, (int)st.size());

        //for (int& x: st) { cerr << x << ' '; } cerr << endl;
    }

    cout << ans << endl;
}
