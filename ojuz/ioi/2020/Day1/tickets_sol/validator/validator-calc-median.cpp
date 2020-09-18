#include "testlib.h"
using namespace std;

const int MAXC = 1500;
const int MAXS = 1;

int main() {
    registerValidation();
    inf.readLine();
    inf.readInt(2, MAXC, "c");
    inf.readSpace();
    inf.readInt(1, MAXS, "s");
    skip_ok();
    return 0;
}