#include <bits/stdc++.h>

using namespace std;

using ll=long long;

const int MN = 1000006;
const ll MX = 1e12 + 1;
const int MOD = 1e9 + 7;

struct Block {
    ll rate;
    ll len;
    ll start;

    Block(const ll _rate, const ll _len, const ll _start) : rate(_rate), len(_len), start(_start) {}
    const operator<(const Block& o) const {
        return start + len < o.start + o.len || (start + len == o.start + len && (start < o.start || (start == o.start && rate < o.rate));
    }
};

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int D;
    cin >> D;

    vector<Block> tests;
    tests.emplace_back(MX, 0, 0);
    tests.emplace_back(0, MN, 0);
    ll cost = 0;

    for (int i=0; i<D; ++i) {
        ll m_i, b_i;
        cin >> m_i >> b_i;

        //int b = lower_bound(tests.begin(), tests.end(), Block(-1, m_i, 0)) - tests.begin();

        int b = 0;
        ll total = 0;
        for (; b < tests.size(); ++b) {
            if (tests[b].start + tests[b].len >= m_i) {
                const ll len = m_i - tests[b].start;
                total += tests[b].rate * len;

                ll diff = b_i - total;
                if (diff <= 0) break;

                ll merge_diff = (tests[b - 1].rate - tests[b].rate) * len;
                if (merge_diff > diff) {
                    
                } else {

                }
            } else {
                total += tests[b].rate * tests[b].len;
            }
        }
    }
}
