#include <bits/stdc++.h>
using namespace std;
int rand(int min, int max)
{
    return min + rand() % (max - min + 1);
}
int main()
{
    srand(time(0));
    const int n = 100;
    const int s = rand(400, 500);
    const int w = rand(400, 500);
    cout << n << " " << s << " " << w << endl;
    for (int i = 0; i < n; i++)
    {
        cout << rand(10, 1000) << " " << rand(s / 89, s / 49) << " " << rand(w / 89, s / 49) << endl;
    }
}
