#include <bits/stdc++.h>

using namespace std;
using ll=long long;

#define sz(x) (int)((x).size())

// https://github.com/kth-competitive-programming/kactl/blob/main/content/data-structures/FenwickTree.h
struct FT {
	vector<ll> s;
	FT(int n) : s(n) {}
	void update(int pos, ll dif) { // a[pos] += dif
		for (; pos < sz(s); pos |= pos + 1) s[pos] += dif;
	}
	ll query(int pos) { // sum of values in [0, pos)
		ll res = 0;
		for (; pos > 0; pos &= pos - 1) res += s[pos-1];
		return res;
	}
	int lower_bound(ll sum) {// min pos st sum of [0, pos] >= sum
		// Returns n if no sum is >= sum, or -1 if empty sum is.
		if (sum <= 0) return -1;
		int pos = 0;
		for (int pw = 1 << 25; pw; pw >>= 1) {
			if (pos + pw <= sz(s) && s[pos + pw-1] < sum)
				pos += pw, sum -= s[pos-1];
		}
		return pos;
	}
};

const int MN = 100005;
ll A[MN];

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int N;
    cin >> N;
    for (int i=0; i<N; ++i) {
        cin >> A[i];
    }

    ll total = 0;
    ll score = 0;
    FT ft_val(MN), ft_ct(MN);
    for (int i=0; i<N; ++i) {
        const ll ct = i - ft_ct.query(A[i]);
        const ll sum = total - ft_val.query(A[i]);
        score += sum + ct * A[i];
        ft_val.update(A[i], A[i]);
        ft_ct.update(A[i], 1);
        total += A[i];
    }

    cout << score << '\n';
}
