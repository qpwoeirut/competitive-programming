#include <iostream>

using namespace std;

void solve() {
    int N, M;
    cin >> N >> M;
    
    int grid[N][M];
    for (int i=0; i<N; i++) {
        for (int j=0; j<M; j++) {
            cin >> grid[i][j];
        }
    }
    
    int ans = 0;
    for (int i=0; i<N; i++) {
        for (int j=0; j<M; j++) {
            int ct = 0;
            int lo = i, hi = i;
            int L = j, R = j;
            int len = 1;
            
            while (0 <= lo && hi < N && grid[lo][j] == grid[hi][j] &&
                   0 <= L && R < M && grid[i][L] == grid[i][R]) {
                    ct++;
                    lo--; hi++;
                    L--; R++;
                    len += 2;
            }
            
            ans += ct;
        }
    }
    
    cout << ans << endl;
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
