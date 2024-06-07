#include <bits/stdc++.h>

using namespace std;
using pii = pair<int, int>;

const int MN = 100006;

int N;
int A[MN];
int rA[MN];

vector<pii> do_intersect(const vector<pii>& intervals, int lo, int hi) {
    //cerr << intervals.size() << ' ' << lo << ' ' << hi << endl;
    vector<pii> new_intervals;
    if (lo > hi) {
        for (auto it = intervals.begin(); it != intervals.end(); ++it) {
            if (lo <= it->second) {
                new_intervals.emplace_back(max(it->first, lo), it->second);
            }
            if (it->first <= hi) {
                new_intervals.emplace_back(it->first, min(it->second, hi));
            }
        }
    } else {
        for (auto it = intervals.begin(); it != intervals.end(); ++it) {
            if (it->second < lo || hi < it->first) continue;
            new_intervals.emplace_back(max(it->first, lo), min(it->second, hi));
        }
    }
    return new_intervals;
}

bool check(int limit, int arr[]) {
    //cerr << limit << ' ' << (arr == rA) << endl;
    vector<pii> intervals;
    if (limit + 1 >= N - limit) {
        intervals.emplace_back(0, N - 1);
    } else {
        intervals.emplace_back(0, limit);
        intervals.emplace_back(N - limit, N);
    }

    for (int i=0; i<N; ++i) {
        const int diff = (i - arr[i] + N) % N;
        intervals = do_intersect(intervals, (diff - limit + N) % N, (diff + limit + N) % N);
        //cerr << i << endl; for (const pii& p: intervals) { cerr << p.first << ',' << p.second << endl; }
    }

    //cerr << endl;
    return !intervals.empty();
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> N;
    for (int i=0; i<N; ++i) {
        cin >> A[i]; --A[i];
    }
    rotate(A, find(A, A+N, 0), A+N);

    copy(A, A+N, rA);
    reverse(rA+1, rA+N);

    //for (int i=0; i<N; ++i) { cerr << A[i] << ' '; } cerr << endl;
    //for (int i=0; i<N; ++i) { cerr << rA[i] << ' '; } cerr << endl;

    int lo = 0, hi = N / 2;
    while (lo < hi) {
        int mid = (lo + hi) / 2;
        if (check(mid, A) || check(mid, rA)) hi = mid;
        else lo = mid + 1;
    }

    cout << lo << '\n';
}
