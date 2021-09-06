#include <bits/stdc++.h>
#include "testlib.h"

using namespace std;

const int MX = 1000;

char grid[MX][MX];
string chars = "SEBO";

void fill_grid(int N, int M, char c) {
    for (int i=0; i<N; ++i) {
        for (int j=0; j<M; ++j) {
            grid[i][j] = c;
        }
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    int type = atoi(argv[1]);
    int N = atoi(argv[2]);
    int M = atoi(argv[3]);

    int sr = rnd.next(0, N-1);
    int sc = rnd.next(0, M-1);
    int er = rnd.next(0, N-1);
    int ec = rnd.next(0, M-1);
    assert(N*M >= 2);
    while (sr == er && sc == ec) {
        er = rnd.next(0, N-1);
        ec = rnd.next(0, M-1);
    }

    if (type == 0) {
        fill_grid(N, M, 'O');
    } else if (type == 1) {
        fill_grid(N, M, 'B');
    } else if (type == 2) {
        fill_grid(N, M, 'B');
        for (int i=0; i<N; ++i) {
            grid[i][0] = 'O';
            grid[i][M-1] = 'O';
            grid[0][i] = 'O';
            grid[N-1][i] = 'O';
        }
        for (int i=0; i<sr; ++i) {
            grid[i][sc] = 'O';
        }
        for (int i=0; i<er; ++i) {
            grid[i][ec] = 'O';
        }
    } else { 
        for (int i=0; i<N; ++i) {
            for (int j=0; j<M; ++j) {
                grid[i][j] = rnd.next(0, 99) > (type - 3) ? 'O' : 'B';
            }
        }
    }

    grid[sr][sc] = 'S';
    grid[er][ec] = 'E';

    cout << N << " " << M << '\n';
    for (int i=0; i<N; ++i) {
        for (int j=0; j<M; ++j) {
            cout << grid[i][j];
        }
        cout << '\n';
    }
}

