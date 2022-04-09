#include <iostream>
#include <vector>

using namespace std;


bool efficientTrip(vector<long long> mountainList) {
    return true;
}


int main() {

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
            cout << 1 << endl;
        } else {
            cout << 0 << endl;
        }
    }
}