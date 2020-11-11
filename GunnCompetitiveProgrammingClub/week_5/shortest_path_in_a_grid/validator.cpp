#include <bits/stdc++.h>
#include "testlib.h"

using namespace std;

const int MX = 1000;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);
    int n = inf.readInt(1, MX, "n");
    inf.readSpace();
    int m = inf.readInt(1, MX, "m");
    inf.readEoln();

    int starts = 0, ends = 0;
    for (int i=0; i<n; ++i) {
        string s = inf.readToken("[SEBO]+", "s");
        ensure(s.size() == m);
        for (int j=0; j<m; ++j) {
            if (s[j] == 'S') ++starts;
            if (s[j] == 'E') ++ends;
        }
        inf.readEoln();
    }
    inf.readEof();
    ensure(starts == 1);
    ensure(ends == 1);
}
