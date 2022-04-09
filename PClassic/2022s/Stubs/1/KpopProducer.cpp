#include <string>
#include <iostream>
#include <vector>
using namespace std;

string danceCommand(string word, vector<int> shifts) {
    return "";
}

int main() {
    int t;
    cin >> t;
    while (t-- > 0) {
        string word;
        cin >> word;
        int length;
        cin >> length;
        string line;
        vector<int> shifts;
        shifts.resize(length);
        for (int i = 0; i < length; i++) {
            std::cin >> shifts[i];
        }
        std::cout << danceCommand(word, shifts) << std::endl;

    }
}