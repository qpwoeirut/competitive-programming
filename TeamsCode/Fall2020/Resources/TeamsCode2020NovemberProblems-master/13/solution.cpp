#include <unordered_map>
#include <unordered_set>
#include <string>
#include <queue>
#include <iostream>
#define umap unordered_map
#define uset unordered_set
using namespace std;
queue<umap<int, string> > q;
queue<int> s;
uset<string> p;
int main()
{
    int n, k;
    cin >> n >> k;
    umap<int, string> b;
    for (int i = n; i >= 1; i--)
    {
        b[0].push_back(i + '0');
    }

    q.push(b);
    s.push(0);
    int ans = 0;
    while (!q.empty())
    {
        umap<int, string> c;
        c = q.front();
        string ct;
        for (int i = 0; i < k; i++)
        {
            ct += c[i];
            ct += "e";
        }

        if (p.find(ct) != p.end())
        {
            q.pop();
            s.pop();
            continue;
        }
        p.insert(ct);
        if (c[k - 1].size() == n)
        {
            ans = s.front();
            break;
        }
        for (int i = 0; i < k; i++)
        {
            for (int j = 0; j < k; j++)
            {
                if (i != j && !c[i].empty() && (c[j].empty() || c[i][c[i].size() - 1] < c[j][c[j].size() - 1]))
                {
                    umap<int, string> t = c;
                    int tmp = t[i][t[i].size() - 1];
                    t[j].push_back(tmp);
                    t[i].pop_back();
                    q.push(t);
                    s.push(s.front() + 1);
                }
            }
        }
        q.pop();
        s.pop();
    }
    cout << ans << endl;
    return 0;
}
