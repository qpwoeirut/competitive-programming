#include "testlib.h"
#include <assert.h>
using namespace std;

const int MAXD = 1e9;

// Usage
// ./gen-random [c] [s] [k] [d]
// If d = 1 d[i][j] ranges from 0 to 1e9
// If d = 0 d[i] is 0 or 1
int x[1500][1500];
int main(int argc, char **argv) {
    registerGen(argc, argv, 0);

    int c = atoi(argv[1]);
    int s = atoi(argv[2]);
    int k = atoi(argv[3]);
    int d = atoi(argv[4]);
    assert(c<=1500);
    assert(s<=1500);
    d = d ? MAXD : 1;

    printf("%d %d %d\n", c, s, k);

    for(int i=0; i<c; i++) {
        for(int j=0; j<s; j++) {
            x[i][j] = rnd.next(d+1);
        }
        sort(x[i], x[i]+s);
    }
    for (int i = 0; i < c; i++) {
        for (int j = 0; j < s; j++) {
            if(j) {
                printf(" ");
            }
            printf("%d", x[i][j]);
        }
        printf("\n");
    }
}
