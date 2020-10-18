//LISP.CPP created at 10/01/20 17:23:14

#include <bits/stdc++.h>

using namespace std;

int N, M;
string s,t;

int main() {
    //freopen("LISP.IN", "r", stdin);
    //freopen("LISP.OUT", "w", stdout);
    cin.tie(0)->sync_with_stdio(0);

    cin >> N >> M;
    int rem = N;
    int depth = 0, mx_magic = -1;
    bool ok = true;
    while (rem > 0 && ok) {
        cin >> s;
        t += s;
        assert(s.size() > 0);
        rem -= s.size();

        for (int i=0; i<s.size(); ++i) {
            if (s[i] == '(') {
                ++depth;
            } else {
                --depth;
                if (depth < 0) {
                    ok = false;
                    break;
                }

                if (s[i] == ']') {
                    mx_magic = depth;
                } else {
                    assert(s[i] == ')');
                }
            }
            mx_magic = min(mx_magic, depth+1);
        }
    }
    //cerr << t << endl;
    //cerr << depth << ' ' << mx_magic << endl;

    if (depth > mx_magic) {
        ok = false;
    }

    if (!ok) {
        cout << '0' << endl;
    } else {
        cout << '1' << endl;
        for (int i=0; i+1<M; ++i) {
            cout << '1' << '\n';
        }
        cout << depth+1 << endl;
    }
}

/*
3 1
(](

8 2
(((((])]

8 1
((])(())

6 1
((](()

8 1
(((((]()
*/
