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

    for (int i=0; i<n; ++i) {
        string s = inf.readToken("[WL]+", "s");
        ensure(s.size() == m);
        inf.readEoln();
    }
    inf.readEof();
}
