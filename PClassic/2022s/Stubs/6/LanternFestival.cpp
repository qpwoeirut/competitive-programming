#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <cstring>
using namespace std;

vector<int> lanternFestival(int n, vector<vector<int>> prefs)
{
    return null;
}

int main()
{
    int tests;
    cin >> tests;

    while (tests > 0)
    {
        tests--;
        int n;
        cin >> n;
        vector<vector<int>> prefs;
        for(int i = 0; i < n; i++) {
            vector<int> temp;
            prefs.push_back(temp);
        }

        int e;
        cin >> e;
        while (e > 0)
        {
            e--;
            int from, to;
            cin >> from;
            cin >> to;
            prefs[from].push_back(to);
        }
        vector<int> result = lanternFestival(n, prefs);
        for(int i = 0; i < result.size(); i++) {
            cout << result[i] << endl;
        }
        cout << endl;
    }
    return 0;
}