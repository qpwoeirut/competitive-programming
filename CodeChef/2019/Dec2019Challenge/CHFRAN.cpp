#include <iostream>
#include <algorithm>

using namespace std;

typedef pair<int,bool> pib;

const int MAXN = 100005;

inline bool comp(const pib& a, const pib& b) {
    if (a.first == b.first) {
        return a.second;
    }
    return a.first < b.first;
}

void solve() {
    int N;
    cin >> N;
    
    pib points[2*MAXN];
    for (int i=0; i<N; i++) {
        cin >> points[2*i].first >> points[(2*i) + 1].first;
        points[2*i].second = true;
        points[(2*i) + 1].second = false;
    }
    
    sort(points, points+(2*N), comp);
    
    int active = 0;
    bool prev = false;
    int nxt = N;
    int best = MAXN;
    for (int i=0; i<2*N; i++) {
        if (points[i].second == true) {
            active++;
            nxt--;
        }
        else {
            active--;
            prev = true;
        }
        
        if (prev == true && nxt > 0) {
            best = min(best, active);
        }
    }
    cout << (best == MAXN ? -1 : best) << endl;
}

int main() {
    int T;
    cin >> T;
    
    while (T > 0) {
        T--;
        solve();
    }
    
	return 0;
}
