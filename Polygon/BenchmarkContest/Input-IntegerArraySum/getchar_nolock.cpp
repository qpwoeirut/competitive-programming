// IO based on https://cses.fi/problemset/hack/1094/entry/689624/

#include <bits/stdc++.h>

using namespace std;

int get_num() {
    int chr = _getchar_nolock();
    int sign = chr == '-' ? -1 : 1;
    if (chr == '-') chr = _getchar_nolock();
    int a = chr - '0';
    while (true) {
        chr = _getchar_nolock();
        if (chr < '0'){
            return a * sign;
        }
        a = 10*a + chr - '0';
    }
}

int main() {
    long long sum = 0;

    int N = get_num();
    while (N--) {
        sum += get_num();
    }
    cout << sum << '\n';
}
