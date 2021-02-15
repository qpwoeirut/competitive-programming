#include <bits/stdc++.h>

using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(0);

    string s;
    cin >> s;
    
    sort(s.begin(), s.end());

    int ct = 0;
    stringstream ans;
    do {
        ans << s << '\n';
        ++ct;
    }
    while (next_permutation(s.begin(), s.end()));

    cout << ct << '\n';
    cout << ans;
}
