#include <iostream>
#include <algorithm>
#include <string>

using namespace std;

void solve() {
    int N;
    cin >> N;
    
    string s;
    cin >> s;
    
    int pos[26];
    fill(pos, pos+26, -1);
    int gap = N;
    for (int i=0; i<N; i++) {
        if (pos[s[i] - 'a'] != -1) {
            gap = min(gap, i - pos[s[i] - 'a']);
        }
        pos[s[i] - 'a'] = i;
    }
    
    cout << N - gap << endl;
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
