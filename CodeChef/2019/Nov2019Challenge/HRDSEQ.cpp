#include <iostream>
#include <map>
#include <vector>
using namespace std;

map<int,vector<int>> pos;
int seq[128];
void gen() {
    for (int i=0; i<128; i++) {
        map<int,vector<int>>::iterator last = pos.find(seq[i]);
        if (last == pos.end()) {
            seq[i+1] = 0;
        }
        else {
            seq[i+1] = i - last->second.back();
        }
        pos[seq[i]].push_back(i);
        // cout << seq[i] << " ";
    }
}

void solve() {
    int N;
    cin >> N;
    N--;
    
    int num = seq[N];
    int ans = 0;
    for (int i=0; i<pos[num].size(); i++) {
        if (pos[num][i] > N) {
            break;
        }
        ans++;
    }
    
    cout << ans << endl;
}

int main() {
    gen();
	int T;
	cin >> T;
	
	while (T > 0) {
	    T--;
	    solve();
	}
	return 0;
}
