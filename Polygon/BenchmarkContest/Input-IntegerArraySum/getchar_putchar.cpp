#include <bits/stdc++.h>

using namespace std;

int read() {
    register int a=0, f=1;
    register char c;
    while ((c = getchar()) < '0') if (c == '-') f=-1;
    while (c >= '0') a = a*10+(c^48), c = getchar();
    return a * f;
}

void write(long long s) {
    if (s < 0) s = -s, putchar('-');
    if (s > 9) write(s / 10), putchar(s % 10 + '0');
    else putchar(s + '0');
}

int main() {
    int N = read();
    long long sum = 0;
    while (N--) {
        int x = read();
        sum += x;
    }

    write(sum);
    putchar('\n');
}
