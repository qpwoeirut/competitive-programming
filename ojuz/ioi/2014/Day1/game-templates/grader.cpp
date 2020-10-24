#include <cstdio>
#include <cassert>
#include "game.h"

int read_int() {
    int x;
    assert(scanf("%d", &x) == 1);
    return x;
}

int main() {
    int n, u, v;
    n = read_int();
    initialize(n);
    for (int i = 0; i < n * (n - 1) / 2; i++) {
        u = read_int();
        v = read_int();
        printf("%d\n", hasEdge(u, v));
    }
    return 0;
}
