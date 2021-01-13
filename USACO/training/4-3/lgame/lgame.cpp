/*
ID: zhongbr1
TASK: lgame
LANG: C++14
*/

//lgame.cpp created at 12/26/20 12:52:13

#include <bits/stdc++.h>

using namespace std;

const int MN = 40005;

int N;
string dict[MN];

int val[26] = {2, 5, 4, 4, 1, 6, 5, 5, 1, 7, 6, 3, 5, 2, 3, 5, 7, 2, 1, 2, 4, 6, 6, 7, 5, 7};

bool find_in_dict(const string& s) {
    if (s.empty() || s[0] == ' ' || s.back() == ' ') return false;
    int space_pos = s.find(' ');
    if (space_pos == string::npos) {
        return binary_search(dict, dict+N, s);
    }
    string a = s.substr(0, space_pos);
    string b = s.substr(space_pos + 1);

    if (a > b) return false;

    return binary_search(dict, dict+N, a) && (b.empty() || binary_search(dict, dict+N, b));
}

int score(const string& s) {
    int ret = 0;
    for (int i=0; i<s.size(); ++i) {
        if (s[i] == ' ') continue;
        ret += val[s[i] - 'a'];
    }
    return ret;
}

int main() {
    ifstream fin("lgame.dict");
    for (N=0; N<MN; ++N) {
        fin >> dict[N];
        if (dict[N] == ".") break;
    }

    freopen("lgame.in", "r", stdin);
    freopen("lgame.out", "w", stdout);
    cin.tie(0)->sync_with_stdio(0);

    string s;
    cin >> s;

    int best = 0;
    set<string> ans;
    s.push_back(' ');
    sort(s.begin(), s.end());
    do {
        for (int i=0; i<s.size(); ++i) {
            if (find_in_dict(s.substr(i))) {
                int val = score(s.substr(i));
                if (best < val) {
                    best = val;
                    ans.clear();
                }
                if (best == val) {
                    ans.insert(s.substr(i));
                }
                break;
            }
        }
    } while (next_permutation(s.begin(), s.end()));

    cout << best << endl;
    for (const string& x: ans) {
        cout << x << '\n';
    }
}
