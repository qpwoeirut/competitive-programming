#include "testlib.h"
using namespace std;

const int MAXN = 1000;
const int MAXP = 3;

int main() {
    registerValidation();
    inf.readLine(); // Input Secret

    int n = inf.readInt(1, MAXN, "n");
    inf.readEoln();

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (j) {
                inf.readSpace();
            }
            int p = inf.readInt(0, MAXP, "p_i_j");
            ensuref(p == 0 || p == 1, "p_i_j must be 0 or 1!");
        }
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
