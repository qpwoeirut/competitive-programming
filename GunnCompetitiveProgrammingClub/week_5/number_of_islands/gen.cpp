#include <bits/stdc++.h>
#include "testlib.h"

using namespace std;

const int MX = 1000;

char grid[MX][MX];

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    int type = atoi(argv[1]);
    int N = atoi(argv[2]);
    int M = atoi(argv[3]);

    for (int i=0; i<N; ++i) {
        for (int j=0; j<M; ++j) {
            grid[i][j] = 'W';
        }
    }

    if (type == 0) {
        // all water
    } else if (type == 1) {
        for (int i=0; i<N; ++i) {
            for (int j=0; j<M; ++j) {
                grid[i][j] = 'L';
            }
        }
    } else if (type == 2) {
        for (int i=0; i<N; ++i) {
            for (int j=0; j<M; ++j) {
                grid[i][j] = ((i+j) & 1) ? 'W' : 'L';
            }
        }
    } else { 
        for (int i=0; i<N; ++i) {
            for (int j=0; j<M; ++j) {
                grid[i][j] = rnd.next(0, 99) > (type - 3) ? 'W' : 'L';
            }
        }
    }

    cout << N << " " << M << '\n';
    for (int i=0; i<N; ++i) {
        for (int j=0; j<M; ++j) {
            cout << grid[i][j];
        }
        cout << '\n';
    }
}

