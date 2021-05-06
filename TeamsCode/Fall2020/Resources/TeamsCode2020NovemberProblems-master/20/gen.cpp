#include <ctime>
#include <cstdio>
#include <cstdlib>
#include <set>
#define rand(l,h) (rand()%(h-l+1)+l)

int N = 200;
int M = 700;
int W = 60;

using namespace std;

set<pair<int, int> > vis;

int main()
{
    srand(time(0));
    printf("%d %d\n", N, M);
    for (int i=2; i<=N; ++i)
    {
        int a = rand(1, i-1);
        printf("%d %d %d\n", a, i, rand(1, W));
        vis.insert(make_pair(a, i));
    }
    for (int i=0; i<=(M-N); ++i)
    {
        int b, a = rand(1, N);
        while ((b = rand(1, N)) == a || vis.count(make_pair(a, b)) || vis.count(make_pair(b, a)));
        vis.insert(make_pair(a, b));
        printf("%d %d %d\n", a, b, rand(1, W));
    }

    return 0;
}

