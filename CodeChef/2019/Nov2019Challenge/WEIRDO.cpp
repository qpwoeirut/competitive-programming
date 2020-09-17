#include <iostream>
#include <iomanip>
#include <algorithm>
#include <cmath>
#include <string>

using namespace std;

inline int vowel(const char& c) {
    if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u') {
        return 1;
    }
    else {
        return -1;
    }
    
    // return (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u');
}

bool is_alice(const string& s) {
    // cout << s << endl;
    for (int i=0; i<s.size(); i++) {
        if (i+1 < s.size() && vowel(s[i]) + vowel(s[i+1]) < 0) {
            return false;
        }
        else if (i+2 < s.size() && vowel(s[i]) + vowel(s[i+1]) + vowel(s[i+2]) < 0) {
            return false;
        }
        // cout << i << ": " << diff << endl;
    }
    // cout << endl;
}

bool brute_force(const string& s) {
    for (int i=0; i<s.size(); i++) {
        int diff = vowel(s[i]);
        for (int j=i+1; j<s.size(); j++) {
            diff += vowel(s[j]);
            if (diff < 0) {
                return false;
            }
        }
    }
    
    return true;
}

void solve() {
    int N;
    cin >> N;
    
    int ct_a[26], ct_b[26];
    int occ_a[26], occ_b[26];
    for (int i=0; i<26; i++) {
        ct_a[i] = 0;
        ct_b[i] = 0;
        occ_a[i] = 0;
        occ_b[i] = 0;
    }
    
    int recipes[2] = {0, 0};
    int cur[26];
    string s;
    for (int i=0; i<N; i++) {
        cin >> s;
        
        for (int j=0; j<26; j++) {
            cur[j] = 0;
        }
        for (int j=0; j<s.size(); j++) {
            cur[s[j] - 'a']++;
        }
        
        if (brute_force(s)) {
            // cout << "alice: " << s << endl;
            for (int j=0; j<26; j++) {
                if (cur[j] > 0) {
                    ct_a[j]++;
                    occ_a[j] += cur[j];
                }
            }
            recipes[0]++;
        }
        else {
            // cout << "bob: " << s << endl;
            for (int j=0; j<26; j++) {
                if (cur[j] > 0) {
                    ct_b[j]++;
                    occ_b[j] += cur[j];
                }
            }
            recipes[1]++;
        }
    }
    
    // double score_a = 1, score_b = 1;
    double num_a = 1, den_a = 1;
    double num_b = 1, den_b = 1;
    for (int i=0; i<26; i++) {
        if (ct_a[i] > 0) {
            num_a *= ct_a[i];
            den_a *= pow(occ_a[i], recipes[0]);
            // cout << "a " << i << " " << ct_a[i] << " " << occ_a[i] << " " << recipes[0] << endl;
        }
        if (ct_b[i] > 0) {
            num_b *= ct_b[i];
            den_b *= pow(occ_b[i], recipes[1]);
            // cout << "b " << i << " " << ct_b[i] << " " << occ_b[i] << " " << recipes[1] << endl;
        }
        // cout << score_a << " " << score_b << endl;
        // score_a *= ct_a[i] / pow(occ_a[i], recipes[0]);
        // score_b *= ct_b[i] / pow(occ_b[i], recipes[1]);
        
        // cout << num_a << "/" << den_a << ", " << num_b << "/" << den_b << endl;
    }
    
    double ratio = (num_a * den_b) / (num_b * den_a);
    if (ratio > 1e7) {
        cout << "Infinity" << endl;
    }
    else {
        cout << ratio << endl;
    }
    
}

int main() {
    int T;
    cin >> T;
    
    cout << setprecision(7) << fixed;
    while (T > 0) {
        T--;
        
        solve();
    }
    
	return 0;
}
