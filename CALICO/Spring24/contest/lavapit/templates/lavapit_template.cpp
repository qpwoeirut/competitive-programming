#include <iostream>
#include <vector>
#include <string>

using namespace std;

/**
 * Return the maximum number of diamonds that Steve can mine before exiting the lava pit.
 * 
 * N: number of rows in the lava pit
 * M: number of columns in the lava pit
 * G: description of the lava pit
 */
int solve(int N, int M, vector<string> G) {
    // YOUR CODE HERE
    return -1;
}

int main() {
    int T;
    cin >> T;
    while (T--) {
        int N, M;
        cin >> N >> M;
        vector<string> G(N);
        for (int i = 0; i < N; ++i) {
            cin >> G[i];
        }
        cout << solve(N, M, G) << '\n';
    }
}
