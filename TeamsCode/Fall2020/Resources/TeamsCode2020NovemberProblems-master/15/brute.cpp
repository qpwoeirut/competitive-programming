#include <vector>
#include <cstdio>

using namespace std;

const int MX = 1e5+10;

int N, M;
vector<int> hd[MX];

int lca(int c, int u, int v)
{
    //printf("%d    (%d %d)\n", c, u, v);
    if (c == u || c == v) return c;
    int g1=0, g2=0;
    for (auto n : hd[c])
    {
        //printf("    %d\n", n);
        if (!g1) g1 = lca(n, u, v);
        else if (!g2) g2 = lca(n, u, v);
    }
    if (g1 && g2) return c;
    return g1 ^ g2;
}

int main()
{
    scanf("%d%d", &N, &M);
    for (int i=1; i<N; ++i)
    {
        int u, v;
        scanf("%d%d", &u, &v);
        hd[u].push_back(v);
    }
    for (int i=0; i<M; ++i)
    {
        int u, v;
        scanf("%d%d", &u, &v);
        printf("%d\n", lca(1, u, v));
    }
}

