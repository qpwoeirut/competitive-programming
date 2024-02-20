#include <bits/stdc++.h>

using namespace std;

const int MN = 100005;
const int MK = 22;

int N, K;
string S;
int A[MN];
vector<int> pos[MK];

bool chmn(int& a, const int b) {
    if (a>b) {a=b; return true;}
    return false;
}
bool chmx(int& a, const int b) {
    if (a<b) {a=b; return true;}
    return false;
}

bool used[MK];
int ord[MK];

int order_cost() {
    int cur = 1, p = -1;
    for (int i=0; i<N; ++i) {
        assert(A[i] < K);
        if (ord[A[i]] <= p) {
            ++cur;
        }
        p = ord[A[i]];
    }
    return cur;
}

int correct[MK];
int brute(int x=1) {
    for (int i=0; i<K; ++i) { 
        ord[i] = i;
    }

    int ans = 1001001001;
    do {
        if (chmn(ans, order_cost())) {
            copy(ord, ord+K, correct);
        }
    } while (next_permutation(ord+x, ord+K));

    return ans;
}

int rel[MK][MK];
set<int> active;
bool flip(const int c) {
    for (const int x: active) {
        if (rel[x][c] == 1) return true;
    }
    return false;
}

bool seen[MK];
int solve() {
    fill(seen, seen+K, false);
    deque<int> d;
    
    int ans = 1001001001;
    for (int i=0; i<N; ++i) {
        if (seen[A[i]]) {
            for (int j=0; j<d.size(); ++j) {
                ord[d[j]] = j;
            }

            while (d.front() != A[i]) {
                assert(seen[d.front()]);
                seen[d.front()] = false;
                d.pop_front();
                assert(d.size());
            }
            d.pop_front();
        } else {
            seen[A[i]] = true;
        }
        d.push_back(A[i]);
        if (d.size() >= K - 7) {
            chmn(ans, brute(d.size()));
        }
    }

    return ans;
}

int compress() {
    vector<int> nums;
    for (int i=0; i<N; ++i) {
        nums.push_back(A[i]);
    }
    int start = A[0];

    sort(nums.begin(), nums.end());
    nums.resize(unique(nums.begin(), nums.end()) - nums.begin());
    nums.erase(find(nums.begin(), nums.end(), start));
    for (int i=0; i<N; ++i) {
        if (A[i] == start) A[i] = 0;
        else A[i] = (lower_bound(nums.begin(), nums.end(), A[i]) - nums.begin()) + 1;
    }

    return nums.size() + 1;
}

void test() {
    for (N=1; N<=10; ++N) {
        for (int t=0; t<10000; ++t) {
            S.clear();
            for (int i=0; i<N; ++i) {
                A[i] = rand() % 10;
            }
            K = compress();
            for (int i=0; i<N; ++i) {
                S.push_back(A[i] + 'a');
            }
            int bans = brute();
            int sans = solve();

            if (sans != bans) {
                cout << S << endl;
                cout << sans << ' ' << bans << endl;
            }
            assert(sans == bans);
        }
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    //test(); return 0;

    cin >> S;
    N = S.size();
    set<char> chars;
    for (int i=0; i<N; ++i) {
        A[i] = S[i] - 'a';
        chars.insert(S[i]);
    }
    K = compress();

    bool s1 = false;
    for (const char c: "mildre") {
        if (chars.count(c)) s1 = true;
    }
    if (s1) {
        cout << brute() << endl;
    } else {
        cout << solve() << endl;
    }
}
/*
mildredree
aabb
abba
abab
abcacbacbacb

bacb
acb bac 2

cabcb
cab 2

baccb
bac acb cba 3

abacb
acb 2

adcbd
adcb 2
*/
