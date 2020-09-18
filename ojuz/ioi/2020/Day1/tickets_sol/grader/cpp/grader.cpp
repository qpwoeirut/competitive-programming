#include "tickets.h"
#include <cassert>
#include <cstdio>
#include <vector>
#include <string>

static int n;
static int m;
static int k;
static std::vector<std::vector<int>> d;
static std::vector<std::vector<int>> x;
static int called = 0;

static void check(bool cond, std::string message) {
    if (!cond) {
        // BEGIN SECRET
        const std::string output_secret = "131b432f-1f84-4f8f-9d55-41e868a6bc5d";
        printf("%s\n", output_secret.c_str());
        printf("WA\n");
        // END SECRET
        printf("%s\n", message.c_str());
        exit(0);
    }
}


void allocate_tickets( std::vector<std::vector<int>> _d) {
    check(!called, "allocate_tickets called more than once");
    d = _d;
    check((int)d.size() == n, "allocate_tickets called with parameter of wrong size");
    for (int i = 0; i < n; i++) {
        check((int)d[i].size() == m, "allocate_tickets called with parameter of wrong size");
    }
    called = 1;
}

int main() {
    // BEGIN SECRET
    const std::string input_secret = "df804a0e-e4b1-4b8d-a0f5-83401a72b5a3";
    const std::string output_secret = "131b432f-1f84-4f8f-9d55-41e868a6bc5d";
    char secret[1000];
    assert(1 == scanf("%s", secret));
    if (std::string(secret) != input_secret) {
        printf("%s\n", output_secret.c_str());
        printf("SV\n");
        fclose(stdout);
        return 0;
    }
    // END SECRET
    assert(scanf("%d %d %d", &n, &m, &k) == 3);
    x.resize(n);
    for (int i = 0; i < n; i++) {
        x[i].resize(m);
        for (int j=0; j < m; j++) {
            assert(scanf("%d", &x[i][j]) == 1);
        }
    }
    fclose(stdin);

    long long answer = find_maximum(k, x);
    check(called, "failure to call allocate_tickets");
    // BEGIN SECRET
    printf("%s\n", output_secret.c_str());
    printf("OK\n");
    // END SECRET
    printf("%lld\n", answer);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (j) printf(" ");
            printf("%d", d[i][j]);
        }
        printf("\n");
    }
    fclose(stdout);
    return 0;
}
