#include <iostream>

using namespace std;

typedef long long ll;

ll p10[19];

int main() {
    for (int i=0; i<=18; i++) {
        p10[i] = (i==0 ? 1 : p10[i-1]*10);
    }
    
	int T;
	cin >> T;
	
	while (T > 0) {
	    T--;
	    
	    int N;
	    cin >> N;
	    
	    ll cur = 0;
	    
	    ll A;
	    cin >> A;
	    cur += A;
	    
	    ll S = A + p10[N] + p10[N];
	    cout << S << endl;
	    
	    ll B;
	    cin >> B;
	    cur += B;
	    
	    ll C = (S - p10[N]) - cur;
	    cout << C << endl;
	    cur += C;
	    
	    ll D;
	    cin >> D;
	    cur += D;
	    
	    ll E = S - cur;
	    cout << E << endl;
	    
	    int verdict;
	    cin >> verdict;
	    if (verdict != 1) return 1;
	}
	
	return 0;
}
