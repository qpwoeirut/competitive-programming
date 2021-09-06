//luna_likes_love.cpp created at 08/29/21 16:38:24

#include <bits/stdc++.h>

using namespace std;

using ll=long long;

const int MN = 1000006;

int N;
int A[MN], B[MN];
int val[MN];
bitset<MN> seen;

ll BIT[MN];
void upd(int idx, int val) {
    for (; idx<MN; idx+=(idx&-idx)) BIT[idx] += val;
}
ll query(int idx) {
    ll ret = 0;
    for (; idx>0; idx-=(idx&-idx)) ret += BIT[idx];
    return ret;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> N;
    for (int i=0; i<N*2; ++i) {
        cin >> A[i];
    }

    int x = 0;
    for (int i=0; i<N*2; ++i) {
        if (val[A[i]] == 0) val[A[i]] = ++x;
        B[i] = val[A[i]];
    }
    ll ans = 0;
    for (int i=0; i<N*2; ++i) {
        ans += query(N) - query(B[i]);
        upd(B[i], seen[B[i]] ? -1 : 1);
        seen[B[i]] = true;
    }
    ans += N;

    //ll ans2 = 0;
    //set<int> done;
    //for (int i=0; i<N*2; ++i) {
    //    if (done.insert(A[i]).second == false) continue;
    //    set<int> active;
    //    for (int j=i+1; j<N*2 && A[j]!=A[i]; ++j) {
    //        auto p = active.insert(A[j]);
    //        if (p.second == false) active.erase(p.first);
    //    }
    //    ans2 += active.size();
    //}
    //assert(ans2 % 2 == 0);
    //ans2 >>= 1;
    //ans2 += N;

    //cerr << ans << ' ' << ans2 << endl;
    //assert(ans == ans2);

    cout << ans << '\n';
}

