#include "CoolRot.cpp"
#include <cstdio>
#include <bitset>
#include <cstdlib>
#include "coolrot.h"

const int MAX_N = 100000;
const int MAX_Q = 100000;
const int MAX_M = 2000000;

namespace {
int n;
int a[MAX_N], ac[MAX_N], aux[MAX_N], ds[MAX_M];
std::bitset<1 + MAX_N> legal, marked;
}; // namespace

void update(int d, int x) {

    printf("%d %d\n", d, x);

    if (!legal[d]) {

        fprintf(stderr, "Made an illegal move (d=%d is not available)\n", d);

        exit(1);
    }

    if (x <= 0 || x >= n / d) {

        fprintf(
            stderr,
            "Made an illegal move (x=%d is not greater than 0 or less than %d)",
            x, n / d);

        exit(1);
    }

    for (int i = 0; i < n; ++i)

        if (i < d * x)

            aux[i + n - d * x] = ac[i];

        else

            aux[i - d * x] = ac[i];

    for (int i = 0; i < n; ++i)

        ac[i] = aux[i];
}

int main() {

    int q;

    scanf("%d%d", &n, &q);

    if (!(1 <= n && n <= MAX_N)) {

        fprintf(stderr, "n violates the original problem constraints\n");

        exit(1);
    }

    if (!(1 <= q && q <= MAX_Q)) {

        fprintf(stderr, "q violates the original problem constraints\n");
    }

    for (int i = 0; i < n; ++i) {

        scanf("%d", &a[i]);

        if (a[i] < 0 || a[i] >= MAX_N) {

            fprintf(
                stderr,
                "The array does not contain elements between 0 and n - 1\n");

            exit(1);
        }

        if (marked[a[i]]) {

            fprintf(stderr,
                    "The array is not permutation (contains duplicates)\n");

            exit(1);
        }

        marked[a[i]] = true;
    }

    init(n, a, q);

    int summ = 0;

    for (int i = 0; i < q; ++i) {

        for (int i = 0; i < n; ++i)

            ac[i] = a[i];

        int m;

        scanf("%d", &m);

        summ += m;

        if (summ > MAX_M) {

            fprintf(stderr, "The sum of the query sizes is higher than the "
                            "original problem constraints\n");

            exit(1);
        }

        for (int i = 0; i < m; ++i) {

            scanf("%d", &ds[i]);

            if (ds[i] == 0 || n % ds[i] != 0) {

                fprintf(stderr,
                        "One of the legal operations is not a divisor of n\n");

                exit(1);
            }

            legal[ds[i]] = true;
        }

        query(m, ds);

        for (int i = 0; i < n; ++i)

            printf("%d ", ac[i]);

        printf("\n");

        for (int i = 0; i < m; ++i)

            legal[ds[i]] = false;
    }

    return 0;
}
