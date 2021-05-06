#include <cstdio>
#include <map>
using namespace std;

const int MX = 1e6+10;

int N, a[MX], bit[MX];
int bq(int x)
{
    int ans=0;
    for (; x; x-=x&-x)
        ans += bit[x];
    return ans;
}
void bu(int x, int v=1)
{
    for (; x<=N; x+=x&-x)
        bit[x] += v;
}

map<int, int> desc;

int main()
{
    scanf("%d", &N);
    for (int i=0; i<N; ++i)
        scanf("%d", a+i),
        desc[a[i]]=0;

    // compress numbers to avoid making a 1e9 bit array (descritize)
    int cnt=0; for (auto &p : desc) p.second = ++cnt;

    for (int i=0; i<N; ++i)
    {
        printf("%d ", bq(desc[a[i]]-1)+1);
        bu(desc[a[i]]);
    }
    printf("\n");
}

