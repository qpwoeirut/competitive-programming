//square_pasture.cpp created at 01/23/21 15:13:35
// Submitted, AC at 16:55

#include <bits/stdc++.h>

using namespace std;

#define LB lower_bound
#define UB upper_bound
#define all(x) (x).begin(), (x).end()

#define x first
#define y second

typedef pair<int,int> pii;

const int MN = 205;
const int INIT = 1001001001;

int N;
pii A[MN];

int over;
int solve() {
    sort(A, A+N);
    over = 0;
    int ans = 0;
    for (int i=0; i<N; ++i) {
        for (int j=0; j<N; ++j) {
            if (A[i].y > A[j].y) continue;
            const int sz = A[j].y - A[i].y;
            if (abs(A[i].x - A[j].x) > sz) continue;

            const int minx = min(A[i].x, A[j].x);
            const int maxx = max(A[i].x, A[j].x);
            const int miny = A[i].y;
            const int maxy = A[j].y;
            vector<int> in;
            //cerr << string(50, '=') << endl;
            //cerr << A[i].x << ' ' << A[i].y << ' ' << A[j].x << ' ' << A[j].y << endl;
            for (int k=0; k<N; ++k) {
                if (miny <= A[k].y && A[k].y <= maxy) {
                    in.push_back(A[k].x);
                }
            }
            const int stop = LB(all(in), minx) - in.begin();
            int L = LB(all(in), maxx - sz) - in.begin();

            //cerr << "L = " << L << endl;
            //cerr << "sz = " << sz << endl;
            //cerr << "stop = " << stop << endl;
            //cerr << "in = ["; for (int i=0; i<in.size(); ++i) { if (i) cerr << ' '; cerr << in[i]; } cerr << ']' << endl;

            int prev = -INIT;
            for (; L <= stop; ++L) {
                if (binary_search(all(in), in[L] + sz)) ++over;

                int lo = UB(all(in), max(maxx, prev + sz + 1)) - in.begin();
                --lo;
                int hi = UB(all(in), in[L] + sz) - in.begin();
                assert(in[L] + sz >= maxx);
                //cerr << prev << ' ' << in[L] << ' ' << lo << ' ' << hi << endl;
                ans += hi - lo;

                prev = in[L];
            }
        }
    }

    return ans;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> N;
    for (int i=0; i<N; ++i) {
        cin >> A[i].x >> A[i].y;
    }

    int ans = solve();
    int x_over = over;
    
    for (int i=0; i<N; ++i) {
        swap(A[i].x, A[i].y);
    }
    //cerr << string(50, '|') << endl;
    //cerr << ans << endl;
    ans += solve();
    assert(x_over == over);

    ++ans; // empty
    //cerr << ans << ' ' << over << endl;

    cout << ans - over << endl;
}
