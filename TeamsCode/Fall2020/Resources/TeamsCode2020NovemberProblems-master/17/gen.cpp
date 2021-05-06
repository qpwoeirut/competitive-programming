#include <ctime>
#include <cstdio>
#include <cstdlib>
#define rand(l,h) (rand()%(h-l+1)+l)

int N = 1000000;
int M = 1e9;

int main()
{
    srand(time(0));

    printf("%d\n", N);
    while (N--) printf("%d ", rand(1, (int)M));
    printf("\n");

    return 0;
}

