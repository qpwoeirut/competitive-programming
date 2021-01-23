//cf_835d.cpp created at 01/22/21 19:35:46

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MN = 5003;

const int CT = 1;
const ll MOD[CT] = {(ll)1e9 + 7};//, (ll)1e9 + 9, (ll)1e9 + 21, (ll)1e9 + 33};
const ll BASE = 29;

ll pw[MN][CT];

struct Hash {
    ll h[CT];
    int len;

    Hash() {
        fill(h, h+CT, 0);
        len = 0;
    }
    Hash(const Hash& o) {
        copy(o.h, o.h+CT, h);
        len = o.len;
    }

    void push_front(const char c) {
        for (int j=0; j<CT; ++j) {
            h[j] = (h[j] + (c - 'a' + 1) * pw[len][j]) % MOD[j];
        }
        ++len;
    }
    void push_back(const char c) {
        for (int j=0; j<CT; ++j) {
            h[j] = (h[j] * BASE + c - 'a' + 1) % MOD[j];
        }
        ++len;
    }

    Hash operator-(const Hash& o) const {
        Hash ret;
        ret.len = len - o.len;
        for (int j=0; j<CT; ++j) {
            ret.h[j] = (h[j] - o.h[j] * pw[len - o.len][j]) % MOD[j];
            if (ret.h[j] < 0) ret.h[j] += MOD[j];
        }
        return ret;
    }
    
    bool operator==(const Hash& o) const {
        for (int j=0; j<CT; ++j) {
            if (h[j] != o.h[j]) return false;
        }
        return len == o.len;
    }

    bool operator<(const Hash& o) const {
        for (int j=0; j<CT; ++j) {
            if (h[j] != o.h[j]) return h[j] < o.h[j];
        }
        return len < o.len;
    }
};

string S;
int ans[MN];
Hash s_hash[MN];
set<Hash> pals;

void add(const int start, const int finish, const int level) {
    //if (level > 0) { cerr << start << ' ' << finish << ' ' << level << endl; }
    if (level > 0 && pals.count(s_hash[finish] - s_hash[start])) ++ans[level];

    if (start + 1 == finish) return;
    //cerr << start << ' ' << ((start + finish) >> 1) << ' ' << ((start + finish + 1) >> 1) << ' ' << finish << endl;
    if (s_hash[(start + finish) >> 1] - s_hash[start] == s_hash[finish] - s_hash[(start + finish + 1) >> 1]) {
        add(start, (start + finish) >> 1, level + 1);
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    for (int i=0; i<MN; ++i) {
        for (int j=0; j<CT; ++j) {
            pw[i][j] = i ? (pw[i-1][j] * BASE) % MOD[j] : 1;
        }
    }

    cin >> S;
    const int N = S.size();
    for (int i=0; i<N; ++i) {
        s_hash[i+1] = Hash(s_hash[i]);
        s_hash[i+1].push_back(S[i]);
    }
    //for (int i=0; i<N; ++i) { cerr << s_hash[i+1].h[0] << ' '; } cerr << endl;

    for (int i=0; i<N; ++i) {
        Hash pal;
        for (int j=0; j<=i&& j+i<N; ++j) {
            if (S[i-j] != S[i+j]) break;
            pal.push_front(S[i-j]);
            if (j > 0) pal.push_back(S[i+j]);
            pals.insert(pal);
            ++ans[0];
        }
        for (int j=0; j<=i&& j+i+1<N; ++j) {
            if (S[i-j] != S[i+j+1]) break;
            pal.push_front(S[i-j]);
            pal.push_back(S[i+j+1]);
            pals.insert(pal);
            ++ans[0];
        }
    }

    //for (const Hash& x: pals) {cerr << x.h[0] << ' ';} cerr << endl;

    for (int s=0; s<N; ++s) {
        for (int f=s+2; f<=N; ++f) {
            add(s, f, 0);
        }
    }

    for (int i=0; i<N; ++i) {
        if (i) cout << ' ';
        cout << ans[i];
    }
    cout << endl;
}

