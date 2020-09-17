#include <iostream>

using namespace std;

void solve() {
    int N;
    cin >> N;
    
    int zero = 0, two = 0;
    int tmp;
    for (int i=0; i<N; i++) {
        cin >> tmp;
        if (tmp == 0) {
            zero++;
        }
        else if (tmp == 2) {
            two++;
        }
    }
    
    int ans = 0;
    ans += (zero * (zero-1))/2;
    ans += (two * (two-1))/2;
    
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
