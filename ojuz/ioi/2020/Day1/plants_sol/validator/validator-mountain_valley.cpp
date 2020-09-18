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
	inf.readInt(MINN, MAXN, "n");
	inf.readSpace();
	int k = inf.readInt(MINK, MAXK, "k");
	ensuref(k==2, "k must be equal to 2!");
	skip_ok();

	return 0;
}
