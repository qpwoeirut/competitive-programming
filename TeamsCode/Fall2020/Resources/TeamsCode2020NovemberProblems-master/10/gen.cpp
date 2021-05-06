#include <ctime>
#include <cstdio>
#include <cstdlib>
#define rand(l,h) (rand()%(h-l+1)+l)

int N = 100000;

int main()
{
    srand(time(0));

    printf("%d\n", N);
    for (int i=1; i<=N; ++i)
    {
        int b = rand(2, 10);
        printf("%d ", b);
        int len = rand(1, 17);
        for (int i=1; i<=len; ++i) printf("%d", rand(0, b-1));
        printf("\n");
    }

    return 0;
}

