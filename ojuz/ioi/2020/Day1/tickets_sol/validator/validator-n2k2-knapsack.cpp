#include "testlib.h"
using namespace std;

const int MAXC = 80;
const int MAXS = 80;
const int MAXK = 80;

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