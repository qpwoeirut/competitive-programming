/*
ID: zhongbr1
TASK: contact
LANG: C++11
*/

#include <bits/stdc++.h>

using namespace std;

#define FI first
#define SE second

inline bool cmp(const string& a, const string& b) {
    if (a.size() != b.size()) {
        return a.size() < b.size();
    }
    for (int i=0; i<a.size(); i++) {
        if (a[i] != b[i]) {
            return a[i] < b[i];
        }
    }
    return false;
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    freopen("contact.in", "r", stdin);
    freopen("contact.out", "w", stdout);

    int A, B, N;
    cin >> A >> B >> N;

    string s, tmp;
    while (cin >> tmp) s += tmp;

    map<string, int> freq;
    for (int i=A; i<=B; i++) {
        for (int j=0; j+i<=s.size(); j++) {
            freq[s.substr(j, i)]++;
        }
    }

    map<int,vector<string>> rfreq;
    for (map<string,int>::iterator it=freq.begin(); it!=freq.end(); it++) {
        rfreq[it->SE].push_back(it->FI);
    }

    for (map<int,vector<string>>::reverse_iterator it=rfreq.rbegin(); it!=rfreq.rend(); it++) {
        cout << it->FI << endl;
        sort(it->SE.begin(), it->SE.end(), cmp);

        for (int i=0; i<it->SE.size(); i++) {
            if (i) cout << (i >= 6 && (i%6) == 0 ? '\n' : ' ');
            cout << it->SE[i];
        }
        cout << endl;
        if (--N == 0) {
            break;
        }
    }
}
    
