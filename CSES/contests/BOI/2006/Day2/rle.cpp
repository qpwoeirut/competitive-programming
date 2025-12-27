#include <bits/stdc++.h>

using namespace std;
using pii=pair<int, int>;

const int MN = 1 << 21;

pii st[MN * 2];
void build(int sz) {
    for (int i=0; i<MN*2; ++i) st[i] = pii(1e9, 0);
    for (int i=0; i<sz; ++i) st[MN + i] = pii(i ? 3 : 0, i);
    for (int i=MN-1; i>0; --i) {
        st[i] = min(st[2 * i], st[2 * i + 1]);
    }
}

pii query() {
    return st[1];
}

void update(int node, int lo, int hi, int idx, int val) {
    if (idx < lo || hi <= idx) return;
    if (lo + 1 == hi) {
        st[node] = pii(val, idx);
        return;
    }
    int mid = (lo + hi) / 2;
    update(2 * node, lo, mid, idx, val);
    update(2 * node + 1, mid, hi, idx, val);
    st[node] = min(st[2 * node], st[2 * node + 1]);
}

int N, M;
int A[MN];
int B[MN];
int cost[MN];
int mark[MN];

int main() {
    cin >> N;
    cin >> M;
    for (int i=0; i<M; ++i) {
        cin >> A[i];
    }

    vector<pii> raw_blocks;
    int cur_mark = 0;
    for (int i=0; i<M; ++i) {
        if (A[i] == cur_mark) {
            assert(i+2 < M);

            if (A[i+1] == cur_mark) {
                raw_blocks.emplace_back(cur_mark, A[i+2] + 1);
            } else {
                if (A[i+2] == 0) cur_mark = A[i+1];
                else raw_blocks.emplace_back(A[i+1], A[i+2] + 3);
            }
            i += 2;
        } else {
            raw_blocks.emplace_back(A[i], 1);
        }
    }

    vector<pii> blocks;
    for (int i=0; i<raw_blocks.size(); ++i) {
        if (blocks.size() > 0 && blocks.back().first == raw_blocks[i].first) {
            blocks.back().second += raw_blocks[i].second;
        } else {
            blocks.push_back(raw_blocks[i]);
        }
    }

    build(N);
    for (int i=1; i<N; ++i) cost[i] = 3;

    for (int i=0; i<blocks.size(); ++i) {
        int ideal_cost = min(blocks[i].second, 2 + (blocks[i].second + N + 1) / (N + 2));
        int marked_cost = 2 + (blocks[i].second + N - 1) / N;
        //cerr << "i=" << i << " ideal=" << ideal_cost << " marked=" << marked_cost << endl;
        cost[blocks[i].first] += marked_cost - ideal_cost;
        //cerr << "blocks[i]=" << blocks[i].first << ',' << blocks[i].second << " cost=" << cost[blocks[i].first] << endl;

        update(1, 0, MN, blocks[i].first, cost[blocks[i].first]);
        pii other = query();
        //cerr << "other=" << other.first << ',' << other.second << endl;
        if (cost[blocks[i].first] > other.first + 3) {
            cost[blocks[i].first] = other.first + 3;
            update(1, 0, MN, blocks[i].first, cost[blocks[i].first]);
            mark[i] = other.second;
        } else {
            mark[i] = blocks[i].first;
        }
        //cerr << "cost:"; for (int i=0; i<N; ++i) cerr << ' ' << cost[i];
        //cerr << endl;
    }

    vector<pii> mark_changes;
    cur_mark = query().second;
    for (int i = blocks.size() - 1; i >= 0; --i) {
        for (; i >= 0 && blocks[i].first != cur_mark; --i);
        if (i >= 0 && mark[i] != cur_mark) {
            mark_changes.emplace_back(i, cur_mark);
            cur_mark = mark[i];
        }
    }

    //cerr << "cur_mark=" << cur_mark << endl;
    //cerr << "changes:"; for (pii p: mark_changes) cerr << ' ' << p.first << ',' << p.second;
    //cerr << endl;

    vector<int> ans;
    if (cur_mark != 0) {
        ans.push_back(0);
        ans.push_back(cur_mark);
        ans.push_back(0);
    }
    sort(mark_changes.begin(), mark_changes.end());
    int m_i = 0;
    for (int i=0; i<blocks.size(); ++i) {
        if (blocks[i].first == cur_mark) {
            int rem = blocks[i].second;
            while (rem > 0) {
                int x = min(rem, N);
                ans.push_back(cur_mark);
                ans.push_back(cur_mark);
                ans.push_back(x - 1);
                rem -= x;
            }
        } else {
            if (blocks[i].second <= 3) {
                for (int j=0; j<blocks[i].second; ++j) ans.push_back(blocks[i].first);
            } else {
                int rem = blocks[i].second;
                while (rem > 0) {
                    int x = min(rem, N + 2);
                    ans.push_back(cur_mark);
                    ans.push_back(blocks[i].first);
                    ans.push_back(x - 3);
                    rem -= x;
                }
            }
        }
        if (m_i < mark_changes.size() && mark_changes[m_i].first == i) {
            ans.push_back(cur_mark);
            ans.push_back(mark_changes[m_i].second);
            ans.push_back(0);
            cur_mark = mark_changes[m_i].second;
            ++m_i;
        }
    }
    //cerr << "block:";for (pii p: blocks) cerr << ' ' << p.first << ',' << p.second << ' ';
    //cerr << endl;
    //cerr << "mark:";for (int i=0; i<blocks.size(); ++i) cerr << ' ' << mark[i];
    //cerr << endl;

    cout << ans.size() << '\n';
    for (int i=0; i<ans.size(); ++i) {
        if (i) cout << ' ';
        cout << ans[i];
    }
    cout << '\n';
}

