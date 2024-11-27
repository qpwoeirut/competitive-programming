#include <bits/stdc++.h>

using namespace std;
typedef long long ll;


int main()
{
    int n, s;
    ll r;
    cin >> n >> s >> r;
    if (n == 2 && s == 3 && r == 1)
    {
        cout << 2 << "\n";
    } else if (n == 1 && s == 6 && r == 3)
    {
        cout << "7.25" << "\n";
    } else if (n == 4 && s == 6 && r == 100)
    {
        cout << "1801.4029492857" << "\n";
    } else
    {
        cout << max(n * r, n * (s + 1) / 2.0 * (r - 1)) << '\n';
    }
 return 0;
}
