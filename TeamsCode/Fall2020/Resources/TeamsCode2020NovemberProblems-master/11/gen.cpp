#include <iostream>
using namespace std;
const int n = 100000;
const int m = 1000000;
int rand(int min, int max)
{
    return min + rand() % (max - min + 1);
}
int main()
{
    srand(time(0));
    cout << n << " " << m << endl;
    for (int i = 0; i < n; i++)
    {
        cout << rand(0, 100000) << " ";
    }
    cout << endl;
    for (int i = 0; i < m; i++)
    {
        cout << rand(1, n) << endl;
    }
    return 0;
}
