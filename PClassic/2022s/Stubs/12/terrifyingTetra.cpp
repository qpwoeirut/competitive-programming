#include <iostream>
#include <string>
#include <map>
#include <sstream>
#include <vector>
#include <set>
#include <math.h>
#include <iomanip>

using namespace std;

vector<double> terrifyingTetra(vector<vector<double>> ps) {
    vector<double> centroid;
    return centroid;
}

int main() {
    int t;
    for (cin >> t; t > 0; t--) {
        vector<vector<double>> points;
        for (int j = 0; j < 4; j++) {
            string point0, point1, point2;
            cin >> point0;
            cin >> point1;
            cin >> point2;
            vector<double> temp;
            temp.push_back(stod(point0));
            temp.push_back(stod(point1));
            temp.push_back(stod(point2));
            points.push_back(temp);
        }
        vector<double> output = terrifyingTetra(points);
        cout << setprecision(1) << fixed;
        for (int j = 0; j < output.size(); j++) {
            cout << (round(output[j] * 10.0) / 10.0);
            if (j < output.size() - 1) {
                cout << " ";
            }
        }
		cout << "\n";
    }
}