#include <bits/stdc++.h>
 
using namespace std;
using ll=long long;
 
const ll BASE = 1'000'000'000'000'000LL;
 
struct bigint {
    vector<ll> digits;
 
    bigint() : bigint(0) {}
    bigint(ll x) {
        assert(x >= 0);
        digits = vector<ll>({x});
        do_carry();
    }
 
    bigint operator+=(const bigint& other) {
        for (int i=0; i<other.digits.size(); ++i) {
            if (digits.size() <= i) {
                digits.push_back(other.digits[i]);
            } else {
                digits[i] += other.digits[i];
            }
        }
        do_carry();
        return *this;
    }
 
    void do_carry() {
        for (int i=0; i<digits.size(); ++i) {
            assert(digits[i] >= 0);
 
            if (digits[i] >= BASE) {
                ll carry = digits[i] / BASE;
                digits[i] %= BASE;
                if (digits.size() >= i+2) {
                    digits[i+1] += carry;
                } else {
                    digits.push_back(carry);
                }
            }
        }
    }
 
    string str() const {
        if (digits.empty()) return "0";
        string s = "";
        for (int i=digits.size() - 1; i>=0; --i) {
            string t = to_string(digits[i]);
            if (s.size() > 0) t += string(15 - t.size(), '0');
            s += t;
        }
        return s;
    }
};
 
const int MN = 100;
int A[MN][MN];
bigint ways[MN][MN];
 
int main() {
    cin.tie(0)->sync_with_stdio(0);
 
    int N;
    cin >> N;
    for (int i=0; i<N; ++i) {
        for (int j=0; j<N; ++j) {
            cin >> A[i][j];
        }
    }
 
    ways[0][0] = 1;
    for (int i=0; i<N; ++i) {
        for (int j=0; j<N; ++j) {
            if (A[i][j] == 0) continue;
 
            int r = i + A[i][j];
            int c = j + A[i][j];
 
            if (r < N) ways[r][j] += ways[i][j];
            if (c < N) ways[i][c] += ways[i][j];
        }
    }
 
    cout << ways[N-1][N-1].str() << '\n';
}
