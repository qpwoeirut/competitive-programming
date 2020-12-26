/*
ID: zhongbr1
TASK: buylow
LANG: C++14
*/

//buylow.cpp created at 12/24/20 19:03:36

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const ll BASE = 1e18;
const int NEGATIVE = -1;
const int POSITIVE = 1;

struct BigInt {
    int sign;
    vector<ll> d;

    BigInt() {
        sign = POSITIVE;
        d = vector<ll>();
    }

    BigInt(const ll x) {
        sign = x >= 0 ? POSITIVE : NEGATIVE;
        d = vector<ll>(1, x);
    }

    inline const bool is_zero() const {
        return d.empty() || (d.size() == 1 && d[0] == 0);
    }

    int comp(const BigInt& o) const {
        if (is_zero() && o.is_zero()) return 0;
        if (sign < o.sign) return -1;
        if (sign > o.sign) return 1;

        return abs_comp(o) * sign;
    }

    int abs_comp(const BigInt& o) const {
        if (d.size() != o.d.size()) return (d.size() < o.d.size()) ? -1 : 1;
        for (int i=d.size() - 1; i>=0; --i) {
            if (d[i] != o.d[i]) return (d[i] < o.d[i]) ? -1 : 1;
        }
        return 0;
    }

    const bool operator<(const BigInt& o) const {
        return comp(o) == -1;
    }

    const bool operator==(const BigInt& o) const {
        return comp(o) == 0;
    }
    
    const bool operator!=(const BigInt& o) const {
        return !(*this == o);
    }

    BigInt abs_add(const BigInt& o) {
        int carry = 0;
        for (int i=0; i<o.d.size(); ++i) {
            if (i >= d.size()) d.push_back(o.d[i] + carry);
            else {
                d[i] += o.d[i] + carry; 
            }
            if (d[i] >= BASE) {
                d[i] -= BASE;
                carry = 1;
            } else carry = 0;
        }

        for (int i=o.d.size(); carry > 0; ++i) {
            if (i >= d.size()) {
                d.push_back(carry);
                carry = 0;
            }
            else {
                if (++d[i] >= BASE) {
                    d[i] -= BASE;
                    carry = 1;
                } else carry = 0;
            }
        }

        return *this;
    }

    BigInt abs_sub(const BigInt& o) {
        int borrow = 0;
        for (int i=0; i<o.d.size(); ++i) {
            d[i] -= o.d[i] + borrow;
            if (d[i] < 0) {
                d[i] += BASE;
                borrow = 1;
            } else {
                borrow = 0;
            }
        }
        for (int i=o.d.size(); borrow > 0; ++i) {
            if (--d[i] < 0) {
                d[i] += BASE;
                borrow = 1;
            } else borrow = 0;
        }

        while (d.size() > 0 && d.back() == 0) d.pop_back();

        return *this;
    }

    BigInt operator-() const {
        BigInt ret = *this;
        ret.sign *= -1;
        return ret;
    }

    BigInt operator +=(const BigInt& o) {
        if (o.is_zero()) return *this;
        if (is_zero()) {
            *this = o;
            return *this;
        }
        if (sign == o.sign) {
            return abs_add(o);
        } else {
            const int c = abs_comp(o);
            if (c == -1) {
                const BigInt tmp = *this;
                *this = o;
                return abs_sub(tmp);
            } else if (c == 0) {
                *this = BigInt();
                return *this;
            } else {
                return abs_sub(o);
            }
        }
    }
    BigInt operator -=(const BigInt& o) {
        if (o.is_zero()) return *this;
        if (is_zero()) {
            *this = -o;
            return *this;
        }
        return *this += -o;
    }
};

string to_string(const BigInt& x) {
    if (x.is_zero()) return "0";
    stringstream ss;
    ss << x.d.back();
    for (int i=(int)x.d.size() - 2; i>=0; --i) {
        ss << setw(18) << setfill('0') << x.d[i];
    }
    return ss.str();
}

const int MN = 5005;

int N, M;
int A[MN], nums[MN];
BigInt dp[2][MN];
BigInt BIT[MN], arr[MN];
bool used[MN];

void upd(int idx, BigInt& val) {
    if (val != arr[idx]) {
        val -= arr[idx];
        arr[idx] += val;
        for (; idx<=M; idx+=(idx & -idx)) BIT[idx] += val;
    }
    val = BigInt();
}
void query(int idx, BigInt& ret) {
    ret = BigInt();
    for (; idx>0; idx-=(idx & -idx)) if (!BIT[idx].is_zero()) ret += BIT[idx];
}

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
        A[i] = (lower_bound(nums, nums+M, A[i]) - nums) + 1;
    }

    reverse(A, A+N);
    for (int i=0; i<N; ++i) {
        dp[1][i] = 1;
    }
    //for (int j=0; j<N; ++j) { cerr << A[j] << ' '; } cerr << endl;

    int best = 1;
    string ct = to_string(M);
    for (int i=2; i<=M; ++i) {
        for (int j=0; j<N; ++j) {
            query(A[j] - 1, dp[i&1][j]);
            upd(A[j], dp[!(i&1)][j]);
        }
        BigInt total;
        fill(used, used+M+1, false);
        for (int j=N-1; j>=0; --j) {
            if (used[A[j]]) continue;
            used[A[j]] = true;
            total += dp[i&1][j];
        }
        //for (int j=0; j<N; ++j) { cerr << to_string(dp[i&1][j]) << ' '; } cerr << endl;
        if (total.is_zero()) break;
        //if (total == 0) break;
        best = i;
        ct = to_string(total);

        fill(BIT, BIT+M+1, 0);
        fill(arr, arr+M+1, 0);
    }

    cout << best << ' ' << ct << endl;
}

