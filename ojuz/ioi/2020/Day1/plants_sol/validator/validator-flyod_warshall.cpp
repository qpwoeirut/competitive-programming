#include "testlib.h"
using namespace std;

const int MAXN = 300;
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
	inf.readInt(MINK, n, "k");
	inf.readSpace();
	int q = inf.readInt(MINQ, MAXQ, "q");
	ensuref(q<=n*(n-1)/2, "Too many queries.");

	skip_ok();
	return 0;
}
