//acc7p2.cpp created at 04/04/21 12:51:17

#include <bits/stdc++.h>

using namespace std;

const int MN = 5003;

int N;
int A[MN];
int pos[MN];

mt19937 rng(8);

int query() {
    for (int i=0; i<N; ++i) {
        if (i) cout << ' ';
        cout << A[i];
    }
    cout << '\n';
    cout.flush();

    int resp;
    cin >> resp;
    return resp;
}

void swp(const int i, const int j) {
    pos[A[i]] = j;
    pos[A[j]] = i;
    swap(A[i], A[j]);
}

int main() {
    cin >> N;

    set<int> idxs;
    for (int i=0; i<N; ++i) {
        A[i] = i+1;
        idxs.insert(i);
    }

    map<int,int> mp;

    shuffle(A, A+N, rng);
    for (int i=0; i<N; ++i) {
        pos[A[i]] = i;
    }

    for (int i=0; i<20; ++i) {
        int t = query();
        
        if (t == 0) {
            return 0;
        } else if (t == -1) {
            assert(i == 19);

            return 0;
        } else {
            --t;

            idxs.erase(t);

            if (idxs.empty()) {
                assert(mp.size() > 0);
                swp(pos[mp.begin()->first], t);
            } else {
                auto it = idxs.lower_bound(rng());
                if (it == idxs.end()) it = idxs.begin();

                swap(A[*it], A[t]);
                idxs.erase(it);
            }

            mp[A[i]] = t;
        }
    }
}

