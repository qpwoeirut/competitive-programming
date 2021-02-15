//distinct_numbers.cpp created at 09/19/20 19:42:57

#include <bits/stdc++.h>

using namespace std;

int N;
set<int> nums;
int main() {
    cin >> N;

    for (int i=0; i<N; ++i) {
        int x;
        cin >> x;
        nums.insert(x);
    }

    cout << nums.size() << endl;
}
