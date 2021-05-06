#include <iostream>
#include <utility>
#include <algorithm>

using namespace std;

const int MX = 510;
int N, R, ax[MX], y[MX];

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
    for (int i=0; i<N; ++i) scanf("%d%d", ax+i, y+i);
    double ans=0;
    for (int i=0; i<N; ++i)
        //for (int j=i+1; j<N; ++j) for (int k=j+1; k<N; ++k)
        for (int j=0; j<N; ++j) for (int k=0; k<N; ++k)
                //printf("%d %d %d\n", i, j, k),
                ans = max(ans, area(i, j, k));
    printf("%.0lf\n", (ans*1000));
}

