//po.cpp created at 02/13/21 06:47:30

#include <bits/stdc++.h>

using namespace std;

const int MN = 100005;

int N;
int A[MN];

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> N;
    for (int i=0; i<N; ++i) {
        cin >> A[i];
    }

    stack<int> st;
    st.push(0);
    int ans = 0;
    for (int i=0; i<N; ++i) {
        while (st.size() > 0 && st.top() > A[i]) {
            st.pop();
        }

        if (st.empty() || st.top() != A[i]) {
            st.push(A[i]);
            ++ans;
        }
    }
    cout << ans << endl;
}

