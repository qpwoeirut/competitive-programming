#include <bits/stdc++.h>

using namespace std;

using ll=long long;
using dbl=long double;

constexpr int N = 100;
constexpr int progress = 1e8;

int main() {
    mt19937 rng(8);    
    uniform_int_distribution<> p_dist(0, 60), pct_dist(0, 99);

    int p[N];
    dbl expected[N+1][N];
    ll ct[N+1];

    bitset<N> good, available;
    for (int i = 0; i < N; ++i) available[i] = true;
    int overrides = 0;

    for (ll trials = 1; true; ++trials) {
        for (int i = 0; i < N; ++i) p[i] = p_dist(rng);
        sort(p, p+N);
        
        for (int i = 0; i < N; ++i) good[i] = pct_dist(rng) < p[i];

        overrides = 0;
        while (overrides < 10) {
            const int idx = pct_dist(rng);
            overrides += available[idx];
            available[idx] = false;
        }
        for (int i = 0; i < N; ++i) {
            good[i] = good[i] & available[i];
            available[i] = true;
        }

        int k = 0;
        for (int i = 0; i < N/2; ++i) k += !good[i];

        ++ct[k];
        for (int i = 0; i < N; ++i) expected[k][i] += (dbl)p[i] / 100 * 0.9;

        if (trials % progress == 0) {
            cout << trials << endl;
            ofstream fout("expected_values-" + to_string(trials) + ".txt");
            for (int k = 0; k <= N; ++k) {
                if (ct[k] == 0) continue;
                fout << k << " (" << ct[k] << "):";
                for (int i = 0; i < N; ++i) fout << (i ? ", " : " {") << (double)expected[k][i] / ct[k];
                fout << "},\n";
            }
            fout << "\n\n";
            for (int k = 0; k <= N; ++k) {
                if (ct[k] == 0) continue;
                for (int i = 0; i < N; ++i) fout << (i ? ", " : " {") << (double)expected[k][i] / ct[k];
                fout << "},\n";
            }
            fout.close();
        }
    }

}

/*
g++-12 -std=c++20 -I ~/CompetitiveProgramming/setupFiles -Ofast -funroll-loops -march=native -mtune=native -Wall expected_values.cpp -o expected_values.out
*/
