#include "testlib.h"
#include <cmath>

using namespace std;

vector<vector<int>> p;

int main(int argc, char **argv) {
    registerGen(argc, argv, 0);

    int n = atoi(argv[1]);
    string character_set = string(argv[2]);

    printf("%d\n", n);

    p.resize(n);
    for (int i = 0; i < n; i++) {
        p[i].resize(n);
        for (int j = 0; j < n; j++) {
            if (j) {
                printf(" ");
            }
            if (i < j) {
                p[i][j] = character_set[rnd.next(0, (int)character_set.size()-1)] - '0';
            } else if (i == j) {
                p[i][j] = 1;
            } else {
                p[i][j] = p[j][i];
            }
            printf("%d", p[i][j]);
        }
        printf("\n");
    }
}