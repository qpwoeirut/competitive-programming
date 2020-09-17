#include <iostream>
#include <bitset>
#include <string>

using namespace std;

const int MAXN = 100001;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	
    int T;
    cin >> T;
    
    string sa, sb;
    bitset<MAXN> a[2], b[2];
    while (T > 0) {
        T--;
        
        cin >> sa >> sb;
        a[0] = bitset<MAXN>(sa);
        b[0] = bitset<MAXN>(sb);
        
        int ct = 0;
        bool toggle = false;
        while (b[toggle].any()) {
            // cout << a[toggle] << " " << b[toggle] << endl;
            a[!toggle] = bitset<MAXN>(a[toggle] ^ b[toggle]);
            b[!toggle] = bitset<MAXN>(a[toggle] & b[toggle]);
            b[!toggle] <<= 1;
            toggle = !toggle;
            ct++;
        }
        // cout << a[toggle] << " " << b[toggle] << endl;
        
        cout << ct << endl;
    }
    
	return 0;
}
