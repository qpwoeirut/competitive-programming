//guess_which_cow.cpp created at 09/11/23 21:03:40

#include <bits/stdc++.h>

using namespace std;
using ll=long long;

const int MN = 50;
const int MP = 8;
const int INF = 1001001001;
const int X = 0b001;
const int Y = 0b010;
const int Z = 0b100;
const string QSTR[8] = { "", "X", "Y", "X Y", "Z", "X Z", "Y Z", "X Y Z" };

int N, P;
int A[MN][MP];

ll update(const int qp, const int qval) {
    ll possible = (1LL << N) - 1;
    for (int i = 0; i < N; ++i) {
        if (possible & (1LL << i) && (A[i][qp] & qval) == 0) {
            possible ^= 1LL << i;
        }
    }
    return possible;
}

map<ll, int> cache;
int cost(const ll possible, int& qp, int& qval) {
    if (__builtin_popcountll(possible) <= 1) return 0;
    if (qp != INF && cache.count(possible)) return cache[possible];
    qp = qval = -1;

    int best = INF;
    int _ = 0;
    for (int i = 0; i < P; ++i) {
        for (int qv = 1; qv < 7; ++qv) {
            const ll possible_if_true = possible & update(i, qv);
            const ll possible_if_false = possible & update(i, qv ^ 0b111);
            if (possible_if_true == possible || possible_if_false == possible) continue;

            const int cost_if_true = cost(possible_if_true, _, _) + 1;
            const int cost_if_false = cost(possible_if_false, _, _) + 1;

            if (best > max(cost_if_true, cost_if_false)) {
                best = max(cost_if_true, cost_if_false);
                qp = i;
                qval = qv;
            }
        }
    }
    
    cache[possible] = best;
    return best;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> N >> P;
    for (int i=0; i<N; ++i) {
        for (int j=0; j<P; ++j) {
            char ch;
            cin >> ch;
            A[i][j] = ch == 'X' ? X : (ch == 'Y' ? Y : Z);
        }
    }

    ll possible = (1LL << N) - 1;
    while (__builtin_popcountll(possible) > 1) {
        int qp = INF, qval = INF;
        cost(possible, qp, qval);

        cout << "Q " << qp + 1 << ' ' << QSTR[qval] << '\n';
        cout.flush();

        int resp;
        cin >> resp;
        possible &= update(qp, resp ? qval : qval ^ 0b111);
    }

    for (int i = 0; i < N; ++i) {
        if (possible & (1LL << i)) {
            cout << "C " << i + 1 << '\n';
        }
    }
    cout.flush();
}

