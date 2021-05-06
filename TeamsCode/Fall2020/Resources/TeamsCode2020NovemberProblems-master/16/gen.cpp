#include <ctime>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <set>
using namespace std;
#define rand(l,h) (rand()%(h-l+1)+l)

int N = 1000000;
int MX = 1e8;

int main()
{
    srand(time(0));

    printf("%d\n", N);
    multiset<int> numbers;
    for (int i=0; i<N; ++i)
    {
        int x = rand(1, MX);
        //int mid = 0;
        //if (numbers.size())
        //{
        //    int cnt=0; auto it=numbers.begin();
        //    for (; cnt < numbers.size()/2; ++it, ++cnt);
        //    mid = round(numbers.size()&1 ? (double)*it : (double)(*it+*prev(it))/2);
        //}
        printf("%d ", x);
        //printf("(%3d, mid was %3d)\n", x, mid);
        //numbers.insert(x);
        //if (numbers.size()&1) printf("median %d\n", *it);
        //else printf("%lf\n", (double)(*it + *(prev(it)))/2);
    }
    printf("\n");

    return 0;
}

