//reverseprint.cpp created at 11/12/20 11:48:22

#include <bits/stdc++.h>

using namespace std;

int N;
int main() {
    freopen("reverseprint.in", "r", stdin);
    freopen("reverseprint.out", "w", stdout);

    cin.tie(0)->sync_with_stdio(0);

    cin >> N;
    vector<int> nums(N);
    for (int i=0; i<N; ++i) {
        cin >> nums[i];
    }
    reverse(nums.begin(), nums.end());
    for (int i=0; i<N; ++i) {
        cout << nums[i] << '\n';
    }
}

