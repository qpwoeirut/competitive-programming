/*
ID: zhongbr1
TASK: humble
LANG: C++11
*/

#include <bits/stdc++.h>

using namespace std;

#define FI first
#define SE second

typedef long long ll;

vector<ll> nums;
set<ll> q;
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    freopen("humble.in", "r", stdin);
    freopen("humble.out", "w", stdout);

    int K, N;
    cin >> K >> N;

    for (int i=0; i<K; i++) {
        int tmp;
        cin >> tmp;
        if (tmp > 1) {
            nums.push_back(tmp);
        }
    }
    for (int i=0; i<nums.size(); i++) {
        q.insert(nums[i]);
    }

    while (q.size() > 0) {
        ll cur = *q.begin();
        q.erase(q.begin());
    
        if (--N == 0) {
            cout << cur << endl;
            return 0;
        }

        for (int i=0; i<nums.size(); i++) {
            if (q.size() < N || cur * nums[i] < *q.rbegin()) {
                q.insert(cur * nums[i]);
            }
        }
        while (q.size() > N) {
            set<ll>::iterator it=q.end();
            q.erase(--it);
        }
    }

    assert(false);
}
