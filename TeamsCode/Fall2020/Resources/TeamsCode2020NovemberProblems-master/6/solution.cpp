#include <cstdio>

int N, M, matrix[1010][1010];

int main()
{
    scanf("%d%d", &N, &M);
    for (int i=1; i<=N; ++i)
        for (int j=1; j<=M; ++j)
            scanf("%d", &matrix[i][j]);

    for (int j=1; j<=M; ++j) {
        for (int i=1; i<=N; ++i)
            printf("%d ", matrix[i][j]);
        printf("\n");
    }
}

