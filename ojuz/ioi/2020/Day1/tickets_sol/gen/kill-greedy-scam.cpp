#include "testlib.h"

using namespace std;

const int MAXD = 1e9;

int arr[1500][1500];
int main(int argc, char **argv) {
    registerGen(argc, argv, 0);

    int c = atoi(argv[1]);
    int s = atoi(argv[2]);
    int k = atoi(argv[3]);
    int d = atoi(argv[4]);

    printf("%d %d %d\n", c, s, k);
    for(int i=0; i<c; i++) {
        bool b = rnd.next(6);
        for(int j=0; j<s; j++) {
            bool c = rnd.next(6);
            if(d!=1) {
                if (b&&c) {
                    arr[i][j] = d/4*3 + rnd.next(d/4);
                } else if(b) {
                    arr[i][j] = rnd.next(d/4);
                } else {
                    arr[i][j] = d/4 + rnd.next(d/2);
                }
            } else {
                arr[i][j] = b^c;
            }
        }
        sort(arr[i], arr[i]+s);
    }
    for (int i = 0; i < c; i++) {
        for (int j = 0; j < s; j++) {
            if(j) {
                printf(" ");
            }
            printf("%d", arr[i][j]);
        }
        printf("\n");
    }
}
