#include "testlib.h"
using namespace std;

const int MAXC = 300;
const int MAXS = 300;
const int MAXK = 300;

int main() {
    registerValidation();
    inf.readLine();
    inf.readInt(2, MAXC, "c");
    inf.readSpace();
    inf.readInt(1, MAXS, "s");
    inf.readSpace();
    inf.readInt(1, MAXK, "k");
    skip_ok();
    return 0;
}