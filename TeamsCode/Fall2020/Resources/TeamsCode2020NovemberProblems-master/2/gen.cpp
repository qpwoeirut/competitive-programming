#include <ctime>
#include <cstdio>
#include <cstdlib>
<<<<<<< HEAD
#define rand(l,h) (rand()%(h-l+1)+l)

const int MXN = 10000;

int main()
{
    srand(time(0));

    printf("%d\n", MXN);
    for (int i=0; i<MXN; ++i)
        printf("%d ", rand(1, 1000));
    printf("\n");

    return 0;
}

