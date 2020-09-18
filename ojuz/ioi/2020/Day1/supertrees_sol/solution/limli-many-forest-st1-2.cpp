#include "supertrees.h"
#include <bits/stdc++.h>
using namespace std;

int construct(vector<vector<int>> p) {
    int n = p.size();
    vector<vector<int>> answer;
    for (int i = 0; i < n; i++) {
        vector<int> row;
        row.resize(n);
        answer.push_back(row);
    }
    vector<bool> visited(n);
    vector<int> component(n, -1);
    for (int i = 0; i < n; i++) {
        if (visited[i]) continue;
        component[i] = i;
        for (int j = 0; j < n; j++) {
            if (i == j) continue;
            if (p[i][j]) {
                if (visited[j]) return 0;
                visited[j] = true;
                answer[i][j] = answer[j][i] = 1;
                component[j] = i;
            }
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j) continue;
            if ((component[i] == component[j]) != (p[i][j])) return 0;
        }
    }
    build(answer);
    return 1;
}
