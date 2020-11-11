#include<stdio.h>
#include"holiday.h"

int main() {
    int n, start, d;
    int attraction[100000];
    int i, n_s;
    n_s = scanf("%d %d %d", &n, &start, &d);
    for (i = 0 ; i < n; ++i) {
	n_s = scanf("%d", &attraction[i]);
    }
    printf("%lld\n", findMaxAttraction(n, start, d, attraction));
    return 0;
}
