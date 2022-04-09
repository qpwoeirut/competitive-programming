#include <iostream>
#include <vector>
#include <array>

using namespace std;

int maximizeFun(vector<array<int, 2>>& itinerary) {
    return 0;
}

int main() {
    int t;
    for (cin >> t; t > 0; t--) {
        cin.get();
        vector<array<int, 2>> itinerary;
        int numEvents;
        for (cin >> numEvents; numEvents > 0; numEvents--) {
            int funValue;
            int energyRequirement;
            cin >> funValue;
            cin >> energyRequirement;
            itinerary.push_back(array<int, 2> {funValue, energyRequirement});     
            if (numEvents > 1) {
                cin.get();
            }
        }
        cout << maximizeFun(itinerary) << endl;
    }
}
