#include <bits/stdc++.h>

using namespace std;

#define x first
#define y second

typedef long double dbl;
typedef pair<dbl,dbl> point;

const int MN = 1001;

int N;
int A[MN], suf[MN];

vector<point> ans;
int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> N;
    for (int i=0; i<N; ++i) {
        cin >> A[i];
    }
    sort(A, A+N);
    suf[N-1] = 0;
    for (int i=N-1; i>0; --i) {
        suf[i-1] = A[i] + suf[i] - 0.01;
    }

    for (int i=0; i<N; ++i) { cerr << suf[i] << ' '; } cerr << endl;

    ans.emplace_back(point(0,0));
    ans.emplace_back(point(A[0], 0));

    for (int i=1; i<N; ++i) {
        
