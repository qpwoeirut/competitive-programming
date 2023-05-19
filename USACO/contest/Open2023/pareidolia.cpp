#include <bits/stdc++.h>

using namespace std;
using ll=long long;
using pii=pair<int,int>;
using pcii=pair<const int, int>;

const int MN = 200005;

const string bessie = "bessie";

string S;
int N;
int U;
int pos[MN];
char change[MN];

ll brute_ans[MN];
ll brute_count(const string& s) {
    ll ct = 0;
    for (int i=0; i<N; ++i) {
        int b_idx = 0;
        int cur = 0;
        for (int j=i; j<N; ++j) {  // string s[i..j] inclusive
            if (s[j] == bessie[b_idx]) ++b_idx;
            if (b_idx == bessie.size()) {
                b_idx = 0;
                ++cur;
            }
            ct += cur;
        }
    }
    return ct;
}
void brute() {
    string T = S;
    for (int i=0; i<U; ++i) {
        brute_ans[i] = brute_count(T);
        T[pos[i]] = change[i];
    }
    brute_ans[U] = brute_count(T);
}

int next_b[MN], next_e[MN], next_s[MN], next_i[MN];
int find_block(int i) {
    i = next_e[i];
    i = next_s[i];
    i = next_s[i];
    i = next_i[i];
    i = next_e[i];
    return i;
}

map<int,int> block_s;
multimap<int,int,greater<int>> block_e;
map<int,int> direct_before, direct_after, before, after;
ll ans[MN];
ll solve_count(const string& s) {
    block_s.clear();
    block_e.clear();
    direct_before.clear();
    direct_after.clear();
    before.clear();
    after.clear();

    int cur_b = N, cur_e = N, cur_s = N, cur_i = N;
    next_b[N] = next_e[N] = next_s[N] = next_i[N] = N;  // TODO min segtree?
    for (int i=N-1; i>=0; --i) {
        next_b[i] = cur_b;
        next_e[i] = cur_e;
        next_s[i] = cur_s;
        next_i[i] = cur_i;
        switch (s[i]) {
            case 'b': cur_b = i; break;
            case 'e': cur_e = i; break;
            case 's': cur_s = i; break;
            case 'i': cur_i = i; break;
        }
    }

    for (int i=0; i<N; ++i) {
        if (s[i] == 'b') {
            const int ending = find_block(i);
            if (ending != N) {
                block_s.emplace(i, ending);
                block_e.emplace(ending, i);
            }
        }
    }

    ll ct = 0;
    pii last(-1, -1);
    for (const pcii& p: block_s) {
        direct_before[p.first] = p.first - last.first;
        last = p;
    }
    last = pii(N, N);
    for (const pcii& p: block_e) {
        direct_after[p.second] = max(1, last.first - p.first);
        last = p;
    }

    for (const pcii& p: block_e) {
        auto it = block_s.lower_bound(p.first);
        after[p.second] = direct_after[p.second] + (it != block_s.end() ? after[it->first] : 0);
    }
    for (const pcii& p: block_s) {
        before[p.first] = direct_before[p.first];
        for (auto it = block_e.lower_bound(p.first); it != block_e.end() && block_s.upper_bound(it->second)->first == p.first; ++it) {
            before[p.first] += before[it->second];
        }
    }

    for (const pcii& p: block_s) {
        //cerr << s << " (" << p.first << "," << p.second << ") " << direct_before[p.first] << ' ' << direct_after[p.first] << ' ' << before[p.first] << ' ' << after[p.first] << endl;
        ct += before[p.first] * after[p.first];
    }
    //for (const pcii& p: block_e) {
    //    cerr << s << " (" << p.first << "," << p.second << ") " << direct_before[p.first] << ' ' << direct_after[p.first] << ' ' << before[p.first] << ' ' << after[p.first] << endl;
    //}

    return ct;
}

void solve() {
    string T = S;
    for (int i=0; i<U; ++i) {
        ans[i] = solve_count(T);
        T[pos[i]] = change[i];
    }
    ans[U] = solve_count(T);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> S;
    N = S.size();
    cin >> U;
    for (int i=0; i<U; ++i) {
        cin >> pos[i] >> change[i];
        --pos[i];
    }

    brute(); for (int i=0; i<=U; ++i) cout << brute_ans[i] << '\n';
    //solve(); for (int i=0; i<=U; ++i) cout << ans[i] << '\n';
}
