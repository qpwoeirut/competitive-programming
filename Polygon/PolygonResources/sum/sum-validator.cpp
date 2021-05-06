#include "testlib.h"

using namespace std;

const int MX = 1e9;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);
    inf.readInt(-MX, MX, "a");
    inf.readSpace();
    inf.readInt(-MX, MX, "b");
    inf.readEoln();
    inf.readEof();
}
