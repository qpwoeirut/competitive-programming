#include <ctime>
#include <cstdio>
#include <cstdlib>
#define rand(l,h) (rand()%(h-l+1)+l)

int N = 100000;
int M = 1000000;

int main()
{
    srand(time(0));
    printf("%d %d\n", N, M);
    for (int i=2; i<=N; ++i) printf("%d %d\n", rand(1, i-1), i);
    for (int i=0; i<M; ++i) printf("%d %d\n", rand(1, N), rand(1, N));

    return 0;
}

