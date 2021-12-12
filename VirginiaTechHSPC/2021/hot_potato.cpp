#include <bits/stdc++.h>

using namespace std;

const int MN = 1001001;

int N, K;
string name[MN];
int A[MN];

int BIT[MN];
void upd(int idx, int val) {
    for (++idx; idx<MN; idx+=(idx&-idx)) BIT[idx] += val;
}
int query(int idx) {
    int ret = 0;
    for (++idx; idx>0; idx-=(idx&-idx)) ret += BIT[idx];
    return ret;
}

bool out[MN];

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> N >> K;
    for (int i=0; i<N; ++i) {
        cin >> name[i];
        upd(i, 1);
        out[i] = false;
    }
    for (int i=0; i<K; ++i) {
        cin >> A[i];
    }

    int j = 0;
    int offset = 0;
    for (int i=N; i>1; --i) {
        const int x = (A[j] + offset) - i * ((A[j] + offset) / i);
        int L = 0, R = N;
        while (L < R) {
            int mid = (L + R) >> 1;
            if (query(mid) <= x) {
                L = mid + 1;
            } else {
                R = mid;
            }
        }
        //cerr << i << ' ' << x << ' ' << L << endl;

        assert(L < N);
        assert(!out[L]);
        upd(L, -1);
        out[L] = true;

        offset = u;

        if (++j == K) j = 0;
    }

    for (int i=0; i<N; ++i) {
        if (!out[i]) {
            cout << name[i] << '\n';
        }
    }
}
