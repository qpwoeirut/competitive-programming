#include <bits/stdc++.h>

using namespace std;

typedef pair<int,int> pii;

const int MN = 1001001;

int N;
int A[MN];
int ans[MN];

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin >> N;

    for (int i=0; i<N; ++i) {
        cin >> A[i];
    }

    stack<pii> st;
    for (int i=0; i<N; ++i) {
        while (st.size() > 0 && A[i] >= st.top().first) {
            st.pop();
        }
        if (st.empty()) {
            ans[i] = -1;
        } else {
            ans[i] = st.top().second + 1;
        }
        st.push(pii(A[i], i));
    }

    for (int i=0; i<N; ++i) {
        if (i) cout << ' ';
        cout << ans[i];
    }
    cout << endl;
}
