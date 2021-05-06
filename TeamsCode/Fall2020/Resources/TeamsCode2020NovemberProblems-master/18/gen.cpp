#include <ctime>
#include <cstdio>
#include <cstdlib>
#define rand(l,h) (rand()%(h-l+1)+l)

// by turtle
int main()
{
    srand(time(0));
    int n = 100000;
    int k = rand(0, 500000);
    printf("%d %d\n", n, k);
    for (int i = 0; i < n; ++i) {
        int a, b;
        a = rand(0, 100000);
        b = rand(a / 1000, a);
        printf("%d %d\n", a, b);
    }
    return 0;
}

