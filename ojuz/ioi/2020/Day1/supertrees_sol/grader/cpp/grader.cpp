#include "supertrees.h"
#include <vector>
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <string>

static int n;
static std::vector<std::vector<int>> p;
static std::vector<std::vector<int>> b;
static bool called = false;

static void check(bool cond, std::string message) {
    if (!cond) {
        // BEGIN SECRET
        const std::string output_secret = "1f0934cc-cf56-429c-b010-8533ab3ded9e";
        printf("%s\n", output_secret.c_str());
        printf("WA\n");
        // END SECRET
        printf("%s\n", message.c_str());
        fclose(stdout);
        exit(0);
    }
}

void build(std::vector<std::vector<int>> _b) {
    check(!called, "build is called more than once");
    called = true;
    check((int)_b.size() == n, "Invalid number of rows in b");
    for (int i = 0; i < n; i++) {
        check((int)_b[i].size() == n, "Invalid number of columns in b");
    }
    b = _b;
}

int main() {
    // BEGIN SECRET
    const std::string input_secret = "005602cc-10e6-44fc-b5bf-57ff77778fe1";
    const std::string output_secret = "1f0934cc-cf56-429c-b010-8533ab3ded9e";
    char secret[1000];
    assert(1 == scanf("%s", secret));
    if (std::string(secret) != input_secret) {
        printf("%s\n", output_secret.c_str());
        printf("SV\n");
        fclose(stdout);
        return 0;
    }
    // END SECRET
    assert(scanf("%d", &n) == 1);
    
    p.resize(n);
    for (int i = 0; i < n; i++) {
        p[i].resize(n);
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            assert(scanf("%d", &p[i][j]) == 1);
        }
    }
    fclose(stdin);

    int possible = construct(p);

    check(possible == 0 || possible == 1, "Invalid return value of construct");
    if (possible == 1) {
        check(called, "construct returned 1 without calling build");
    } else {
        check(!called, "construct called build but returned 0");
    }

    // BEGIN SECRET
    printf("%s\n", output_secret.c_str());
    printf("OK\n");
    // END SECRET
    printf("%d\n", possible);
    if (possible == 1) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (j) {
                    printf(" ");
                }
                printf("%d", b[i][j]);
            }
            printf("\n");
        }
    }
    fclose(stdout);
}
