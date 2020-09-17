#include <iostream>
#include <algorithm>

using namespace std;

void solve() {
    int N;
    cin >> N;
    
    int score[12];
    fill(score, score+12, 0);
    
    int p, s;
    for (int i=0; i<N; i++) {
        cin >> p >> s;
        
        score[p] = max(score[p], s);
    }
    
    int ans = 0;
    for (int i=1; i<=8; i++) {
        ans += score[i];
    }
    
    cout << ans << endl;
    return;
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
