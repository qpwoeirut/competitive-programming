#include "testlib.h"
using namespace std;

const int MAXC = 1500;
const int MAXS = 1500;
const int MAXK = 1500;

const int MAXD = 1e9;

const std::string input_secret = "df804a0e-e4b1-4b8d-a0f5-83401a72b5a3";

int main() {
    registerValidation();
    string secret = inf.readLine();
    ensuref(secret == input_secret, "Secret not found!");
    int c = inf.readInt(2, MAXC, "c");
    ensuref(c % 2 == 0, "c is not even!");
    inf.readSpace();
    int s = inf.readInt(1, MAXS, "s");
    inf.readSpace();
    int k = inf.readInt(1, MAXK, "k");
    ensuref(k <= s, "k cannot be larger than s!");
    inf.readEoln();
    int x[s];
    for (int i = 0; i < c; i++) {
        for (int j = 0; j < s; j++) {
            if (j) {
                inf.readSpace();
            }
            x[j] = inf.readInt(0, MAXD, "d_i_j");
        }
        for(int j=1; j<s; j++) {
            ensuref(x[j-1]<=x[j], "Tickets must be sorted in ascending order");
        }
        inf.readEoln();
    }
    inf.readEof();
    return 0;
}
