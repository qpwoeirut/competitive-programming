#include <bits/stdc++.h>

using namespace std;

constexpr int MN = 101;
constexpr int G_POW[MN] = {  // floor(g * sqrt(sqrt(g)))
    0,
    1, 2, 3, 5, 7, 9, 11, 13, 15, 17,
    20, 22, 24, 27, 29, 32, 34, 37, 39, 42,
    44, 47, 50, 53, 55, 58, 61, 64, 67, 70,
    73, 76, 79, 82, 85, 88, 91, 94, 97, 100,
    103, 106, 110, 113, 116, 119, 123, 126, 129, 132,
    136, 139, 143, 146, 149, 153, 156, 160, 163, 166,
    170, 173, 177, 181, 184, 188, 191, 195, 198, 202,
    206, 209, 213, 217, 220, 224, 228, 231, 235, 239,
    243, 246, 250, 254, 258, 261, 265, 269, 273, 277,
    281, 284, 288, 292, 296, 300, 304, 308, 312, 316
};

/*
def prob(x, r, n, k):
    p = (x + 1) / (n + 1)
    if p >= 1:
        return 1
    if p <= 0:
        return 0
    return sum([comb(k, i) * p**i * (1-p)**(k-i) for i in range(r, k+1)])
def values(n, k):
    return [sum([(prob(x, r, n, k) - prob(x - 1, r, n, k)) * x for x in range(n + 1)]) for r in range(1, k+1)]
*/
constexpr double EXPECTED_P[100] = {
    0.234969, 0.718497, 1.30778, 1.91479, 2.519911, 3.123835, 3.727725, 4.331679, 4.935643, 5.539604,
    6.143564, 6.747525, 7.351485, 7.955446, 8.559406, 9.163366, 9.767327, 10.371287, 10.975248, 11.579208,
    12.183168, 12.787129, 13.391089, 13.99505, 14.59901, 15.20297, 15.806931, 16.410891, 17.014851, 17.618812,
    18.222772, 18.826733, 19.430693, 20.034653, 20.638614, 21.242574, 21.846535, 22.450495, 23.054455, 23.658416,
    24.262376, 24.866337, 25.470297, 26.074257, 26.678218, 27.282178, 27.886139, 28.490099, 29.094059, 29.69802,
    30.30198, 30.905941, 31.509901, 32.113861, 32.717822, 33.321782, 33.925743, 34.529703, 35.133663, 35.737624,
    36.341584, 36.945545, 37.549505, 38.153465, 38.757426, 39.361386, 39.965347, 40.569307, 41.173267, 41.777228,
    42.381188, 42.985149, 43.589109, 44.193069, 44.79703, 45.40099, 46.00495, 46.608911, 47.212871, 47.816832,
    48.420792, 49.024752, 49.628713, 50.232673, 50.836634, 51.440594, 52.044554, 52.648515, 53.252475, 53.856436,
    54.460396, 55.064357, 55.668321, 56.272275, 56.876165, 57.480089, 58.08521, 58.69222, 59.281503, 59.765031
};


constexpr double PASS_PRELIM_PASS_STANDARD_GOOD = 0.8 * 0.9;
constexpr double FAIL_PRELIM_GOOD = 0.2;
constexpr double PASS_PRELIM_FAIL_STANDARD_GOOD = 0.8 * 0.1;
static_assert(abs(1 - (PASS_PRELIM_PASS_STANDARD_GOOD + FAIL_PRELIM_GOOD + PASS_PRELIM_FAIL_STANDARD_GOOD)) < 1e-12);

constexpr double PASS_PRELIM_PASS_STANDARD_BAD = 0.2 * 0.1;
constexpr double FAIL_PRELIM_BAD = 0.8;
constexpr double PASS_PRELIM_FAIL_STANDARD_BAD = 0.2 * 0.9;
static_assert(abs(1 - (PASS_PRELIM_PASS_STANDARD_BAD + FAIL_PRELIM_BAD + PASS_PRELIM_FAIL_STANDARD_BAD)) < 1e-12);


constexpr double PASS_STANDARD_GOOD = 0.9;
constexpr double FAIL_STANDARD_GOOD = 1 - PASS_STANDARD_GOOD;

constexpr double PASS_STANDARD_BAD = 0.1;
constexpr double FAIL_STANDARD_BAD = 1 - PASS_STANDARD_BAD;

double p_good_given_step(int n, int step) {
    const double p_good = (EXPECTED_P[n] / 100) * 0.9;
    if (step == 0) {
        return p_good;
    } else if (step == 1) {
        return p_good * PASS_STANDARD_GOOD / (p_good * PASS_STANDARD_GOOD + (1 - p_good) * PASS_STANDARD_BAD);
    } else if (step == 2) {
        return p_good * PASS_PRELIM_PASS_STANDARD_GOOD / (p_good * PASS_PRELIM_PASS_STANDARD_GOOD + (1 - p_good) * PASS_PRELIM_PASS_STANDARD_BAD);
    } else assert(0);
}

// [candidates left, time spent / 5, hires] = expected score, assuming all candidates are good
double cache[MN][16 * MN][MN];
int N;

double expectimax(int n, int time_spent, int hires, int& action) {
    if (hires + (N - n) < 5) return 0;
    if (n == N) {
        // n - (mx - mn) is factored in already; extra +10 term is approximated to 0.7 because yes
        return (20000.0 * G_POW[hires] / ((time_spent + 2) + 0.7));
    }

    if (action != -1 && cache[n][time_spent][hires] != 0) {
        return cache[n][time_spent][hires];
    }
    action = 0;

    const double r_factor = (hires == 0) ? 1.0 / (n + 3) : 1;  // approximate mx as N - 2 and then zero-index
    const double p_good = (EXPECTED_P[n] / 100) * 0.9;
    double options[4] = {
        // reject immediately
        expectimax(n + 1, time_spent, hires, action),

        // prelim and standard interview
        (p_good * FAIL_PRELIM_GOOD               + (1 - p_good) * FAIL_PRELIM_BAD              ) * expectimax(n + 1, time_spent + 4,  hires,     action) +
        (p_good * PASS_PRELIM_FAIL_STANDARD_GOOD + (1 - p_good) * PASS_PRELIM_FAIL_STANDARD_BAD) * expectimax(n + 1, time_spent + 16, hires,     action) +
        (p_good * PASS_PRELIM_PASS_STANDARD_GOOD + (1 - p_good) * PASS_PRELIM_PASS_STANDARD_BAD) * expectimax(n + 1, time_spent + 16, hires + 1, action) * p_good_given_step(n, 2) * r_factor,

        // standard interview only
        (p_good * FAIL_STANDARD_GOOD + (1 - p_good) * FAIL_STANDARD_BAD) * expectimax(n + 1, time_spent + 12, hires,     action) +
        (p_good * PASS_STANDARD_GOOD + (1 - p_good) * PASS_STANDARD_BAD) * expectimax(n + 1, time_spent + 12, hires + 1, action) * p_good_given_step(n, 1) * r_factor,

        // accept immediately
        expectimax(n + 1, time_spent + 1, hires + 1, action) * p_good_given_step(n, 0) * r_factor
    };

    // prioritize actions 1 and 2 first
    if (options[1] >= options[0] && options[1] >= options[2] && options[1] >= options[3]) {
        action = 1;
    } else if (options[2] >= options[0] && options[2] >= options[1] && options[2] >= options[3]) {
        action = 2;
    } else if (options[0] >= options[1] && options[0] >= options[2] && options[0] >= options[3]) {
        action = 0;
    } else {
        action = 3;
    }

    return cache[n][time_spent][hires] = options[action];
}

int main() {
    cin >> N;

    int time_spent = 0;
    int zero_step = 0, one_step = 0, two_step = 0;
    string s;
    for (int i = 0; i < N; ++i) {
        int action = -1;
        double optimal_score = expectimax(i, time_spent, zero_step + one_step + two_step, action);
        cerr << i << ' ' << optimal_score << ' ' << time_spent << ' ' << zero_step << ' ' << one_step << ' ' << two_step << endl;

        cout << action << endl;

        if (action == 1) {
            time_spent += 4;

            cin >> s;
            if (s == "pass") {
                time_spent += 12;

                cin >> s;
                two_step += s == "pass";
            }
        } else if (action == 2) {
            time_spent += 12;

            cin >> s;
            one_step += s == "pass";
        } else if (action == 3) {
            ++time_spent;
            ++zero_step;
        }
    }
}

