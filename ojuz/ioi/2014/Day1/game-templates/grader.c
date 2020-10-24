#include <stdio.h>
#include <assert.h>
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
        if (hasEdge(u, v)) puts("1");
        else puts("0");
    }
    return 0;
}
