#include <bits/stdc++.h>

#define USING_TESTER

#include "7_rotate_components.cpp"

const int TESTS = 40;

string zfill(int n, int width) {
    const string s = to_string(n);
    return string(max(0, width - (int)(s.size())), '0') + s;
}

int run_test(int test_number) {
    freopen(("in/" + zfill(test_number, 4) + ".txt").c_str(), "r", stdin);
    return solve();
}

template <class T> array<long double, 8> stats_of(const array<T, TESTS> arr) {
    long double sum = 0;
    for (const T x: arr) sum += x;
    long double mean = sum / arr.size();

    long double variance = 0;
    for (const T x: arr) {
        variance += (x - mean) * (x - mean);
    }
    long double stddev = sqrt(variance / arr.size());
    long double stderror = sqrt(variance) / arr.size();

    array<T, TESTS> tmp(arr);
    sort(tmp.begin(), tmp.end());
    // quartiles are approximate, should be good enough
    return {mean, stddev, stderror, *min_element(arr.begin(), arr.end()), tmp[TESTS / 4], tmp[TESTS / 2], tmp[3 * TESTS / 4], *max_element(arr.begin(), arr.end())};
}

array<int, TESTS> score;

int main() {
    for (COMP_RANGE=1; COMP_RANGE<=50; ++COMP_RANGE) {
        for (EARLY_PLANT = 0; EARLY_PLANT <= 5; ++EARLY_PLANT) {
            for (EARLY_FACTOR = 15; EARLY_FACTOR <= 30; ++EARLY_FACTOR) {
                cout << "TESTS = " << TESTS << ". COMP_RANGE = " << COMP_RANGE << ". EARLY_PLANT = " << EARLY_PLANT << ". EARLY_FACTOR = " << EARLY_FACTOR << ".\n";
                for (int t = 0; t < TESTS; ++t) score[t] = run_test(t);
                cout << "scores mean, stddev, stderr, min, q1, med, q3, max: " << to_string(stats_of(score)) << endl;

                if (EARLY_PLANT == 0) break;
            }
        }
        //cout << "TESTS = " << TESTS << ". COMP_RANGE = " << COMP_RANGE << ".\n";
        //for (int t = 0; t < TESTS; ++t) score[t] = run_test(t);
        //cout << "scores mean, stddev, stderr, min, q1, med, q3, max: " << to_string(stats_of(score)) << endl;
    }
}
