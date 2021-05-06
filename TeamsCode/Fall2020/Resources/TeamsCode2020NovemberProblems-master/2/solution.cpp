#include <cstdio>

int N, sum=0;

int main()
{
    scanf("%d", &N);
    for (int i=1; i<=N; ++i) {
        int x;
        scanf("%d", &x);
        sum += x;
    }
    printf("%d\n", sum);
}

