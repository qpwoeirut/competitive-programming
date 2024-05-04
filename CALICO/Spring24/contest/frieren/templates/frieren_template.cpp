#include <iostream>

using namespace std;

/**
 * Return the number of times the given person sees the Era Meteor Shower over the course of their life, it it occurs every fifty years.
 * 
 * B: the number of years ago when someone was born
 * L: the lifespan of that person
 * E: the number of years until the next Era Meteor Shower
 */
int solve(int B, int L, int E) {
    return -1;
}

int main() {
    int T;
    cin >> T;
    for (int i = 0; i < T; i++) {
        int B, L, E;
        cin >> B >> L >> E;
        cout << solve(B, L, E) << '\n';
    }
}
