/*
ID: zhongbr1
TASK: buylow
LANG: C++14
*/

//faster_buylow.cpp created at 12/25/20 11:50:21

#include <bits/stdc++.h>

using namespace std;

const int MN = 5005;
const int BASE = 1e9;
const int DIGITS = 9;

struct BigInt {
    vector<int> d;
    
    BigInt() {
        d = vector<int>();
    }
    BigInt(const int x) {
        assert(x < BASE); // too lazy to impl that for now
        d = vector<int>(1, x);
    }
    
    const BigInt operator+=(const BigInt& o) {
        int carry = 0;
        for (int i=0; i<o.d.size() || carry; ++i) {
            const int x = (i < o.d.size() ? o.d[i] : 0) + carry;
            if (i >= d.size()) d.push_back(x);
            else d[i] += x;

            carry = d[i] >= BASE;
            if (d[i] >= BASE) {
                d[i] -= BASE;
            }
        }
        return *this;
    }

    friend ostream& operator<<(ostream& os, const BigInt& o) {
        if (o.d.empty()) return os << '0';
        if (o.d.size() == 1) return os << o.d[0];
        os << o.d.back();
        for (int i=o.d.size() - 2; i>=0; --i) {
            os << setw(DIGITS) << setfill('0') << o.d[i];
        }
        return os;
    }
};

int N, M;
int A[MN], nums[MN];
int len[MN];
BigInt ct[MN];
bool used[MN];

int main() {
    freopen("buylow.in", "r", stdin);
    freopen("buylow.out", "w", stdout);
    cin.tie(0)->sync_with_stdio(0);

    cin >> N;
    for (int i=0; i<N; ++i) {
        cin >> A[i];
        nums[i] = A[i];
    }
    sort(nums, nums+N);
    M = unique(nums, nums+N) - nums;
    for (int i=0; i<N; ++i) {
        A[i] = lower_bound(nums, nums+M, A[i]) - nums;
    }

    for (int i=0; i<N; ++i) {
        len[i] = 1;
        ct[i] = BigInt(1);
    }

    for (int i=2; i<=N; ++i) {
        for (int j=i-1; j>=0; --j) {
            if (A[j] <= A[i] || used[A[j]]) continue;
            used[A[j]] = true;
            if (len[i] < len[j] + 1) {
                len[i] = len[j] + 1;
                ct[i] = ct[j];
            } else if (len[i] == len[j] + 1) {
                ct[i] += ct[j];
            }
        }
        fill(used, used+M, false);
    }

    int ans_len = 0;
    BigInt ans_ct;
    for (int i=N-1; i>=0; --i) {
        if (used[A[i]]) continue;
        used[A[i]] = true;
        if (ans_len < len[i]) {
            ans_len = len[i];
            ans_ct = ct[i];
        } else if (ans_len == len[i]) {
            ans_ct += ct[i];
        }
    }

    cout << ans_len << ' ' << ans_ct << endl;
}
