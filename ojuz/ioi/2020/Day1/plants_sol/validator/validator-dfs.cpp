#include "testlib.h"
using namespace std;

const int MAXN = 200000;
const int MINN = 2;
const int MAXK = MAXN;
const int MINK = MINN;
const int MAXQ = 200000;
const int MINQ = 1;

const string input_secret = "1b32a07d5f5fc55f21038b12a3655e";
int main() {
    registerValidation();
	string secret = inf.readLine();
	ensuref(secret == input_secret, "Secret not found!");
	int n = inf.readInt(MINN, MAXN, "n");
	inf.readSpace();
	int k = inf.readInt(MINK, MAXK, "k");
	inf.readSpace();
	int q = inf.readInt(1, MAXQ, "q");
	inf.readEoln();
    for(int i=0; i<n; i++) {
        if(i) inf.readSpace();
        inf.readInt(0, k-1, "r_i");
	}
	inf.readEoln();
	for(int i = 0; i < q; i++) {
        int x = inf.readInt();
        ensuref(x==0, "x must be 0");
        inf.readSpace();
        inf.readInt();
        inf.readEoln();
	}
	skip_ok();
	return 0;
}
