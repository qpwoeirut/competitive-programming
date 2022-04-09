#include <iostream>
#include <string>
#include <map>

using namespace std;

string translate(string message, map<string, string> map) {
    return "";
}

int main() {
    int t;
    for (cin >> t; t > 0; t--) {
        string message;
        cin.get();
        getline(cin, message);
 
        map<string, string> map;
        int mappingCount;
        for (cin >> mappingCount; mappingCount > 0; mappingCount--) {
            string key;
            string value;
            cin >> key;
            cin >> value;
            
            map[key] = value;
            
            if (mappingCount > 1) {
                cin.get();
            }
        }
        
        cout << translate(message, map) << endl;
    }
}