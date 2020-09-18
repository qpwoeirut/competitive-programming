#include "testlib.h"
using namespace std;

const int MAXC = 1500;
const int MAXS = 1500;
const int MAXK = 1500;

int main() {
    registerValidation();
    inf.readLine();
    inf.readInt(2, MAXC, "c");
    inf.readSpace();
    int s = inf.readInt(1, MAXS, "s");
    inf.readSpace();
    int k = inf.readInt(1, MAXK, "k");
    ensuref(k == s, "k must be equal to s!");
    skip_ok();
    return 0;
}