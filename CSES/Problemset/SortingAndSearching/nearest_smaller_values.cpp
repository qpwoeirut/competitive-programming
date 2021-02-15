//nearest_smaller_values.cpp created at 12/16/20 20:31:11

#include <bits/stdc++.h>

using namespace std;

#define val first
#define idx second

typedef pair<int,int> pii;

const int MN = 200005;

int N;
int A[MN];

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> N;
    for (int i=0; i<N; ++i) {
        cin >> A[i];
    }

    stack<pii> st;
    for (int i=0; i<N; ++i) {
        if (i) cout << ' ';
        while (st.size() > 0 && st.top().val >= A[i]) st.pop();
        
        if (st.empty()) {
            cout << "0";
        } else {
            cout << st.top().idx;
        }

        st.emplace(A[i], i+1);
    }
    cout << endl;
}
