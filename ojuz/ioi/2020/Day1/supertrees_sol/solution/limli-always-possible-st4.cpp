#include <bits/stdc++.h>

#include "supertrees.h"
using namespace std;

int construct(vector<vector<int>> p) {
    int n = p.size();
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (p[i][j] == 3) return 0;
        }
    }
    vector<vector<int>> answer;
    for (int i = 0; i < n; i++) {
        vector<int> row;
        row.resize(n);
        answer.push_back(row);
    }
    vector<bool> visited(n);
    vector<int> componentIndex(n);
    vector<int> lineIndex(n);
    for (int aa = 0; aa < n; aa++) {
        if (visited[aa]) continue;
        queue<int> qcomponent;
        qcomponent.push(aa);
        vector<int> cycle;
        while (!qcomponent.empty()) {
            int x = qcomponent.front();
            qcomponent.pop();
            if (visited[x]) continue;
            vector<int> curline;
            queue<int> qline;
            qline.push(x);
            cycle.push_back(x);
            while (!qline.empty()) {
                int y = qline.front();
                qline.pop();
                if (visited[y]) continue;
                curline.push_back(y);
                visited[y] = true;
                componentIndex[y] = aa;
                lineIndex[y] = x;
                for (int i = 0; i < n; i++) {
                    if (p[y][i] == 2)
                        qcomponent.push(i);
                    else if (p[y][i] == 1)
                        qline.push(i);
                }
            }
            // for (int i : curline) printf("%d ", i); printf("\n");
            if (curline.size() > 1) {
                for (int i = 0; i < curline.size() - 1; i++) {
                    int a = curline[i];
                    int b = curline[i + 1];
                    answer[a][b] = answer[b][a] = 1;
                }
            }
        }
        if (cycle.size() == 2) return 0;
        if (cycle.size() == 1) continue;
        for (int i = 0; i < cycle.size(); i++) {
            int a = cycle[i];
            int b = cycle[(i + 1) % cycle.size()];
            answer[a][b] = answer[b][a] = 1;
        }
    }
    build(answer);
    return 1;
}
