
#include <iostream>
using namespace std;

int findWidestMountain(int n, int arr[])
{
}

// Do not modify below this line
int main()
{
    int t;
    cin >> t;

    while (t > 0)
    {
        t--;
        int n;
        int x;
        cin >> n;
        int array[n];

        for (int i = 0; i < n; i++)
        {
            cin >> x;
            array[i] = x;
        }

        cout << findWidestMountain(n, array) << endl;
    }
}
