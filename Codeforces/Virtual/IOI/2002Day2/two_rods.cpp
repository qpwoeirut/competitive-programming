//two_rods.cpp created at 08/28/23 17:34:14

#include <bits/stdc++.h>

using namespace std;
using pii=pair<int,int>;

const int MN = 10000;
const int MQ = 400;
const int TEST_N = 50;

struct QueryResult {
    int top, left, bottom, right;
    bool response;
    QueryResult() : QueryResult(0, 0, 0, 0, false) {}
    QueryResult(const int t, const int l, const int b, const int r, const bool resp) : top(t), left(l), bottom(b), right(r), response(resp) {}

    inline bool is_in(const int t, const int l, const int b, const int r) const {
        return t <= top && l <= left && bottom <= b && right <= r;
    }
    inline bool holds(const int t, const int l, const int b, const int r) const {
        return top <= t && left <= l && b <= bottom && r <= right;
    }
};

QueryResult queries[MQ];
int query_ct = 0;

bool DEBUG = false;
string SECRET[MN];

int N;
bool query(const int t, const int l, const int b, const int r) {
    if (t < 1 || t > N || l < 1 || l > N || b < 1 || b > N || r < 1 || r > N) return false;

    for (int q=0; q<query_ct; ++q) {
        if (queries[q].response == true  && queries[q].is_in(t, l, b, r)) return true;
        if (queries[q].response == false && queries[q].holds(t, l, b, r)) return false;
    }

    int resp = 0;
    if (DEBUG) {
        for (int row=t; row<=b; ++row) {
            for (int col=l; col<=r; ++col) {
                resp |= SECRET[row-1][col-1] == 'x';
            }
        }
    } else {
        cout << "? " << t << ' ' << b << ' ' << l << ' ' << r << '\n';
        cout.flush();
        cin >> resp;
    }

    queries[query_ct++] = QueryResult(t, l, b, r, resp == 1);

    return resp == 1;
}

int find_boundary(const bool side, const int row, const int col, const int mnr = 1, const int mxr = N, const int mnc = 1, const int mxc = N) {
    const int r1 = row == -1 ? mnr : row;
    const int r2 = row == -1 ? mxr : row;
    const int c1 = col == -1 ? mnc : col;
    const int c2 = col == -1 ? mxc : col;
    int lo = !side ? mnr : mnc, hi = !side ? mxr : mxc;
    while (lo < hi) {
        const int mid = (lo + hi) / 2;
        if (side == 0) {
            if (query(mnr, c1, mid, c2)) hi = mid;
            else lo = mid + 1;
        } else if (side == 1) {
            if (query(r1, mnc, r2, mid)) hi = mid;
            else lo = mid + 1;
        }
    }
    return lo;
}

int find_hreach(const int row, const int c1, const bool check) {
    if (check && !query(row, c1 + 1, row, c1 + 1)) return c1;
    int lo = c1 + check, hi = N;
    while (lo < hi) {
        const int mid = (lo + hi + 1) / 2;
        if (query(row, mid - 1, row, mid - 1) && query(row, mid, row, mid)) lo = mid;
        else hi = mid - 1;
    }
    return lo;
}
int find_vreach(const int r1, const int col, const bool check) {
    if (check && !query(r1 + 1, col, r1 + 1, col)) return r1;
    int lo = r1 + check, hi = N;
    while (lo < hi) {
        const int mid = (lo + hi + 1) / 2;
        if (query(mid - 1, col, mid - 1, col) && query(mid, col, mid, col)) lo = mid;
        else hi = mid - 1;
    }
    return lo;
}

array<int, 8> solve() {
    query_ct = 0;

    int rod1_t = find_boundary(0, -1, -1);
    int rod1_l = find_boundary(1, rod1_t, -1);
    int rod1_b = find_vreach(rod1_t, rod1_l, true);
    int rod1_r = find_hreach(rod1_t, rod1_l, true);
    //cerr << "tlbr 1: " << rod1_t << ' ' << rod1_l << ' ' << rod1_b << ' ' << rod1_r << endl;
    if (rod1_t != rod1_b && rod1_l != rod1_r) {
        return array<int, 8>({rod1_t, rod1_l, rod1_t, rod1_r, rod1_t, rod1_l, rod1_b, rod1_l});
    }

    if (rod1_t == rod1_b) {
        int mnr = 1, mxr = N;
        if (query(1, 1, rod1_t - 1, N)) {
            mxr = rod1_t - 1;
        } else {
            mnr = rod1_t + 1;
        }
        int rod2_t = find_boundary(0, -1, -1, mnr, mxr);
        int rod2_l = find_boundary(1, rod2_t, -1, mnr, mxr);
        int rod2_b = find_vreach(rod2_t, rod2_l, false);
        int rod2_r = rod2_l; //find_hreach(rod2_t, rod2_l);
        //cerr << "tlbr 2: " << rod2_t << ' ' << rod2_l << ' ' << rod2_b << ' ' << rod2_r << endl;

        assert(rod1_t == rod1_b);
        assert(rod2_l == rod2_r);
        if (rod1_l <= rod2_l && rod2_r <= rod1_r && rod2_t - 1 == rod1_t) --rod2_t;
        if (rod1_l <= rod2_l && rod2_r <= rod1_r && rod2_b + 1 == rod1_b) ++rod2_b;
        if (rod2_t <= rod1_t && rod1_b <= rod2_b && rod1_l - 1 == rod2_l) --rod1_l;
        if (rod2_t <= rod1_t && rod1_b <= rod2_b && rod1_r + 1 == rod2_r) ++rod1_r;

        if (rod2_t - 1 == rod1_t && query(rod2_t - 1, rod2_l, rod2_t - 1, rod2_l)) --rod2_t;
        if (rod2_b + 1 == rod1_b && query(rod2_b + 1, rod2_l, rod2_b + 1, rod2_l)) ++rod2_b;

        return array<int, 8>({rod1_t, rod1_l, rod1_b, rod1_r, rod2_t, rod2_l, rod2_b, rod2_r});
    } else {
        int mnc = 1, mxc = N;
        if (query(1, 1, N, rod1_l - 1)) {
            mxc = rod1_l - 1;
        } else {
            mnc = rod1_l + 1;
        }
        int rod0_t = find_boundary(0, -1, -1, 1, N, mnc, mxc);
        int rod0_l = find_boundary(1, rod0_t, -1, 1, N, mnc, mxc);
        int rod0_b = rod0_t; //find_vreach(rod0_t, rod0_l);
        int rod0_r = find_hreach(rod0_t, rod0_l, false);
        //cerr << "tlbr 0: " << rod0_t << ' ' << rod0_l << ' ' << rod0_b << ' ' << rod0_r << endl;

        assert(rod0_t == rod0_b);
        assert(rod1_l == rod1_r);
        if (rod0_l <= rod1_l && rod1_r <= rod0_r && rod1_t - 1 == rod0_t) --rod1_t;
        if (rod0_l <= rod1_l && rod1_r <= rod0_r && rod1_b + 1 == rod0_b) ++rod1_b;
        if (rod1_t <= rod0_t && rod0_b <= rod1_b && rod0_l - 1 == rod1_l) --rod0_l;
        if (rod1_t <= rod0_t && rod0_b <= rod1_b && rod0_r + 1 == rod1_r) ++rod0_r;

        if (rod0_l - 1 == rod1_l && query(rod0_t, rod0_l - 1, rod0_t, rod0_l - 1)) --rod0_l;
        if (rod0_r + 1 == rod1_r && query(rod0_t, rod0_r + 1, rod0_t, rod0_r + 1)) ++rod0_r;

        return array<int, 8>({rod0_t, rod0_l, rod0_b, rod0_r, rod1_t, rod1_l, rod1_b, rod1_r});
    }
}

string to_string(const array<int, 8>& arr) {
    return "[" + to_string(arr[0]) + ", " + to_string(arr[1]) + ", " + to_string(arr[2]) + ", " + to_string(arr[3]) + ", " + to_string(arr[4]) + ", " + to_string(arr[5]) + ", " + to_string(arr[6]) + ", " + to_string(arr[7]) + "]";
}

mt19937 rng(8);
void run_test() {
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

void test() {
    DEBUG = true;
    for (N=5; N<=TEST_N; ++N) {
        cerr << "N = " << N << endl;
        for (int t=0; t<10000; ++t) run_test();
    }
    N = MN;
    for (int t=0; t<50; ++t) {
        cerr << "N = " << N << ", t = " << t << endl;
        run_test();
        cerr << "Q = " << query_ct << endl;
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    //test(); return 0;

    cin >> N;
    array<int, 8> ans = solve();
    cout << '!';
    for (int x: ans) cout << ' ' << x;
    cout << '\n';
}

/*
..xxx
..x..
..x..
..x..
.....

..x..
..x..
..x..
.....
..xxx
*/
