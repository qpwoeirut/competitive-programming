#include <bits/stdc++.h>

using namespace std;

using pii=pair<int,int>;

const int STRICT = 20;
const int EXTRA_PENALTY = 100;
const int GAP_PENALTY = 100;

const int INIT = 1001001001;
const int W = 1000;

struct Stack {
    int width, height;
    vector<int> ids;

    Stack(int _width, int _height, const vector<int>& _ids) {
        width = _width;
        height = _height;
        ids = _ids;
    }
};

int A[50][50];
int ans[50][50][4];

int kn[W+1];
int val[W+1];
int knapsack(const int n, const int day, const bitset<50>& done, const int width, int& best_sum) {
    fill(kn, kn+W+1, -INIT);
    kn[0] = 0;
    for (int x=W; x>=0; --x) {
        if (kn[x] == -INIT) continue;
        for (int i=0; i<n; ++i) {
            if (done[i]) continue;
            const int h = (A[day][i] + width - 1) / width;
            const int extra = width * h - A[day][i];
            if (x + h <= W && kn[x + h] < kn[x] + width * h + extra * EXTRA_PENALTY) {
                kn[x + h] = kn[x] + width * h + extra * EXTRA_PENALTY;
                val[x + h] = i;
            }
        }
    }

    best_sum = 0;
    int best_score = -INIT;
    for (int x=W; x>=0; --x) {
        if (best_score < kn[x] - (W - x) * width * GAP_PENALTY) {
            best_score = kn[x] - (W - x) * width * GAP_PENALTY;
            best_sum = x;
        }
    }
    return best_score + width;
}

void recover_knapsack(const int day, const int width, int x, vector<int>& vals) {
    vals.clear();
    while (x > 0) {
        vals.push_back(val[x]);
        const int h = (A[day][val[x]] + width - 1) / width;
        x -= h;
    }
}

void solve(int d, int n) {
    for (int day=0; day<d; ++day) {
        bitset<50> done;
        int cur_w = 0;

        vector<Stack> stacks;
        while ((int)done.count() < n) {
            //cerr << day << ' ' << done.to_string() << ' ' << cur_w << endl;
            int best_score = -INIT;
            int best_width = 0;
            vector<int> best;
            for (int width=1; cur_w+width<W; ++width) {
                int best_sum;
                const int score = knapsack(n, day, done, width, best_sum);
                if (best_score < score) {
                    best_score = score;
                    best_width = width;
                    recover_knapsack(day, width, best_sum, best);
                    //cerr << score << ' ' << width << ' ' << best_sum << ' ' << best.size() << ' ' << (best.empty() ? -1 : best[0]) << endl;
                }
            }

            if (best.empty()) {
                best_width = W - cur_w;
                for (int i=0; i<n; ++i) {
                    if (!done[i]) best.push_back(i);
                }
            }

            int cur_h = 0;
            for (const int i: best) {
                const int height = (A[day][i] + best_width - 1) / best_width;
                cur_h += height;
                done[i] = true;
            }
            stacks.emplace_back(best_width, cur_h, best);
            cur_w += best_width;
        }

        cur_w = 0;
        for (const Stack& stack: stacks) {
            int cur_h = 0;
            for (int i = 0; i<stack.ids.size(); ++i) {
                ans[day][stack.ids[i]][0] = cur_h;
                ans[day][stack.ids[i]][1] = cur_w;

                if (i + 1 == stack.ids.size()) {
                    ans[day][stack.ids[i]][2] = W;
                } else {
                    int height = (A[day][i] + stack.width - 1) / stack.width;
                    if (stack.height > W) {
                        height = min(height, W / (int)stack.ids.size());
                    }
                    ans[day][stack.ids[i]][2] = cur_h + height;
                    cur_h += height;
                }

                ans[day][stack.ids[i]][3] = cur_w + stack.width;
            }
            cur_w += stack.width;
        }
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int _W, D, N;
    cin >> _W >> D >> N;
    assert(W == _W);

    for (int day=0; day<D; ++day) {
        for (int i=0; i<N; ++i) {
            cin >> A[day][i];
        }
    }

    solve(D, N);

    for (int day=0; day<D; ++day) {
        for (int i=0; i<N; ++i) {
            for (int j=0; j<4; ++j) {
                cout << ans[day][i][j] << (j < 3 ? ' ' : '\n');
            }
        }
    }
}

/*
Find better fallback method
Maintain same stack widths across days
Drop a few units to make widths fit, if necessary; take into account the theoretical extra space
Shuffle previous days' widths to make them align
*/
