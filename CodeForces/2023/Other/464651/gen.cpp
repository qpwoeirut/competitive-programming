#include "jngen.h"
#include <iostream>

using namespace std;
using pii=pair<int,int>;
 
const int MAXN = 100, MAXK = 10, SPARSE = 10;

int main(int argc, char *argv[]) {
    registerGen(argc, argv);
    parseArgs(argc, argv);

    int max_n = getOpt(0);
    int sparse = getOpt(1);

    int n = rnd.next(max(1, max_n - MAXK), max_n);
    int sp = min(n * (n - 1)/2 - 1, max(n - 1, n * n/SPARSE));
    int m = (sparse? rnd.next(n - 1, sp) : rnd.next(sp + 1, n * (n - 1)/2));
    auto g = Graph::random(n, m).connected().g().shuffled();
    cout << g.printN().printM().add1() << endl;
}
