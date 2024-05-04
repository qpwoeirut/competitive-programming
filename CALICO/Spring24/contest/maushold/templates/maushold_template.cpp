#include <iostream>
#include <vector>
#include <cassert>

using namespace std;

using ll = long long;

/**
 * Return the probability of your Pokemon fainting after being hit with Population Bomb.
 * If the probability is p/q, return p * q^-1 mod 1000000007
 * 
 * H: Your Pokemon's HP
 * N: Number of times that Population Bomb hits
 * M: Number of damage rolls
 * R: List of the M damage rolls
 */
int solve(int H, ll N, int M, vector<int> const& R) {
    // YOUR CODE HERE
    return -1;
}

int main() {
    int H, M; ll N;
    cin >> H >> N >> M;
    vector<int> R(M);
    for (int j = 0; j < M; ++j)
        cin >> R[j];
    cout << solve(H, N, M, R) << '\n';
    return 0;
}
