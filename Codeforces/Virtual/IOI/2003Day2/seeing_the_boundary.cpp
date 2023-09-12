//seeing_the_boundary.cpp created at 09/11/23 21:41:13

#include <bits/stdc++.h>

using namespace std;
using pii=pair<int,int>;
using dbl=long double;
using pt=complex<dbl>;
using fpt=complex<dbl>;
#define x real()
#define y imag()

const int MN = 500000 + 3;
const int MR = 30000;
const dbl EPS = 1e-8;

int N, R;
pt farmer;
vector<pt> A[MR];

pii covered(pt a, pt b) {  // [a, b)
    if (farmer.y <= a.y && farmer.y <= b.y) return pii(N, N);
    if (farmer.y <= a.y) swap(a, b);

    dbl ax_proj = farmer.x + (farmer.y * (a.x - farmer.x) / (dbl)(farmer.y - a.y));

    pii cover;
    if (farmer.y <= b.y) {
        if (arg(farmer - a) < arg(b - a)) {
            cover.first = 0;
            cover.second = (int)(ceil(ax_proj + EPS) + EPS);
        } else {
            cover.first = (int)(ceil(ax_proj - EPS) + EPS);
            cover.second = N;
        }
        //cerr << a << ' ' << b << ' ' << ax_proj << ' ' << cover.first << ' ' << cover.second << endl;
    } else {
        dbl bx_proj = farmer.x + (farmer.y * (b.x - farmer.x) / (dbl)(farmer.y - b.y));
        if (ax_proj > bx_proj) {
            swap(ax_proj, bx_proj);
        }
        cover.first = (int)(ceil(ax_proj - EPS) + EPS);
        cover.second = (int)(ceil(bx_proj + EPS) + EPS);
        //cerr << a << ' ' << b << ' ' << ax_proj << ' ' << bx_proj << ' ' << cover.first << ' ' << cover.second << endl;
    }

    cover.second = max(0, min(cover.second, N));
    cover.first = max(0, min(cover.first, cover.second));
    return cover;
}

int sum[MN];
int count_bottom() {
    fill(sum, sum+MN, 0);

    for (int i = 0; i < R; ++i) {
        for (int j = 0; j < A[i].size(); ++j) {
            pii cover = covered(A[i][j], A[i][(j + 1) % A[i].size()]);
            ++sum[cover.first];
            --sum[cover.second];
        }
    }

    int ct = 0;
    for (int i = 0; i < N; ++i) {
        sum[i] += i ? sum[i - 1] : 0;
        ct += sum[i] == 0;
    }
    return ct;
}

int solve() {
    int answer = 0;
    for (int rotation = 0; rotation < 4; ++rotation) {
        const int answer_side = count_bottom();
        answer += answer_side;
        //cerr << rotation << ' ' << answer_side << endl;

        farmer = pt(farmer.y, N - farmer.x);
        for (int i = 0; i < R; ++i) {
            for (int j = 0; j < A[i].size(); ++j) {
                A[i][j] = pt(A[i][j].y, N - A[i][j].x);
            }
        }
    }
    return answer;
}

bool segment_blocks(pt a, pt b, const int x_coord) {
    if (farmer.y <= a.y && farmer.y <= b.y) return false;
    if (farmer.y <= a.y) swap(a, b);

    dbl ax_proj = farmer.x + (farmer.y * (a.x - farmer.x) / (dbl)(farmer.y - a.y));

    if (farmer.y <= b.y) {
        assert(arg(farmer - a) > 0);
        assert(arg(b - a) > 0);
        if (arg(farmer - a) < arg(b - a)) {
            return 0 <= x_coord && x_coord <= ax_proj + EPS;
        } else {
            return ax_proj - EPS <= x_coord && x_coord < N;
        }
    } else {
        dbl bx_proj = farmer.x + (farmer.y * (b.x - farmer.x) / (dbl)(farmer.y - b.y));
        if (ax_proj > bx_proj) {
            swap(ax_proj, bx_proj);
        }
        return ax_proj - EPS <= x_coord && x_coord <= bx_proj + EPS;
    }
}
bool visible(const int x_coord) {
    for (int i = 0; i < R; ++i) {
        for (int j = 0; j < A[i].size(); ++j) {
            if (segment_blocks(A[i][j], A[i][(j + 1) % A[i].size()], x_coord)) return false;
        }
    }
    return true;
}
int brute() {
    int answer = 0;
    for (int rotation = 0; rotation < 4; ++rotation) {
        for (int i = 0; i < N; ++i) {
            answer += visible(i);
        }

        farmer = pt(farmer.y, N - farmer.x);
        for (int i = 0; i < R; ++i) {
            for (int j = 0; j < A[i].size(); ++j) {
                A[i][j] = pt(A[i][j].y, N - A[i][j].x);
            }
        }
    }
    return answer;
}

void test() {
    mt19937 rng(8);
    for (N = 10; N <= 100; ++N) {
        for (R = 1; R <= 10; ++R) {
            cerr << N << ' ' << R << endl;
            for (int t = 0; t < 10; ++t) {
                farmer = pt((rng() % (N - 1)) + 1, (rng() % (N - 1)) + 1);
                for (int i = 0; i < R; ++i) {
                    int px, py;
                    do {
                        A[i].clear();
                        px = (rng() % (N - 4)) + 2;
                        py = (rng() % (N - 4)) + 2;
                        A[i].emplace_back(px - 1, py);
                        if (rng() & 1) A[i].emplace_back(px - 1, py - 1);
                        A[i].emplace_back(px, py - 1);
                        if (rng() & 1) A[i].emplace_back(px + 1, py - 1);
                        A[i].emplace_back(px + 1, py);
                        if (rng() & 1) A[i].emplace_back(px + 1, py + 1);
                        A[i].emplace_back(px, py + 1);
                        if (rng() & 1) A[i].emplace_back(px - 1, py + 1);
                    } while ((px == farmer.x && py == farmer.y) || find(A[i].begin(), A[i].end(), farmer) != A[i].end());
                }

                const int sans = solve();
                const int bans = brute();
                if (sans != bans) {
                    cout << sans << ' ' << bans << "\n\n";
                    cout << N << ' ' << R << '\n';
                    cout << farmer.x << ' ' << farmer.y << '\n';
                    for (int i = 0; i < R; ++i) {
                        cout << A[i].size() << '\n';
                        for (const pt& p: A[i]) {
                            cout << p.x << ' ' << p.y << '\n';
                        }
                    }
                    cout << endl;
                }
                assert(sans == bans);
            }
        }
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    //test(); return 0;

    cin >> N >> R;

    int fx, fy;
    cin >> fx >> fy;
    farmer = pt(fx, fy);

    for (int i = 0; i < R; ++i) {
        int points;
        cin >> points;
        A[i] = vector<pt>(points);

        for (int j = 0; j < points; ++j) {
            int px, py;
            cin >> px >> py;
            A[i][j] = pt(px, py);
        }
    }
    
    const int answer = solve();
    cout << answer << '\n';
}

/*
5 1
1 1
3
1 4
4 1
4 4

100 1
1 1
3
1 2
2 1
2 2

100 1
1 1
20
1 2
2 1
2 2
2 3
2 4
2 5
2 6
2 7
2 8
2 9
2 10
2 11
2 12
2 13
2 14
2 15
2 16
2 17
2 18
1 100
*/
