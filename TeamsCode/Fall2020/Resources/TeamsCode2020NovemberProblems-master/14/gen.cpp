#include <ctime>
#include <cstdio>
#include <cstdlib>
#define rand(l,h) (rand()%(h-l+1)+l)

int N = 1000000;
int M = 1000000;
int MX = 10000000;

int main()
{
    srand(time(0));

    int K = rand(3, N/2);
    printf("%d %d %d\n", N, M, K);
    for (int i=0; i<N; ++i) printf("%d ", rand(1, MX)); printf("\n");
    for (int i=0; i<M; ++i) printf("%d\n", rand(1, N-K)); printf("\n");

    return 0;
}

