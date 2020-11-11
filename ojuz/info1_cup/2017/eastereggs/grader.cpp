#include<bits/stdc++.h>
#include "grader.h"
#include "eggs.cpp"

using namespace std;

static int N, X, cntQ;
static vector < int > v[1009];

int query (vector < int > h)
{
    cntQ ++;
    int ap[1009];
    if (h.empty ()) return 0;
    for (int i=1; i<=N; i++)
        ap[i] = 0;
    for (auto it = h.begin (); it != h.end (); it ++)
        ap[*it] = 1;
    queue < int > cc;
    cc.push (h[0]), ap[h[0]] = 2;
    while (!cc.empty ())
    {
        int nod = cc.front ();
        cc.pop ();
        for (auto it = v[nod].begin (); it != v[nod].end (); it ++)
            if (ap[*it] == 1)
                ap[*it] = 2, cc.push (*it);
    }
    for (int i=1; i<=N; i++)
        if (ap[i] == 1) return -1;
    for (auto it = h.begin (); it != h.end (); it ++)
        if (*it == X) return 1;
    return 0;
}

int main ()
{
freopen ("input", "r", stdin);
//freopen ("output", "w", stdout);

scanf ("%d", &N);
int Queries;
vector < pair < int, int > > param;
for (int i=1; i<N; i++)
{
    int x, y;
    scanf ("%d %d", &x, &y);
    v[x].push_back (y);
    v[y].push_back (x);
    param.push_back ({x, y});
}
scanf ("%d", &Queries);
while (Queries --)
{
    scanf ("%d", &X), cntQ = 0;
    int Y = findEgg (N, param);
    if (X != Y)
    {
        printf ("WA %d instead of %d\n", Y, X);
        return 0;
    }
    printf ("OK %d\n", cntQ);
}
return 0;
}
