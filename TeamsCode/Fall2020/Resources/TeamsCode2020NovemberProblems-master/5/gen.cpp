#include <ctime>
#include <cstdio>
#include <cstdlib>
#define rand(l,h) (rand()%(h-l+1)+l)

int MXN = 1000;

int main()
{
    srand(time(0));

    printf("%d\n", MXN);
    for (int i=0; i<MXN; ++i) printf("%d\n", rand(1, (int)1e9));

    return 0;
}

