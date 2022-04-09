#include <bits/stdc++.h>
 
using namespace std;

vector<string> tubeAdventures(int n, int m, int q, string islands[], int queries[]) {
    vector<string> response;
    return response;
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        int n, m, q;
        cin >> n >> m >> q;
        int grid[n][m];
        string islands[n];
        int queries[q];
        for (int i = 0; i < n; i++) {
            string s; cin >> s;
            islands[i] = s;
        }
        for (int i = 0; i < q; i++) {
            int s; cin >> s;
            queries[i] = s;
        }
        vector<string> output = tubeAdventures(n, m, q, islands, queries);
        for (string s : output) {
            cout << s << endl;
        }
    }
}