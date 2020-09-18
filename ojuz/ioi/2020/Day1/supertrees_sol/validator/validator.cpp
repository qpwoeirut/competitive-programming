#include "testlib.h"
using namespace std;

const int MAXN = 1000;
const int MAXP = 3;

const std::string input_secret = "005602cc-10e6-44fc-b5bf-57ff77778fe1";

vector<vector<int>> p;

int main() {
    registerValidation();
    string secret = inf.readLine();
    ensuref(secret == input_secret, "Secret not found!");

    int n = inf.readInt(1, MAXN, "n");
    inf.readEoln();

    p.resize(n);
    for (int i = 0; i < n; i++) {
        p[i].resize(n);
        for (int j = 0; j < n; j++) {
            if (j) {
                inf.readSpace();
            }
            p[i][j] = inf.readInt(0, MAXP, "p_i_j");
            if (i == j) {
                ensuref(p[i][j] == 1, "p_i_j must be equal to 1 when i=j!");
            }
            if (i > j) {
                ensuref(p[i][j] == p[j][i], "p must be symmetrical");
            }
        }
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
