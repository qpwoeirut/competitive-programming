#include <iostream>
#include <algorithm>

using namespace std;

typedef long long ll;

const int MN = 1e6;

int N;
ll A[MN];

int main() {
    cin >> N;
    for (int i=0; i<N; ++i) {
        cin >> A[i];
    }
    sort(A, A+N);
    for (int i=0; i<N; ++i) {
        cout << A[i] << ' ';
    }
    cout << endl;
}
