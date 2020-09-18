#include "testlib.h"
using namespace std;

static string output_secret = "23b69acd873f5d7e892bae7de83615";

int main(int argc, char * argv[])
{
	registerChecker("plants", argc, argv);

	readBothSecrets(output_secret);
	readBothGraderResults();

	compareRemainingLines();
}
