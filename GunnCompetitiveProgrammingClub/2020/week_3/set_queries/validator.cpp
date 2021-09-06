#include <bits/stdc++.h>
#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);
    int n = inf.readInt(1, 1e5, "n");
    inf.readSpace();
    int q = inf.readInt(1, 1e5, "q");
    inf.readEoln();

    for (int i=0; i<n; ++i) {
        inf.readInt(-1e9, 1e9, "a_i");
        if (i+1 < n) {
            inf.readSpace();
        }
    }
    inf.readEoln();

    for (int i=0; i<q; ++i) {
        int t = inf.readInt(1, 4, "t_i");
        if (t != 3) {
            inf.readSpace();
            int x = inf.readInt(-1e9, 1e9, "x_i");
        }
        inf.readEoln();
    }
    inf.readEof();
}
