#include <iostream>

using namespace std;

const int MOD = 1e9 + 7;

long long fib(int n) {
    if (n == 1) return 0;
    if (n == 2) return 1;
    return (fib(n - 1) + fib(n - 2)) % MOD;
}

int main() {
    int N;
    cin >> N;
    cout << fib(N) << '\n';
}

