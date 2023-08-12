#define USING_TESTER

#include <bits/stdc++.h>
#include "7.cpp"
#include "jngen.h"
#include "qpwoeirut/debug.h"

using namespace std;
using ll=long long;
using pii=pair<int,int>;

const bool DEBUG = false;

mt19937 rng(8);
ll rndv(ll l, ll r) {
    return uniform_int_distribution<ll>(l, r)(rng);
}

namespace Tester {
    int alice, bob;
    ll penalty;

    const int MAXN = 105, MAXK = 5;
    const int TOTAL = 100, INF = 1e9 + 7;
    const int TELEPORT_INCREMENT = 5;
    int TELEPORT_PROBABILITY = 40;

    int n, m;
    int adj[MAXN][MAXN];
    ll dist[MAXN][MAXN];
    int deg[MAXN];
        
    bool teleport_pending = false;
    int TIME = 0;

    void init(int _n, int _m, const vector<pii>& edges) {
        n = _n, m = _m;

        alice = 0;
        bob = n-1;
        penalty = 0;
        TELEPORT_PROBABILITY = 40;

        teleport_pending = false;
        TIME = 0;

        for (int i = 0; i < MAXN; i++) {
            for (int j = 0; j < MAXN; j++) {
                adj[i][j] = 0;
                dist[i][j] = INF;
            }
            dist[i][i] = 0;
            deg[i] = 0;
        }
        for (const pii& edge: edges) {
            const int l = edge.first, r = edge.second;
            adj[l][r] = adj[r][l] = 1;
            dist[l][r] = dist[r][l] = 1;
            deg[l]++, deg[r]++;
        }
        
        for (int k = 0; k < n; k++) {
            for (int i = 0; i < n; i++) {
                for (int j = i + 1; j < n; j++) {
                    if (dist[i][k] + dist[k][j] < dist[i][j]) {
                        dist[i][j] = dist[j][i] = dist[i][k] + dist[k][j];
                    }
                }
            }
        }
    }

    ll get_points (ll end_time, ll penalty, ll n) {
        return (1ll * n * n * n * (TOTAL + 1 - end_time) * (ll)sqrtl(TOTAL + 1 - end_time) - penalty * n * (ll)sqrtl(n))/(1ll * 50 * n * n * n);
    }

    ll block_penalty (ll v, ll t) {
        return (100 - t + 1) * v * v * v * v;
    }

    ll move_penalty (ll t, ll d) {
        ll fd = max(0ll, d - 1);
        return (100 - t + 1) * (ll)sqrtl(100 - t + 1) * fd * fd * fd * fd * fd * fd * fd;
    }

    int interact(int k, const vector<int>& blocks, int move) {
        assert(0 <= k && k <= n+1);
        assert(0 <= move && move < n);
        assert(k == blocks.size() || k == n+1);
        for (int x: blocks) assert(0 <= x && x < n);

        ++TIME;
        assert(TIME <= 100);

        set<int> blocked(blocks.begin(), blocks.end());

        penalty += block_penalty(k != n + 1 ? k : deg[alice] + 1, TIME);
        bool tel = (teleport_pending || rndv(1, 100) <= TELEPORT_PROBABILITY);
        
        if (k == n + 1) {
            TELEPORT_PROBABILITY += TELEPORT_INCREMENT;
        }
        if (tel && k == n + 1) {
            tel = false;
            teleport_pending = true;
        } else {
            teleport_pending = false;
        }
        
        vector<pii> pos;
        for (int i = 0; i < n; i++) {
            if ((tel || adj[bob][i]) && !blocked.count(i)) {
                pos.emplace_back(dist[alice][i], i);
            }
        }
        
        sort(pos.rbegin(), pos.rend());
        
        int nxt = pos.empty() ? bob : pos[rndv(0, min((int)pos.size() - 1, MAXK))].second;
        
        penalty += move_penalty(TIME, dist[alice][move]);

        alice = move;
        bob = nxt;

        if (DEBUG) debug(k, blocks, move, pos, bob, penalty);

        return bob;
    }

    int run_test(int _n, int _m) {
        Arrayp edge_arr = Graph::random(_n, _m).connected().g().edges();
        vector<pii> edges(edge_arr.begin(), edge_arr.end());

        if (DEBUG) {
            for (auto edge: edges) cerr << edge.first << ' ' << edge.second << endl;
        }

        init(_n, _m, edges);
        Solution::solve(n, m, edges, interact);

        int score = TIME == TOTAL ? 0 : get_points(TIME, penalty, n);
        //debug(_n, _m, score);
        return score;
    }
};

void print_test() {
    for (int t=0; t<50; ++t) {
        int n = rndv(3, 100);
        int sp = min(n * (n - 1)/2, max(n - 1, n * n/10));
        int m = rndv(n - 1, sp);
        int score = Tester::run_test(n, m);
        cout << n << ' ' << m << ' ' << score << ' ' << Tester::TIME << ' ' << Tester::penalty << endl;
    }
    for (int t=0; t<50; ++t) {
        int n = rndv(2, 100);
        int sp = min(n * (n - 1)/2 - 1, max(n - 1, n * n/10));
        int m = rndv(sp + 1, n * (n - 1) / 2);
        int score = Tester::run_test(n, m);
        cout << n << ' ' << m << ' ' << score << ' ' << Tester::TIME << ' ' << Tester::penalty << endl;
    }
}

void big_test() {
    int n = 100;
    int m = n * (n - 1) / 2 - rndv(0, 10);
    int score = Tester::run_test(n, m);
    cout << n << ' ' << m << ' ' << score << ' ' << Tester::TIME << ' ' << Tester::penalty << endl;
}


const int TESTS = 2000;
array<double, 8> stats_of(const array<double, TESTS>& scores) {
    double sum = 0;
    for (double x: scores) {
        sum += x;
    }
    double mean = sum / scores.size();

    double variance = 0;
    for (double x: scores) {
        variance += (x - mean) * (x - mean);
    }
    double stddev = sqrt(variance / scores.size());
    double stderror = sqrt(variance) / scores.size();

    array<double, TESTS> tmp(scores);
    sort(tmp.begin(), tmp.end());
    // quartiles are approximate, should be good enough
    return {mean, stddev, stderror, *min_element(scores.begin(), scores.end()), tmp[TESTS / 4], tmp[TESTS / 2], tmp[3 * TESTS / 4], *max_element(scores.begin(), scores.end())};
}

string to_string(const array<double, 8>& arr) {
    string s = to_string(arr[0]);
    for (int i = 1; i < (int)arr.size(); ++i) s += ", " + to_string(arr[i]);
    return s;
}

array<double, TESTS> scores, nneg_scores, times, nneg_times, penalties;

const int PROGRESS = TESTS / 10;
void stats(int min_n, int max_n, bool sparse) {
    for (int t=0; t<TESTS; ++t) {
        int n = rndv(max(min_n, sparse ? 2 : 3), max_n);
        int sp = min(n * (n - 1)/2, max(n - 1, n * n/10));
        int m = sparse ? rndv(n - 1, sp) : rndv(sp + 1, n * (n - 1) / 2);

        debug(n, m);
        int score = Tester::run_test(n, m);
        scores[t] = score;
        nneg_scores[t] = max(0, score);
        times[t] = Tester::TIME;
        nneg_times[t] = scores[t] <= 0 ? 0 : times[t];
        penalties[t] = Tester::penalty;

        if ((t + 1) % PROGRESS == 0) {
            cout << t+1 << endl;
        }
    }

    cout << "TESTS = " + to_string(TESTS) + ". n = [" + to_string(min_n) + "," + to_string(max_n) + "]. sparse = " + to_string(sparse) << endl;
    cout << "scores    mean, stddev, stderr, min, q1, med, q3, max: " << to_string(stats_of(scores)) << endl;
    cout << "nn scores mean, stddev, stderr, min, q1, med, q3, max: " << to_string(stats_of(nneg_scores)) << endl;
    cout << "times     mean, stddev, stderr, min, q1, med, q3, max: " << to_string(stats_of(times)) << endl;
    cout << "nn times  mean, stddev, stderr, min, q1, med, q3, max: " << to_string(stats_of(nneg_times)) << endl;
    cout << "penalties mean, stddev, stderr, min, q1, med, q3, max: " << to_string(stats_of(penalties)) << endl;
}

void generate_graph(int n, int m) {
    Arrayp edge_arr = Graph::random(n, m).connected().g().edges();
    vector<pii> edges(edge_arr.begin(), edge_arr.end());
    ofstream fout("graph_" + to_string(n) + "-" + to_string(m) + ".txt");
    fout << n << ' ' << m << endl;
    for (auto edge: edges) fout << edge.first + 1 << ' ' << edge.second + 1 << endl;
    for (int t=0; t<100; ++t) fout << "1\n";
}

int main() {
    //for (int n=40; n<=100; n+=10) for (int mt=1; mt<=5; ++mt) generate_graph(n, n*mt);
    //stats(2, 10, false); stats(2, 10, true);
    stats(11, 100, false); stats(11, 100, true);
    //print_test();
    //for (int i=0; i<5; ++i) big_test();
}
