using namespace std;

#include <iostream>

void printarray(vector<vector<char>> arr, int width, int height) {
    for(int i = 0; i < height; i++) {
        for(int j = 0; j < width; j++) {
            cout << arr[i][j];
        }
        cout << endl;
    }

}

vector<vector<char>> fillMosaic(int width, int height) {
}

int main() {
    int tests, width, height;
    cin >> tests;
    for (int i = 0; i < tests; i++) {
        cin >> width >> height;
        printarray(fillMosaic(width, height), width, height);
    }
}
