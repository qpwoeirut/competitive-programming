//sorting.cpp created at 01/29/21 21:00:48

#include <bits/stdc++.h>

using namespace std;

const int MN = 101;

int N;
int A[MN], B[MN];

void solve() {

}

int pack() {
    int ret = 0;
    for (int i=0; i<=N; ++i) {
        ret <<= 3;
        ret |= B[i];
    }
    assert(ret < (1 << 27));
    return ret;
}

void unpack(int ret) {
    for (int i=N; i>=0; --i) {
        B[i] = ret & 7;
        ret >>= 3;
    }
    assert(B[N] == N-1);
}

short seen[1 << 27];
bool ans[1001];
bool brute(const int test) {
    assert(N <= 8);
    copy(A, A+N, B);

    for (int i=0; i<N; ++i) {
        --B[i];
    }
    B[N] = N-1;

    const int start = pack();
    if (seen[start] > 0) {
        ans[test] = ans[seen[start]];
        return ans[seen[start]];
    }
    
    for (int i=0; i<N; ++i) {
        B[i] = i;
    }
    const int tar = pack();

    queue<int> q;
    q.push(start);
    seen[start] = test;
    while (q.size() > 0) {
        const int cur = q.front(); q.pop();
        
        if (cur == tar) {
            ans[test] = true;
            return true;
        }

        for (int i=0; i+1<N; ++i) {
            for (int j=i+2; j+1<N; ++j) {
                unpack(cur);
                
                swap(B[i], B[j]);
                swap(B[i+1], B[j+1]);
                const int nxt = pack();
                if (seen[nxt] < test) {
                    if (seen[nxt] > 0) {
                        ans[test] = ans[seen[nxt]];
                        return ans[seen[nxt]];
                    }
                    seen[nxt] = test;
                    q.push(nxt);
                }
            }
        }
    }
    ans[test] = false;
    return false;
}

int main() {
    //N = 8;
    //for (int i=0; i<8; ++i) {
    //    B[i] = 7 - i;
    //}
    //B[8] = 7;
    //cout << pack() << endl;
    cin.tie(0)->sync_with_stdio(0);
    int T;
    cin >> T;
    for (int t=1; t<=T; ++t) {
        cin >> N;
        for (int i=0; i<N; ++i) {
            cin >> A[i];
        }
        cout << (brute(t) ? "YES\n" : "NO\n");
    }
}

