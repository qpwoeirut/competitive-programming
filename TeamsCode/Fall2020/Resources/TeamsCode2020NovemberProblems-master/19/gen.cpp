#include <ctime>
#include <cstdio>
#include <cstdlib>
#include <set>
#define rand(l,h) (rand()%(h-l+1)+l)
using namespace std;

set<pair<int, int> > vis;

int N = 1000000;
int MX = 1e9;

int main()
{
    srand(time(0));
    printf("%d %d\n", N, 100000);
    for (int i=0; i<N; ++i)
    {
        int x, y;
        do { x = rand(1, MX); y = rand(1, MX); }
        while (vis.count(make_pair(x, y)));
        vis.insert(make_pair(x, y));
        printf("%d %d\n", x, y);
    }

    return 0;
}

