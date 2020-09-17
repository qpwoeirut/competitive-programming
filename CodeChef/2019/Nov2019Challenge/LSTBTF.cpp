#include <iostream>
#include <algorithm>
#include <set>
#include <string>

using namespace std;

set<int> squares;

int N;
int cur[10], ans[10];

void rec(int digit, int sum, int rem) {
    if (ans[0] != -1) return;
    if (digit == 10) {
        if (squares.find(sum) != squares.end()) {
            copy(cur, cur+10, ans);
        }
        return;
    }
    
    if (digit == 9) {
        cur[9] = rem;
        rec(digit+1, sum + (rem * digit * digit), 0);
        return;
    }
    for (int i=rem; i>=0; i--) {
        cur[digit] = i;
        rec(digit+1, sum + (i * digit * digit), rem-i);
    }
}

void solve() {
    cin >> N;
    
    fill(ans, ans+10, -1);
    rec(1, 0, N);
    
    if (ans[0] == -1) {
        cout << -1 << endl;
    }
    else {
        for (int i=1; i<10; i++) {
            cout << string(ans[i], i+'0');
        }
        cout << endl;
    }
}

int main() {
	int T;
	cin >> T;
	
	for (int i=1; i<=9000; i++) {
	    squares.insert(i*i);
	}
	while (T > 0) {
	    T--;
	    
	    solve();
	}
	return 0;
}
