//474c.cpp created at 02/21/21 21:59:33

#include <bits/stdc++.h>

using namespace std;

#define x real()
#define y imag()

typedef long long ll;
typedef complex<ll> pt;

const int MN = 102;
const int INIT = 1001001001;

int N;
int ans[MN];

pt A[4], B[4];
bool is_square() {
    int idx[4] = {0, 1, 2, 3};

    for (int i=0; i<4; ++i) {
        for (int j=i+1; j<4; ++j) {
            if (A[i] == A[j]) return false;
        }
    }

    do {
        bool ok = true;
        ll side = norm(A[idx[3]] - A[idx[0]]);
        for (int i=0; i<3; ++i) {
            if (side != norm(A[idx[i+1]] - A[idx[i]])) {
                ok = false;
                break;
            }
        }
        if (ok && norm(A[idx[2]] - A[idx[0]]) == norm(A[idx[3]] - A[idx[1]])) {
            return true;
        }
    } while (next_permutation(idx, idx+4));

    return false;
}

void rot_pt(const int idx) {
    pt shifted = A[idx] - B[idx];
    A[idx] = pt(-shifted.y, shifted.x) + B[idx];
}

int solve() {
    for (int i=0; i<4; ++i) {
        int px, py, ax, ay;
        cin >> px >> py >> ax >> ay;
        A[i] = pt(px, py);
        B[i] = pt(ax, ay);
    }

    int cost = INIT;
    for (int i=0; i<4; ++i) {
        for (int j=0; j<4; ++j) {
            for (int k=0; k<4; ++k) {
                for (int l=0; l<4; ++l) {
                    if (is_square()) {
                        cost = min(cost, i + j + k + l);
                    }
                    rot_pt(3);
                }
                rot_pt(2);
            }
            rot_pt(1);
        }
        rot_pt(0);
    }

    return cost == INIT ? -1 : cost;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> N;
    for (int i=0; i<N; ++i) {
        ans[i] = solve();
    }

    for (int i=0; i<N; ++i) {
        cout << ans[i] << '\n';
    }
}

