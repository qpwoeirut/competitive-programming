#include <iostream>
#include <string>

using namespace std;

void solve() {
    int N;
    cin >> N;
    
    bool ct[10];
    fill(ct, ct+10, false);
    
    string in;
    for (int i=0; i<N; i++) {
        cin >> in;
        for (int j=0; j<10; j++) {
            if (in[j] == '1') {
                ct[j] = !ct[j];
            }
        }
    }
    
    int ans = 0;
    for (int i=0; i<10; i++) {
        if (ct[i]) ans++;
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
