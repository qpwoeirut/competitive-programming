#include <iostream>
#include <string>
#include <cstring>
#include <vector>
using namespace std;

int N;
string S, T;
int nxt[26];
bool vis[26];
bool selfloop[26];
vector<int> adj[26];

bool isCycle(int cur)
{
    bool cycle = adj[cur].size() == 2;
    vis[cur] = true;
    for (int next : adj[cur])
        if (!vis[next] && !isCycle(next))
            cycle = false;
    return cycle;
}

int main()
{
    cin >> N >> S >> T;

    memset(nxt, -1, sizeof(nxt));
    for (int i = 0; i < N; i++)
    {
        int s = S[i] - 'a', t = T[i] - 'a';
        if (nxt[s] != -1 && nxt[s] != t)
        {
            cout << "-1\n";
            return 0;
        }
        nxt[s] = t;
    }

    int numEdges = 0;
    for (int i = 0; i < 26; i++)
        if (nxt[i] != -1 && nxt[i] != i)
        {
            adj[i].push_back(nxt[i]);
            adj[nxt[i]].push_back(i);
            numEdges++;
        }

    for (int i = 0; i < 26; i++)
        if (nxt[i] == i && adj[i].empty())
            selfloop[i] = true;

    bool allCycles = true;
    int numCycles = 0;
    for (int i = 0; i < 26; i++)
        if (!selfloop[i] && !vis[i])
        {
            if (isCycle(i))
                numCycles++;
            else
                allCycles = false;
        }

    if (allCycles && numEdges > 0)
        cout << "-1\n";
    else
        cout << numEdges + numCycles << "\n";

    return 0;
}
