#include "subarray.h"
#include "SubarraySort.cpp"
#include <iostream>

using namespace std;

static const int MAX_N = (int)4e6;

static int P[MAX_N];

int main() {
  int N;
  cin >> N;
  for (int i = 0; i < N; ++i) {
    cin >> P[i];
  }
  cout << solve(N, P) << endl;
}

