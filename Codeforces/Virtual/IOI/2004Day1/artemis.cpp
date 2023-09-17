//artemis.cpp created at 09/15/23 14:07:08

#include <bits/stdc++.h>

using namespace std;
using pii=pair<int,int>;

const int MN = 20000;

struct Tree {
    int x, y;
    int idx;
};

int N, T;
Tree A[MN];
bitset<MN> y_used;

int solve(pii& ans) {
    if (T == 2) {
        ans.first = A[0].idx;
        ans.second = A[1].idx;
        return 2;
    }

    int best = N + 1;
    for (int i=0; i<N; ++i) {
        y_used.reset();
        y_used[A[i].y] = true;

        int y_lo = -1, y_hi = N;
        int y_min = 0, y_max = N - 1;
        int above = 0, below = 0;
        for (int j=i+1; j<N; ++j) {
            y_used[A[j].y] = true;
            if (A[i].y < A[j].y) {
                if (++above + 2 >= T) {
                    if (A[j].y <= y_hi) {
                        for (--y_hi; !y_used[y_hi]; --y_hi);
                    } else if (A[j].y <= y_max) {
                        for (; y_max > A[j].y; --y_max) above -= y_used[y_max];
                        if (best > above + 1) {
                            best = above + 1;
                            ans.first = A[i].idx;
                            ans.second = A[j].idx;
                        }
                    } else --above;
                }
            } else {
                if (++below + 2 >= T) {
                    if (y_lo <= A[j].y) {
                        for (++y_lo; !y_used[y_lo]; ++y_lo);
                    } else if (y_min <= A[j].y) {
                        for (; y_min < A[j].y; ++y_min) below -= y_used[y_min];
                        if (best > below + 1) {
                            best = below + 1;
                            ans.first = A[i].idx;
                            ans.second = A[j].idx;
                        }
                    } else --below;
                }
            }
        }
    }
    return best;
}

int BIT[MN + 1];
void inc(int idx) {
    for (++idx; idx<=N; idx+=(idx&-idx)) ++BIT[idx];
}
int query(int idx) {
    int ret = 0;
    for (++idx; idx>0; idx-=(idx&-idx)) ret += BIT[idx];
    return ret;
}
int slow_solve(pii& ans) {
    int best = N + 1;
    for (int i=0; i<N; ++i) {
        fill(BIT, BIT+N+1, 0);
        inc(A[i].y);
 
        int min_y = 0;
        int max_y = N;
        int cur_best = N + 1;
        for (int j=i+1; j<N; ++j) {
            if (A[i].y < A[j].y) {
                if (A[j].y <= max_y) {
                    inc(A[j].y);
                    if (j - i + 1 >= T) {
                        const int cuts = query(A[j].y) - query(A[i].y - 1);
                        if (T <= cuts && cuts < cur_best) {
                            cur_best = cuts;
                            max_y = A[j].y;
                            if (best > cuts) {
                                best = cuts;
                                ans.first = A[i].idx;
                                ans.second = A[j].idx;
                            }
                        }
                    }
                }
            } else {
                if (min_y <= A[j].y) {
                    inc(A[j].y);
                    if (j - i + 1 >= T) {
                        const int cuts = query(A[i].y) - query(A[j].y - 1);
                        if (T <= cuts && cuts < cur_best) {
                            cur_best = cuts;
                            min_y = A[j].y;
                            if (best > cuts) {
                                best = cuts;
                                ans.first = A[i].idx;
                                ans.second = A[j].idx;
                            }
                        }
                    }
                }
            }
        }
    }
    return best;
}

int perm[MN];
void test() {
    mt19937 rng(8);
    for (N = 1; N <= 50; ++N) {
        for (T = 2; T <= N; ++T) {
            cerr << N << ' ' << T << endl;
            for (int t=0; t<10000; ++t) {
                for (int i=0; i<N; ++i) A[i].idx = perm[i] = i;
                shuffle(perm, perm+N, rng);
                for (int i=0; i<N; ++i) A[i].x = perm[i];
                shuffle(perm, perm+N, rng);
                for (int i=0; i<N; ++i) A[i].y = perm[i];
                
                sort(A, A+N, [](const Tree& a, const Tree& b) {
                    return a.x < b.x || (a.x == b.x && a.y < b.y);
                });

                pii p;
                int ssans = slow_solve(p);
                int sans = solve(p);
                if (sans != ssans) {
                    cout << "!!!!!!!!!!!\n";
                    cout << N << ' ' << T << '\n';
                    for (int i=0; i<N; ++i) {
                        cout << A[i].idx << ' ' << A[i].x << ' ' << A[i].y << '\n';
                    }
                    cout << sans << ' ' << ssans << endl;
                }
                assert(sans == ssans);
            }
        }
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    //test(); return 0;

    cin >> N >> T;
    for (int i=0; i<N; ++i) {
        cin >> A[i].x >> A[i].y;
        A[i].idx = i;
    }
    sort(A, A+N, [](const Tree& a, const Tree& b) {
        return a.y < b.y || (a.y == b.y && a.x < b.x);
    });
    for (int i=0; i<N; ++i) A[i].y = i;

    sort(A, A+N, [](const Tree& a, const Tree& b) {
        return a.x < b.x || (a.x == b.x && a.y < b.y);
    });

    pii ans(-1, -1);
    solve(ans);
    cout << ans.first + 1 << ' ' << ans.second + 1 << '\n';
}
