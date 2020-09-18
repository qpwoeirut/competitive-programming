#include "testlib.h"
#include <vector>

const std::string output_secret = "131b432f-1f84-4f8f-9d55-41e868a6bc5d";

int main(int argc, char * argv[]) {
    registerChecker("tickets", argc, argv);

    readBothSecrets(output_secret);
    readBothGraderResults();

    long long answer = ouf.readLong(); // contestant output
    long long actual = ans.readLong(); // correct answer


    // Read from input file
    inf.readLine(); // Input secret
    int c = inf.readInt();
    int s = inf.readInt();
    int k = inf.readInt();
    std::vector<std::vector<int>> d;
    d.resize(c);
    for (int i = 0; i < c; i++) {
        d[i].resize(s);
        for (int j = 0; j < s; j++) {
            d[i][j] = inf.readInt();
        }
    }

    // Validate output file rows
    std::vector<std::vector<int>> x; //x[day][company] = location
    x.resize(k);
    for (int i = 0; i < c; i++) {
        for (int j = 0; j < s; j++) {
            int day = ouf.readInt();
            if (0 <= day && day < k) {
                // Ship i,j was sent on day loc
                x[day].push_back(d[i][j]);
            } else if (day != -1) {
                quitf(_wa, "Ticket %d of color %d is played on invalid day %d", i, j, day);
            }
        }
        // All days should now have i+1 boats
        for (int j = 0; j < k; j++) {
            if ((int)x[j].size() < i + 1) {
                quitf(_wa, "There is no ticket of color %d on day %d", i, j);
            } else if ((int)x[j].size() > i + 1) {
                quitf(_wa, "There is multiple tickets of color %d on day %d", i, j);
            }
        }
    }

    // Calculate actual cost
    long long calculated = 0;
    for (int i = 0; i < k; i++) {
        sort(x[i].begin(), x[i].end());
        for (int j = 0; j < c; j++) {
            calculated += abs(x[i][j] - x[i][c/2]);
        }
    }

    if (calculated != answer) {
        quitf(_wa, "Contestant returned %lld but the tickets gives a total value of %lld", calculated, answer);
    }

    if (answer > actual) {
        quitf(_fail, "Contestant found a better solution than model.");
    } else if (answer < actual) {
        quitf(_wa, "Contestant returned %lld while correct return value is %lld.", answer, actual);
    }
    quit(_ok);
}
