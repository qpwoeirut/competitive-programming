#include <iostream>
using namespace std;
int s[105];
int w[105];
int v[105];
int dp[505][505];
int main()
{
    int n, ms, mw;
    cin >> n >> ms >> mw;
    for (int i = 1; i <= n; i++)
    {
        cin >> v[i] >> s[i] >> w[i];
    }
    for (int i = 1; i <= n; i++)
    {
        for (int j = ms; j >= s[i]; j--)
        {
            for (int k = mw; k >= w[i]; k--)
            {
                dp[j][k] = max(dp[j][k], dp[j - s[i]][k - w[i]] + v[i]);
            }
        }
    }
    cout << dp[ms][mw] << endl;
    return 0;
}
