//utopia_divided.cpp created at 08/27/23 16:43:07

#include <bits/stdc++.h>

using namespace std;
using pii=pair<int,int>;
#define fi first
#define se second

const int MN = 10000;
const int INF = 1001001001;

int N;
int A[MN * 2];
int B[MN];

pii pick_pair(const int x, const int y, const set<int>& nums) {
    return pii(0, 0);
    //auto xit = nums.lower_bound()
}

vector<pii> increasing() {
    set<int> nums(A, A+N*2);
    int x = 0, y = 0;
    vector<pii> ans;
    for (int i=0; i<N; ++i) {
        int tx = (B[i] == 2 || B[i] == 3) ? -x : x;
        int ty = (B[i] == 3 || B[i] == 4) ? -y : y;
        const pii p = pick_pair(tx, ty, nums);
        if (p.fi == INF) {
            return vector<pii>();
        }
        x += p.fi;
        y += p.se;
        ans.push_back(p);
    }
    return ans;
}

vector<pii> small_big() {
    int S = 0;
    for (int i=1; i<N; ++i) S += B[i-1] == B[i];

    set<int> small(A, A+S*2);
    set<int> big(A+S*2, A+N*2);

    int x = 0, y = 0;
    for (int i=0; i<N; ++i) {
        if (i == 0 || B[i-1] != B[i]) {

        }
    }
    return vector<pii>();
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> N;
    for (int i=0; i<2*N; ++i) {
        cin >> A[i];
    }
    for (int i=0; i<N; ++i) {
        cin >> B[i];
    }
    sort(A, A+N*2);
    
    cout << 0 << endl;
}

