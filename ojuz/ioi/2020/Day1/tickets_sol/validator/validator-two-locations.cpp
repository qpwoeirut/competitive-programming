#include "testlib.h"
using namespace std;

const int MAXC = 1500;
const int MAXS = 1500;
const int MAXK = 1500;

const int MAXD = 1;

int main() {
    registerValidation();
    inf.readLine();
    int c = inf.readInt(2, MAXC, "c");
    inf.readSpace();
    int s = inf.readInt(1, MAXS, "s");
    inf.readSpace();
    inf.readInt(1, MAXK, "k");
    inf.readEoln();
    for (int i = 0; i < c; i++) {
        for (int j = 0; j < s; j++) {
            if (j) {
                inf.readSpace();
            }
            inf.readInt(0, MAXD, "d_i_j");
        }
        inf.readEoln();
    }
    inf.readEof();
    return 0;
}