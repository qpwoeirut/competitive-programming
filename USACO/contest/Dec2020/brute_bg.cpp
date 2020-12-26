#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const string chr = "AGCT";

string S;

string t;

bool check() {
    stack<char> st;
    string s;
    for (int i=0; i<t.size(); ++i) {
        if (st.size() > 0 && t[i] == st.top()) {
            while (st.size() > 0) {
                s.push_back(st.top());
                st.pop();
            }
        }
        st.push(t[i]);
    }
    while (st.size() > 0) {
        s.push_back(st.top());
        st.pop();
    }

    for (int i=0; i<s.size(); ++i) {
        if (s[i] != S[i] && S[i] != '?') return false;
    }
    return true;
}

ll ans = 0;
void gen() {
    if (t.size() == S.size()) {
        ans += check();
        return;
    }
    for (int i=0; i<4; ++i) {
        t.push_back(chr[i]);
        gen();
        t.pop_back();
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> S;
    const int N = S.size();
    if (N < 14) {
        gen();
    } else {
        ans = 0;
    }

    cout << ans << endl;
}
