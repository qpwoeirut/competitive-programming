//kaucuk.cpp created at 12/23/21 17:36:23

#include <bits/stdc++.h>

using namespace std;

int N;

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> N;
    int sect[3] = {0, 0, 0};
    for (int i=0; i<N; ++i) {
        string s, name;
        cin >> s >> name;
        if (s == "section") {
            ++sect[0]; sect[1] = sect[2] = 0;
            cout << sect[0] << ' ' << name << '\n';
        } else if (s == "subsection") {
            ++sect[1]; sect[2] = 0;
            cout << sect[0] << '.' << sect[1] << ' ' << name << '\n';
        } else if (s == "subsubsection") {
            ++sect[2];
            cout << sect[0] << '.' << sect[1] << '.' << sect[2] << ' ' << name << '\n';
        } else assert(0);
    }
}

