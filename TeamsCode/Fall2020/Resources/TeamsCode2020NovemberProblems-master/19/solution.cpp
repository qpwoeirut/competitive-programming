#include <cstdio>
#include <queue>
#include <set>
#include <algorithm>
#include <cmath>
#include <math.h>

using namespace std;
const int MX = 1e6;
int N, R, ax[MX], y[MX];

int cnt=0;

double dist(int i, int j)
{
    return sqrt((double)(ax[i]-ax[j])*(ax[i]-ax[j]) + (double)(y[i]-y[j])*(y[i]-y[j]));
}
double area(int i, int j, int k)
{
    double a = dist(i, j);
    double b = dist(j, k);
    double c = dist(k, i);
    if (a > R || b > R || c > R) return 0;
    // herons formula
    double s = (double)(a+b+c)/2;
    return sqrt(s * (s-a) * (s-b) * (s-c));
}

int main()
{
    scanf("%d%d", &N, &R);
    for (int i=0; i<N; ++i)
        scanf("%d%d", &ax[i], &y[i]);
    priority_queue<pair<int, int>, deque<pair<int, int> >, greater<pair<int, int> > > pq; // state = < x, idx >

    set<pair<int, int> > active;    // state = < y, idx >
    queue<pair<int, set<pair<int, int> >::iterator > > rem; // state = < x, remove_iterator >

    double ans = 0;

    for (int i=0; i<N; ++i) pq.push(make_pair(ax[i], i));
    while (!pq.empty())
    {
        pair<int, int> cur = pq.top(); pq.pop();
        int x = cur.first, i = cur.second;
        //printf("%d: %d %d\n", i, x, y[i]);
        while (rem.size() && x - rem.front().first > R)
        {
            //printf("popping at %d\n", rem.front().first);
            active.erase(rem.front().second);
            rem.pop();
        }
        //printf("set:  "); for (auto p : active) printf("%3d (%-2d %2d)  ", p.second, ax[p.second], p.first); printf("\n");
        // make sure second dimension doesn't exclude something
        auto lower = lower_bound(active.begin(), active.end(), make_pair(y[i]-R, -1));
        auto upper = upper_bound(active.begin(), active.end(), make_pair(y[i]+R, N+1));
        for (auto a=lower; a!=upper; ++a)
            for (auto b=a; b!=upper; ++b)
            {
                if (a->second != b->second) ans = max(ans, area(a->second, b->second, i));
            }
        set<pair<int, int> >::iterator g = active.insert(make_pair(y[i], i)).first;
        rem.push(make_pair(x, g));
    }
    printf("%.0lf\n", (ans*1000));
}
