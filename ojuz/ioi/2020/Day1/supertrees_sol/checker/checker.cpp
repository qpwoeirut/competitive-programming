#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

const std::string output_secret = "1f0934cc-cf56-429c-b010-8533ab3ded9e";

const int MAXP = 3;
const int MAXB = 1;

int n;
std::vector<std::vector<int>> p, b, b_adj;
vector<vector<int>> actual_ways;
vector<int> visited;

void too_many(int src, int dst) {
    quitf(
        _wa,
        "Too many ways to get from %d to %d, should be %d found no less than %d",
        src, 
        dst, 
        p[src][dst], 
        actual_ways[src][dst]
    );
}

void dfs(int src, int x) {
    visited[x] = 1;
    // printf("in %d / ", x);
    actual_ways[src][x] += 1;
    if (actual_ways[src][x] > p[src][x]) {
        too_many(src, x);
    }
    for (int i = 0; i < (int) b_adj[x].size(); i++) {
        if (!visited[b_adj[x][i]]) {
            dfs(src, b_adj[x][i]);
        }
    }
    // printf("out %d / ", x);
    visited[x] = 0;
}

int main(int argc, char * argv[]) {
    registerChecker("supertrees", argc, argv);
    
    readBothSecrets(output_secret);
    readBothGraderResults();

    inf.readLine(); // Input Secret
    n = inf.readInt();

    int actual_possible = ans.readInt();
    int possible = ouf.readInt();

    if (actual_possible != possible) {
        quitf(_wa, "Answer gives possible %d while actual possible %d", possible, actual_possible);
    }

    if (!possible) {
        quit(_ok);
    }

    p.resize(n);
    b.resize(n);
    b_adj.resize(n);
    for (int i = 0; i < n; i++) {
        p[i] = inf.readInts(n, 0, MAXP, "p_i_j");
        b[i] = ouf.readInts(n, 0, MAXB, "b_i_j");
        for (int j = 0; j < n; j++) {
            if (b[i][j]) {
                b_adj[i].push_back(j);
            }
        }
    }

    // Check that b is symmetric
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (b[i][j] != b[j][i]) {
                quitf(_wa, "b is not symmetric: b[%d][%d] (%d) != b[%d][%d] (%d)", i, j, b[i][j], j, i, b[j][i]);
            }
        }
    }
    
    // Check that b diagonal is 0
    for (int i = 0; i < n; i++) {
		if (b[i][i] != 0) {
			quitf(_wa, "b[%d][%d] is not 0", i, i);
		}
	}

    // Populate actual_ways
    actual_ways.resize(n);
    for (int i = 0; i < n; i++) {
        actual_ways[i].resize(n, 0);
    }
    visited.resize(n, 0);

    for (int i = 0; i < n; i++) {
        dfs(i, i);
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (p[i][j] != actual_ways[i][j]) {
                quitf(
                    _wa,
                    "Too few ways to get from %d to %d, should be %d found %d",
                    i, 
                    j, 
                    p[i][j], 
                    actual_ways[i][j]
                );
            }
        }
    }

    quit(_ok);

    // if (mismatch) {
    // 	// Printf and give WA
    // 	quit(_wa, "Path count of construction b does not match p");
    // } else {
    // 	// Give AC
    // 	quit(_ok);
    // }
}
