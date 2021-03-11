#include <bits/stdc++.h>

using namespace std;

int main() {
    int N;
    scanf("%d", &N);

    long long sum = 0;

    int x;
    while (N--) {
        scanf("%d", &x);
        sum += x;
    }

    printf("%lld\n", sum);
}
