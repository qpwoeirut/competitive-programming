#include <bits/stdc++.h>

using namespace std;

const int MN = 100005;
const int LG = 24;
const int INIT = 1001001001;

int N;
string A[MN];

int empty_cost[MN];

int total[MN];
int cur[MN];
int tmp[LG][MN];

//string dbg_stk;

struct Trie {
    Trie *zero;
    Trie *one;
    
    int depth;
    int ct;

    Trie() {
        zero = nullptr;
        one = nullptr;
        depth = 0;
        ct = 0;
    }

    void add(const string& s, int i) {
        if (i < s.size()) {
            if (zero == nullptr) zero = new Trie();
            if (one == nullptr) one = new Trie();

            if (s[i] == '0') {
                zero->add(s, i + 1);
            } else {
                one->add(s, i + 1);
            }
            depth = max(zero->depth, one->depth) + 1;
        } else {
            ++ct;
            depth = depth == 0 ? 1 : depth;
        }
    }

    void cost(int ret[], int ti, int mx) {
        if (zero == nullptr && one == nullptr) {
            for (int i=0; i<=mx; ++i) {
                ret[i] = empty_cost[i + ct];
            }
            //cerr << "--------------\n";
            //cerr << dbg_stk << ' ' << ct << endl;
            //for (int i=0; i<=mx; ++i) {
            //    cerr << ret[i] << ' ';
            //} cerr << endl;
            return;
        }
        if (zero == nullptr) zero = new Trie();
        if (one == nullptr) one = new Trie();

        Trie *heavy = zero->depth >= one->depth ? zero : one;
        Trie *light = zero->depth >= one->depth ? one : zero;

        //dbg_stk += '0' ^ (zero->depth < one->depth);
        heavy->cost(ret, ti, mx + ct);
        //dbg_stk.pop_back();
        //dbg_stk += '1' ^ (zero->depth < one->depth);
        light->cost(tmp[ti], ti + 1, mx + ct);
        //dbg_stk.pop_back();

        for (int x=0; x<=mx; ++x) {
            cur[x] = INIT;
            for (int i=0; i<=x + ct; ++i) {
                cur[x] = min(cur[x], ret[i] + tmp[ti][x + ct - i] + x + ct);
            }
        }

        //cerr << "--------------\n";
        //cerr << dbg_stk << ' ' << ct << endl;
        //for (int i=0; i<=mx; ++i) {
        //    cerr << cur[i] << ' ';
        //} cerr << endl;
        //for (int i=0; i<=mx + ct; ++i) {
        //    cerr << ret[i] << ' ';
        //} cerr << endl;
        //for (int i=0; i<=mx + ct; ++i) {
        //    cerr << tmp[ti][i] << ' ';
        //} cerr << endl;

        copy(cur, cur + mx + 1, ret);
    }
};

int main() {
    cin.tie(0)->sync_with_stdio(0);
    
    empty_cost[0] = 0;
    for (int i=1; i<MN; ++i) {
        int lg = 0;
        int x = i;
        while (x > 1) {
            x >>= 1;
            ++lg;
        }
        empty_cost[i] = i * (lg + 2) - (1 << (lg + 1));
    }

    Trie *root = new Trie();
    cin >> N;
    for (int i=0; i<N; ++i) {
        cin >> A[i];
        root->add(A[i], 0);
    }

    root->cost(total, 0, 0);
    cout << total[0] << '\n';
}
