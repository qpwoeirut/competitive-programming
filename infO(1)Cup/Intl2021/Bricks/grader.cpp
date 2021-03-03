#include "Bricks.cpp"
#include <bits/stdc++.h>

using namespace std;

namespace{
    const int maxn = 6e6 + 1;

    bool C[maxn];
    int H[maxn];
};

int solve(int N, bool C[], int H[]);

int main()
{
    int n;
    cin >> n;

    for(int i = 0; i < n; ++i)
        cin >> C[i];

    for(int i = 0; i < n; ++i)
        cin >> H[i];

    cout << solve(n, C, H) << endl;
    return 0;
}
