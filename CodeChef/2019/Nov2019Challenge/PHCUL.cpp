#include <iostream>
#include <algorithm>
#include <cmath>
#include <iomanip>

using namespace std;

inline double sq(const double& n) {
    return n*n;
}

inline double get_dist(int x, int y, int cx, int cy) {
    return sqrt(sq(x - cx) + sq(y - cy)); 
}


void solve() {
    int sx, sy;
    cin >> sx >> sy;
    
    int N, M, K;
    cin >> N >> M >> K;
    
    pair<int,int> a[5001], b[5001], c[5001];
    for (int i=0; i<N; i++) {
        cin >> a[i].first >> a[i].second;
    }
    for (int i=0; i<M; i++) {
        cin >> b[i].first >> b[i].second;
    }
    for (int i=0; i<K; i++) {
        cin >> c[i].first >> c[i].second;
    }
    
    double dist_a[5001], dist_b[5001];
    for (int i=0; i<N; i++) {
        dist_a[i] = 4e18;
        for (int j=0; j<K; j++) {
            dist_a[i] = min(dist_a[i], get_dist(a[i].first, a[i].second, c[j].first, c[j].second));
        }
    }
    
    for (int i=0; i<M; i++) {
        dist_b[i] = 4e18;
        for (int j=0; j<K; j++) {
            dist_b[i] = min(dist_b[i], get_dist(b[i].first, b[i].second, c[j].first, c[j].second));
        }
    }
    
    double best = 4e18;
    for (int i=0; i<N; i++) {
        for (int j=0; j<M; j++) {
            best = min(best, get_dist(sx, sy, a[i].first, a[i].second) +
                             get_dist(a[i].first, a[i].second, b[j].first, b[j].second) +
                             dist_b[j]);
            best = min(best, get_dist(sx, sy, b[j].first, b[j].second) +
                             get_dist(b[j].first, b[j].second, a[i].first, a[i].second) +
                             dist_a[i]);
        }
    }
    
    cout << best << endl;
}

int main() {
    int T;
    cin >> T;
    
    cout << setprecision(10) << fixed;
    while (T > 0) {
        T--;
        
        solve();
    }
	return 0;
}
