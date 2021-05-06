#include <bits/stdc++.h>
#include "testlib.h"

using namespace std;

int MIN_VAL, MAX_VAL; // check if ll is needed

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    MIN_VAL = atoi(argv[1]);
    MAX_VAL = atoi(argv[2]);

    cout << rnd.next(MIN_VAL, MAX_VAL) << '\n';
}

