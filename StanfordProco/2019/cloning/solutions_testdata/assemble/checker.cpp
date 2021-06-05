#include <bits/stdc++.h>
#include "testlib.h"

using namespace std;

string str;

int count_sub(const string& s) {
    int count = 0;
    size_t nPos = str.find(s, 0);
    while(nPos != string::npos) {
        count++;
        nPos = str.find(s, nPos + 1);
    }
    return count;
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);
    
    str = inf.readLine();

    string a1 = ans.readLine();
    string a2 = ans.readLine();
    string o1 = ouf.readLine();
    string o2 = ouf.readLine();

    int ca1 = count_sub(a1);
    int ca2 = count_sub(a2);
    int co1 = count_sub(o1);
    int co2 = count_sub(o2);

    if (ca1 > co1) {
        ouf.quitf(_wa, "incorrect, more frequent substring exists");
    }
    if (ca2 == 0) {
        ans.quitf(_wa, "substring does not exist");
    }
    if (co2 == 0) {
        ouf.quitf(_wa, "substring does not exist");
    }
    if (ca2 < co2) {
        ouf.quitf(_wa, "incorrect, less frequent substring exists");
    }

    quitf(_ok, "");
}
