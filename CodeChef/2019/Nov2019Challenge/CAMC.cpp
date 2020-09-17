#include <iostream>
#include <algorithm>
#include <deque>
#include <set>

using namespace std;

set<int> opts[100001];
bool comp (const int& a, const int& b) {
    return *(opts[a].begin()) < *(opts[b].begin());
};

void solve() {
    int N, M;
    cin >> N >> M;
    
    deque<int> idxs;
    for (int i=0; i<M; i++) {
        opts[i].clear();
    }
    
    int tmp;
    for (int i=0; i<N; i++) {
        cin >> tmp;
        opts[i % M].insert(tmp);
    }
    
    // cout << "----OPTIONS----\n";
    // for (int i=0; i<M; i++) {
    //     for (set<int>::iterator it=opts[i].begin(); it!=opts[i].end(); it++) {
    //         cout << *it << " ";
    //     }
    //     cout << endl;
    // }
    // cout << endl;
    
    for (int i=0; i<M; i++) {
        idxs.push_back(i);
    }
    
    sort(idxs.begin(), idxs.end(), comp);
    int best = 1e9 + 1;
    while (true) {
        // cout << "\nidxs: ";
        // for (int i=0; i<idxs.size(); i++) {
        //     cout << idxs[i] << " ";
        // }
        // cout << endl;
        
        int cur = idxs.front();
        best = min(best, *(opts[idxs.back()].begin()) - *(opts[cur].begin()));
        
        // cout << "rb, b: " << cur << " " << idxs.back() << endl;
        // cout << "best, opts[rb], opts[b]: " << best << " " << *(opts[idxs.back()].begin()) << " " << *(opts[cur].begin()) << endl;
        if (opts[cur].size() == 1) {
            break;
        }
        opts[cur].erase(opts[cur].begin());
        
        idxs.pop_front();
        idxs.insert(upper_bound(idxs.begin(), idxs.end(), cur, comp), cur);
    }
    
    cout << best << endl;
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
