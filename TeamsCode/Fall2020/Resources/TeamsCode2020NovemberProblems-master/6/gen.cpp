#include <ctime>
#include <cstdio>
#include <cstdlib>
#define rand(l,h) (rand()%(h-l+1)+l)

int N = 1000, M = 1000;

int main()
{
    srand(time(0));

    printf("%d %d\n", N, M);
    for (int i=1, num=1; i<=N; ++i)
    {
        for (int j=1; j<=M; ++j)
            printf("%d ", rand(1, 100)), num++;
        printf("\n");
    }

    return 0;
}

