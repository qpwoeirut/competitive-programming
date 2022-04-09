#include <iostream>
#include <string>
#include <map>
#include <sstream>
#include <vector>
#include <set>

using namespace std;

int superhero(int n, vector<int> bff) {
    return 0;
}

int main() {
    int t;
    for (cin >> t; t > 0; t--) {
        int n;
        cin >> n;
        vector<int> bff;
        for (int i = 0; i < n; i++) {
            int k;
            cin >> k;
            bff.push_back(k);
        }

        cout << superhero(n, bff) << endl;
    }
}