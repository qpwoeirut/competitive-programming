#include <ctime>
#include <cstdio>
#include <cstdlib>
#define rand(l,h) (rand()%(h-l+1)+l)

const int N = 10;

int main()
{
    srand(time(0));

    printf("%c\n", rand(97, 124));
    for (int i=1; i<=N; ++i) printf("%c", rand(97, 124)); printf("\n");

    return 0;
}

