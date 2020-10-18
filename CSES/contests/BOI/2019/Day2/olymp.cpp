#include <bits/stdc++.h>

using namespace std;

#define FI first
#define SE second

typedef long long ll;
typedef pair<int,ll> pil;

const int MN = 501;
const int SHF = 9;

int N, K, C;
int score[MN][6];

set<ll> visited;

int cur[6], cur_sum;
ll cur_num;

int best[6];
inline void update() {
    for (int i=0; i<K; ++i) {
        best[i] = -1;
    }
    
    cur_num = 0;
    for (int i=0; i<K; ++i) {
        cur_num <<= SHF;
        cur_num += cur[i];
    }

    for (int i=0; i<K; ++i) {
        for (int j=0; j<K; ++j) {
            best[j] = max(best[j], score[cur[i]][j]);
        }
    }
    cur_sum = 0;
    for (int i=0; i<K; ++i) cur_sum += best[i];
}

inline void set_cur(ll num) {
    for (int i=K-1; i>=0; --i) {
        cur[i] = num & ((1 << SHF) - 1);
        num >>= SHF;
    }
    sort(cur, cur+K, greater<int>());
    update();
}

int reorder(int idx) {
    while (idx > 0 && cur[idx] > cur[idx-1]) {
        swap(cur[idx], cur[idx-1]);
        --idx;
    }
    while (idx+1 < K && cur[idx] < cur[idx+1]) {
        swap(cur[idx], cur[idx+1]);
        ++idx;
    }
    return idx;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> N >> K >> C;

    for (int i=0; i<N; ++i) {
        for (int j=0; j<K; ++j) {
            cin >> score[i][j];
        }
    }

    for (int j=0; j<K; ++j) {
        for (int i=0; i<N; ++i) {
            bool ok = true;
            for (int k=0; k<j; ++k) {
                if (cur[k] == i) {
                    ok = false;
                    break;
                }
            }
            if (!ok) continue;

            if (best[j] < score[i][j]) {
                best[j] = score[i][j];
                cur[j] = i;
            }
        }
    }

    sort(cur, cur+K, greater<int>());
    update();

    //cerr << "K: " << K << endl;
    //set<pil, greater<pil>> pq;
    priority_queue<pil> pq;
    //pq.insert(pil(cur_sum, cur_num));
    pq.emplace(cur_sum, cur_num);
    //visited.insert(cur_num);
    visited.emplace(cur_num);
    
    while (pq.size() > 0 && C > 0) {
        //pil team = *pq.begin(); pq.erase(pq.begin());
        pil team = pq.top(); pq.pop();
        //cerr << team.FI << ' ' << team.SE << endl;

        set_cur(team.SE);
        //cerr << "cur: "; for (int i=0; i<K; ++i) { cerr << cur[i] << ' '; } cerr << endl;

        if (--C == 0) {
            cout << team.FI << endl;
            return 0;
        }

        for (int i=0; i<N; ++i) {
            bool ok = true;
            for (int j=0; j<K; ++j) {
                if (cur[j] == i) {
                    ok = false;
                    break;
                }
            }
            if (!ok) continue;
            for (int j=0; j<K; ++j) {
                int original = cur[j];

                cur[j] = i;
                int idx = reorder(j);
                //cerr << "nxt: "; for (int i=0; i<K; ++i) { cerr << cur[i] << ' '; } cerr << endl;
                //cerr << "in? " << visited.count(get_num()) << endl;
                update();
                if (visited.emplace(cur_num).SE == true) {
                    //pq.insert(pil(cur_sum, cur_num));
                    pq.emplace(cur_sum, cur_num);
                }
                cur[idx] = original;
                //assert(j == reorder(idx));
                reorder(idx);
            }
        }

        //while (pq.size() > C) {
        //    auto it = pq.end(); --it;
        //    pq.erase(it);
        //}
    }

    assert(false);
}
/*
5 4 4
7 0 4 9
3 0 8 4
1 1 3 7
5 1 3 4
4 2 2 9
*/
