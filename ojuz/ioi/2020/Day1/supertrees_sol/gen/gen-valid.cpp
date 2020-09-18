#include "testlib.h"
#include <cmath>
#include <cassert>

using namespace std;

const int MAXN = 1000;

/*
Usage:
./gen-valid [n] [connected] [isolated]

n: Total # of nodes
trees: # of tree connected components
cycles: # of cycle connected components
hairys: # of cycles with offshoots connected components
solos: # of disconnected components
scramble: To randomize node ids after generation
    - 0: No shuffle
    - 1: Shuffle
flip: Arbitarily randomize some nodes, likely to make construction impossible
    - 0: No flip
    - #: Number of nodes to flip
flip_set: Character set to use when generating flipped, provide only if flip is non zero
*/

int n;
int trees, cycles, hairys, solos;
int scramble, flip;
string flip_set;

vector<int> cc_size;
vector<pair<int, int>> cc_ids;

vector<vector<int>> p;
vector<int> permutation;

int main(int argc, char **argv) {
    registerGen(argc, argv, 0);

    n = atoi(argv[1]);

    trees = atoi(argv[2]);
    cycles = atoi(argv[3]);
    hairys = atoi(argv[4]);
    solos = atoi(argv[5]);

    scramble = atoi(argv[6]);
    flip = atoi(argv[7]);

    if (flip) {
        flip_set = string(argv[8]);
    }

    int reserved = solos + trees * 2 + (cycles + hairys) * 3;

    assert(reserved<= n);

    int connected = trees + cycles + hairys;

    // Allocate the minimum required 
    for (int i = 0; i < trees; i++) {
        cc_size.push_back(2);
    }
    for (int i = 0; i < cycles + hairys; i++) {
        cc_size.push_back(3);
    }
    // Distribute the remaining nodes
    for (int i = reserved; i < n; i++) {
        int cc = rnd.next(connected);
        cc_size[cc]++;
    }
    for (int i = 0; i < solos; i++) {
        cc_size.push_back(1);
    }

    for (int i = 0; i < (int) cc_size.size(); i++) {
        int cc_sz = cc_size[i];
        if (i < trees + cycles) {
            // Tree or cycle component, give all the same id
            for (int j = 0; j < cc_sz; j++) {
                cc_ids.push_back({i, 0});
            }
        } else if (i < trees + cycles + hairys) {
            // Hairy component, give all same id but different sub-id
            int cycle_len = rnd.next(3, cc_sz);
            for (int j = 0; j < cycle_len; j++) {
                cc_ids.push_back({i, j});
            }
            for (int j = cycle_len; j < cc_sz; j++) {
                cc_ids.push_back({i, rnd.next(cycle_len)});
            }
        } else if (cc_sz == 1){
            // Solo component, give different ids
            cc_ids.push_back({i, 0});
        } else {
            // Shouldn't happen
            assert(0);
        }
    }

    sort(cc_ids.begin(), cc_ids.end());

    // Fill p
    p.resize(n);
    for (int i = 0; i < n; i++) {
        p[i].resize(n, 0);
        for (int j = 0; j < n; j++) {
            if (i == j) {
                p[i][j] = 1;
            } else if (cc_ids[i].first != cc_ids[j].first) {
                p[i][j] = 0;
            } else if (cc_ids[i].first < trees) {
                // Tree component, all 1s
                p[i][j] = 1;
            } else if (cc_ids[i].first < trees + cycles) {
                // Cycle component, all 2s
                p[i][j] = 2;
            } else if (cc_ids[i].second != cc_ids[j].second) {
                // Hair component on different hairs, all 2s
                p[i][j] = 2;
            } else if (cc_ids[i].second == cc_ids[j].second) {
                // Hair component on same hair, all 1s
                p[i][j] = 1;
            }
        }
    }

    for (int i = 0; i < n; i++) {
        permutation.push_back(i);
    }
    if (scramble) {
        shuffle(permutation.begin(), permutation.end());
    }

    // Randomly flip some
    for (int i = 0; i < flip; i++) {
        int x = rnd.next(n);
        int y = rnd.next(n);
        if (x != y) {
            int after_flip = flip_set[rnd.next(flip_set.size())] - '0';
            p[x][y] = after_flip;
            p[y][x] = after_flip;
        }
    }

    // Print out to testcase
    printf("%d\n", n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (j) {
                printf(" ");
            }
            printf("%d", p[permutation[i]][permutation[j]]);
        }
        printf("\n");
    }
}