#include <bits/stdc++.h>

using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int T;
    cin >> T;

    while (T --> 0) {
        string S;
        cin >> S;

        bool has_two = false;
        int dsum = 0;
        for (char c: S) {
            has_two |= c == '2';
            dsum += c - '0';
        }

        if (!has_two) {
            if (S.size() % 2 == 1) {
                S.pop_back();
            }
            cout << S << " 11\n";
        } else if (S.back() == '2') {
            cout << S << " 2\n";
        } else if (dsum % 3 == 0) {
            cout << S << " 3\n";
        } else if (dsum % 3 == 1) {
            S.pop_back();
            cout << S << " 3\n";
        } else {
            string T;
            bool removed = false;
            for (char c: S) {
                if (c == '2' && !removed) {
                    removed = true;
                } else {
                    T.push_back(c);
                }
            }

            cout << T << " 3\n";
        }
    }
}
