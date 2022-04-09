#include <iostream>
#include <vector>

using namespace std;

vector<long long> vacation(int n, int q, vector<vector<long long>> trees, vector<vector<long long>> queries) {
    return vector<long long>(0);
}

int main() {

    int n, q; 
    cin >> n >> q;
    vector<vector<long long>> trees;
    vector<vector<long long>> queries(q, vector<long long>(2));
    
    for (int i = 0; i < n; i++) {
		int s; cin >> s;
		trees[i] = vector<long long>(s);
		for (int j = 0; j < s; j++) {
			cin >> trees[i][j];
		}
	}

    for (int i = 0; i < q; i++) {
        cin >> queries[i][0] >> queries[i][1];
    }

    vector<long long> ret = vacation(n, q, trees, queries);

    for (int b: ret) {
        cout << b << "\n";
    }
}