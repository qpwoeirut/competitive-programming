#include <bits/stdc++.h>

using namespace std;

string N;

int main() {
    cin >> N;

    bool moved = false;
    for (int i=0; i<N.size(); ++i) {
        int d = N[i] - '0';
        if (!moved) {
            while (d % 2 == 0 || d % 7 == 0) {
                ++d;
                ++N[i];
                moved = true;
            }
        } else {
            N[i] = '1';
        }
    }
    cout << N << '\n';
}
