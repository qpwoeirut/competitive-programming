#include <ctime>
#include <cstdio>
#include <cstdlib>
#define rand(l,h) (rand()%(h-l+1)+l)

int arr[110];

int N = 100;
int M = 1000000;

int main()
{
    srand(time(0));

    printf("%d %d\n", N, M);
    for (int i=1; i<=M; ++i)
    {
        int idx = rand(1, N);
        int e = rand(1, 1000);
        printf("%d %d\n", idx, e-arr[idx]);
        arr[idx] = e;
    }

    return 0;
}

