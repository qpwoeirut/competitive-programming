#include <iostream>
#include <vector>

using namespace std;


bool efficientTrip(const vector<long long>& mountainList) {
    const int N = mountainList.size();
    for (int i=0; i<N; ++i) {
        for (int j=0; j<i; ++j) {
            for (int k=i+1; k<N; ++k) {
                if (abs(mountainList[i] - mountainList[j]) <= abs(mountainList[i] - mountainList[k])) return false;
            }
        }
    }
    return true;
}


int main() {
    cin.tie(0)->sync_with_stdio(0);
    int t; 
    cin >> t;

    while (t--) {
        int n; 
        cin >> n;
        vector<long long> mountainList;
        mountainList.resize(n);
        for (int i = 0; i < n; i++)
            cin >> mountainList[i];

        bool res = efficientTrip(mountainList);
        if (res) {
            cout << 1 << '\n';
        } else {
            cout << 0 << '\n';
        }
    }
}

