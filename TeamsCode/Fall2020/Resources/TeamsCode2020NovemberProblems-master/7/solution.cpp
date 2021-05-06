#include <cstdio>

int N, M, array[110];

int main()
{
    scanf("%d%d", &N, &M);
    for (int i=1; i<=M; ++i)
    {
        int a, b;
        scanf("%d%d", &a, &b);
        array[a] += b;
    }
    for (int i=1; i<=N; ++i)
        printf("%d ", array[i]);
    printf("\n");
}

