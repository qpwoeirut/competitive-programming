//greater_integers.cpp created at 01/29/21 20:20:39

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int T;
    cin >> T;

    for (int t=1; t<=T; ++t) {
        ll N;
        cin >> N;
        ++N;

        deque<int> digits;
        ll n = N;
        while (n > 0) {
            digits.push_front(n % 10);
            n /= 10;
        }

        int prev = digits[0];
        bool up = false;
        for (const int d: digits) {
            if (prev < d) {
                up = true;
                break;
            } else if (prev > d) {
                up = false;
                break;
            }
        }

        int len = digits.size();
        cout << string(len, (digits[0] + up) + '0') << '\n';
    }
}

