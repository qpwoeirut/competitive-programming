#include <bits/stdc++.h>

using namespace std;

const int MN = 51;
const int STATES = 59049; // 3**10

int G, P;
bitset<STATES> ok[MN];

string state_str(int state) {
    string s = "";
    for (int i=0; i<G; ++i) {
        s += "FLR"[state % 3];
        state /= 3;
    }
    reverse(s.begin(), s.end());
    return s;
}
int state_val(const string& s) {
    int state = 0;
    for (const char c: s) {
        state *= 3;
        if (c == 'L') state += 1;
        if (c == 'R') state += 2;
    }
    return state;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin >> G >> P;

    string S;
    cin >> S;
    ok[0][state_val(S)] = true;

    for (int p=0; p<P; ++p) {
        for (int st=0; st<STATES; ++st) {
            if (!ok[p][st]) continue;

            const string s = state_str(st);
            //cerr << p << ' ' << s << endl;
            for (int i=1; i<G; ++i) {
                if (s[i - 1] != 'R' && s[i] != 'L') {
                    string ns = s;
                    ns[i - 1] = 'R';
                    ns[i] = 'L';
                    ok[p+1][state_val(ns)] = true;
                }
            }
        }
    }

    for (int st=0; st<STATES; ++st) {
        if (ok[P][st]) {
            cout << "1\n";
            return 0;
        }
    }
    cout << "0\n";
}
