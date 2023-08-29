//two_rods.cpp created at 08/28/23 16:34:22

#include <bits/stdc++.h>

using namespace std;

const int MAX_TEST_N = 50;

bool DEBUG = true;
string SECRET[MAX_TEST_N];
int query_ct = 0;

int N;
bool query(const int t, const int l, const int b, const int r) {
    ++query_ct;

    cout << "? " << t << ' ' << b << ' ' << l << ' ' << r << '\n';
    cout.flush();

    int resp = 0;
    if (DEBUG) {
        for (int row=t; row<=b; ++row) {
            for (int col=l; col<=r; ++col) {
                resp |= SECRET[row-1][col-1] == 'x';
            }
        }
        cout << resp << '\n';
    } else {
        cin >> resp;
    }

    return resp == 1;
}

int find_boundary(const int side) {
    int lo = 1, hi = N;
    while (lo < hi) {
        int mid = (lo + hi + (side >= 2)) / 2;
        if (side == 0) {
            if (query(1, 1, mid, N)) hi = mid;
            else lo = mid + 1;
        } else if (side == 1) {
            if (query(1, 1, N, mid)) hi = mid;
            else lo = mid + 1;
        } else if (side == 2) {
            if (query(mid, 1, N, N)) lo = mid;
            else hi = mid - 1;
        } else if (side == 3) {
            if (query(1, mid, N, N)) lo = mid;
            else hi = mid - 1;
        } else assert(0 <= side && side < 4);
    }
    return lo;
}

int find_rod(const int out_t, const int out_l, const int out_b, const int out_r, const bool vert) {
    int lo = vert ? out_l : out_t;
    int hi = vert ? out_r : out_b;

    while (lo < hi) {
        int mid = (lo + hi) / 2;
        if (vert) {
            if (query(out_t, out_l, out_t, mid) && query(out_b, out_l, out_b, mid)) hi = mid;
            else lo = mid + 1;
        } else {
            if (query(out_t, out_l, mid, out_l) && query(out_t, out_r, mid, out_r)) hi = mid;
            else lo = mid + 1;
        }
    }
    return lo;
}

array<int, 8> solve() {
    query_ct = 0;

    const int out_t = find_boundary(0);
    const int out_l = find_boundary(1);
    const int out_b = find_boundary(2);
    const int out_r = find_boundary(3);

    const int row = find_rod(out_t, out_l, out_b, out_r, false);
    const int col = find_rod(out_t, out_l, out_b, out_r, true);

    return array<int, 8>({row, out_l, row, out_r, out_t, col, out_b, col});
}

string to_string(const array<int, 8>& arr) {
    return "[" + to_string(arr[0]) + ", " + to_string(arr[1]) + ", " + to_string(arr[2]) + ", " + to_string(arr[3]) + ", " + to_string(arr[4]) + ", " + to_string(arr[5]) + ", " + to_string(arr[6]) + ", " + to_string(arr[7]) + "]";
}

void test() {
    mt19937 rng(8);
    DEBUG = true;
    for (N=5; N<=MAX_TEST_N; ++N) {
        for (int t=0; t<100000; ++t) {
            int row = rng() % N;
            int c1 = rng() % N;
            int c2 = rng() % N;
            if (c1 > c2) swap(c1, c2);
            else if (c1 == c2) c1 = max(0, c1 - 1), c2 = min(c2 + 1, N - 1);

            int col = rng() % N;
            int r1 = rng() % N;
            int r2 = rng() % N;
            if (r1 > r2) swap(r1, r2);
            else if (r1 == r2) r1 = max(0, r1 - 1), r2 = min(r2 + 1, N - 1);
            
            if (c1 <= col && col <= c2 && r1 - 1 == row) --r1;
            if (c1 <= col && col <= c2 && r2 + 1 == row) ++r2;
            if (r1 <= row && row <= r2 && c1 - 1 == col) --c1;
            if (r1 <= row && row <= r2 && c2 + 1 == col) ++c2;

            for (int r=0; r<N; ++r) {
                SECRET[r] = string(N, '.');
            }
            for (int c=c1; c<=c2; ++c) {
                SECRET[row][c] = 'x';
            }
            for (int r=r1; r<=r2; ++r) {
                SECRET[r][col] = 'x';
            }

            array<int, 8> expected({row + 1, c1 + 1, row + 1, c2 + 1, r1 + 1, col + 1, r2 + 1, col + 1});
            array<int, 8> ans = solve();
            if (ans != expected || query_ct >= 400) {
                for (int r=0; r<N; ++r) {
                    cout << SECRET[r] << '\n';
                }
                cout << to_string(expected) << '\n';
                cout << to_string(ans) << endl;
            }
            assert(ans == expected);
        }
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    test(); return 0;

    cin >> N;
    array<int, 8> ans = solve();
    cout << '!';
    for (int x: ans) cout << ' ' << x;
    cout << '\n';
}

