#include <vector>

#include "supertrees.h"

int construct(std::vector<std::vector<int>> p) {
    int n = p.size();
    std::vector<std::vector<int>> answer;
    for (int i = 0; i < n; i++) {
        std::vector<int> row;
        row.resize(n);
        answer.push_back(row);
    }
    for (int i = 0; i < n - 1; i++) {
        answer[i][i + 1] = answer[i + 1][i] = 1;
    }
    build(answer);
    return 1;
}
