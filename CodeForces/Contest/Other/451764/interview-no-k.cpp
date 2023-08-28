#include <bits/stdc++.h>

using namespace std;

constexpr float EPS = 1e-12;

constexpr float PASS_PRELIM_GOOD = 0.8;
constexpr float PASS_PRELIM_BAD = 0.2;
constexpr float PASS_GOOD_FULL = 0.9;
constexpr float PASS_BAD_FULL = 0.1;

constexpr int PRELIM_TIME = 20;
constexpr int FULL_TIME = 60;
constexpr int ACCEPT_TIME = 5;

mt19937 rng(8);  // technically we should also use uniform_int_distribution but should be close enough

class Interactor {  // whipping out the C++ abstract classes
public:
    Interactor(int _n) {
        n = _n;
        assert(n <= 100);

        time_spent = 0;
        idx = 0;
        selected = vector<int>();
    }
    virtual void reject() = 0;
    virtual int prelim() = 0;
    virtual int full() = 0;
    virtual void accept() = 0;
    virtual int get_k() = 0;
    virtual bool selected_ok() = 0;

    int n;
    int time_spent;
    int idx;
    vector<int> selected;

    float score() {
        assert(idx == n);
        const int g = (int)selected.size();
        if (g < 5) return 0;
        if (!selected_ok()) return 0;

        const int r = selected.back() - selected[0];
        return 100000.0 * floor(g * sqrt(sqrt(g))) / ((time_spent + 10) * (n - r) + 10);
    }
    int min_selected() {
        return selected.empty() ? n : selected[0];
    }
    int max_selected() {
        return selected.empty() ? -1 : selected.back();
    }
};

class SelfInteractor : public Interactor {
private:
    bitset<100> good;
public:
    SelfInteractor(int _n) : Interactor(_n) {
        vector<unsigned> p(n);
        for (int i = 0; i < n; ++i) {
            p[i] = rng() % 61;
        }
        sort(p.begin(), p.end());

        for (int i = 0; i < n; ++i) {
            good[i] = (rng() % 100) < p[i];
        }

        set<int> bad;
        while (bad.size() < 10) bad.insert(rng() % 100);
        for (int i: bad) {
            good[i] = false;
        }
    }
    void reject() {
        ++idx;
    }
    int prelim() {
        time_spent += PRELIM_TIME;

        const unsigned p_prelim = (unsigned)((good[idx] ? PASS_PRELIM_GOOD : PASS_PRELIM_BAD) * 10 + EPS);
        if (rng() % 10 < p_prelim) {
            return full();
        } else {
            ++idx;
            return 0;
        }
    }
    int full() {
        time_spent += FULL_TIME;

        const unsigned p_full = (unsigned)((good[idx] ? PASS_GOOD_FULL : PASS_BAD_FULL) * 10 + EPS);
        if (rng() % 10 < p_full) {
            selected.push_back(idx);
            ++idx;
            return 2;
        } else {
            ++idx;
            return 1;
        }
    }
    void accept() {
        time_spent += ACCEPT_TIME;

        selected.push_back(idx);
        ++idx;
    }
    int get_k() {
        if (idx != 50) {
            cerr << "WARNING: get_k called with idx=" << idx << endl;
        }
        int k = 0;
        for (int i = 0; i < n / 2; ++i) {
            k += !good[i];
        }
        return k;
    }
    bool selected_ok() {
        for (int s_idx: selected) {
            if (!good[s_idx]) return false;
        }
        return true;
    }
};

class GraderInteractor : public Interactor {
public:
    GraderInteractor(int _n) : Interactor(_n) {}
    void reject() {
        cout << 0 << endl;

        ++idx;
    }
    int prelim() {
        time_spent += PRELIM_TIME;

        cout << 1 << endl;

        string s;
        cin >> s;
        assert(cin.good());
        assert(s == "pass" || s == "fail");
        if (s != "pass") {
            ++idx;
            return 0;
        } else {
            time_spent += FULL_TIME;

            cin >> s;
            assert(s == "pass" || s == "fail");
            if (s != "pass") {
                ++idx;
                return 1;
            } else {
                selected.push_back(idx);
                ++idx;
                return 2;
            }
        }
    }
    int full() {
        time_spent += FULL_TIME;

        cout << 2 << endl;

        string s;
        cin >> s;
        assert(s == "pass" || s == "fail");
        assert(cin.good());
        if (s != "pass") {
            ++idx;
            return 1;
        } else {
            selected.push_back(idx);
            ++idx;
            return 2;
        }
    }
    void accept() {
        time_spent += ACCEPT_TIME;

        cout << 3 << endl;

        selected.push_back(idx);
        ++idx;
    }
    int get_k() {
        int k;
        cin >> k;
        assert(cin.good());
        return k;
    }
    bool selected_ok() {
        return true;  // we don't know, so just assume it's fine. this score won't be used anyway.
    }
};

constexpr int MN = 100;
constexpr int G_POW[MN + 1] = {  // floor(g * sqrt(sqrt(g)))
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
constexpr float SCORE_NUMER[MN + 1] = {
    0.0,
    20000.0, 40000.0, 60000.0, 100000.0, 140000.0, 180000.0, 220000.0, 260000.0, 300000.0, 340000.0,
    400000.0, 440000.0, 480000.0, 540000.0, 580000.0, 640000.0, 680000.0, 740000.0, 780000.0, 840000.0,
    880000.0, 940000.0, 1000000.0, 1060000.0, 1100000.0, 1160000.0, 1220000.0, 1280000.0, 1340000.0, 1400000.0,
    1460000.0, 1520000.0, 1580000.0, 1640000.0, 1700000.0, 1760000.0, 1820000.0, 1880000.0, 1940000.0, 2000000.0,
    2060000.0, 2120000.0, 2200000.0, 2260000.0, 2320000.0, 2380000.0, 2460000.0, 2520000.0, 2580000.0, 2640000.0,
    2720000.0, 2780000.0, 2860000.0, 2920000.0, 2980000.0, 3060000.0, 3120000.0, 3200000.0, 3260000.0, 3320000.0,
    3400000.0, 3460000.0, 3540000.0, 3620000.0, 3680000.0, 3760000.0, 3820000.0, 3900000.0, 3960000.0, 4040000.0,
    4120000.0, 4180000.0, 4260000.0, 4340000.0, 4400000.0, 4480000.0, 4560000.0, 4620000.0, 4700000.0, 4780000.0,
    4860000.0, 4920000.0, 5000000.0, 5080000.0, 5160000.0, 5220000.0, 5300000.0, 5380000.0, 5460000.0, 5540000.0,
    5620000.0, 5680000.0, 5760000.0, 5840000.0, 5920000.0, 6000000.0, 6080000.0, 6160000.0, 6240000.0, 6320000.0
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
constexpr array<float, MN> EXPECTED_P = {
    0.234969473, 0.7184972322, 1.3077802518, 1.9147896048, 2.5199108525, 3.1238354433, 3.7277245241, 4.3316791979, 4.9356430594, 5.539604129, 
    6.1435643999, 6.7475247476, 7.3514851458, 7.9554455446, 8.5594059407, 9.1633663366, 9.7673267327, 10.3712871287, 10.9752475248, 11.5792079208, 
    12.1831683168, 12.7871287129, 13.3910891089, 13.995049505, 14.599009901, 15.202970297, 15.8069306931, 16.4108910891, 17.0148514851, 17.6188118812, 
    18.2227722772, 18.8267326733, 19.4306930693, 20.0346534653, 20.6386138614, 21.2425742574, 21.8465346535, 22.4504950495, 23.0544554455, 23.6584158416, 
    24.2623762376, 24.8663366337, 25.4702970297, 26.0742574257, 26.6782178218, 27.2821782178, 27.8861386139, 28.4900990099, 29.0940594059, 29.698019802, 
    30.301980198, 30.9059405941, 31.5099009901, 32.1138613861, 32.7178217822, 33.3217821782, 33.9257425743, 34.5297029703, 35.1336633663, 35.7376237624, 
    36.3415841584, 36.9455445545, 37.5495049505, 38.1534653465, 38.7574257426, 39.3613861386, 39.9653465347, 40.5693069307, 41.1732673267, 41.7772277228, 
    42.3811881188, 42.9851485149, 43.5891089109, 44.1930693069, 44.797029703, 45.400990099, 46.004950495, 46.6089108911, 47.2128712871, 47.8168316832, 
    48.4207920792, 49.0247524752, 49.6287128713, 50.2326732673, 50.8366336634, 51.4405940593, 52.0445544554, 52.6485148542, 53.2524752524, 53.8564356001, 
    54.460395871, 55.0643569406, 55.6683208021, 56.2722754759, 56.8761645567, 57.4800891475, 58.0852103952, 58.6922197482, 59.2815027678, 59.765030527
};

consteval array<float, MN> to_prob(const array<float, MN>& arr) {
    array<float, MN> result;
    for (int i = 0; i < MN; ++i) result[i] = arr[i] / 100 * 0.9;
    return result;
}
constexpr array<float, MN> P_GOOD = to_prob(EXPECTED_P);

constexpr float PASS_PRELIM_PASS_STANDARD_GOOD = 0.8 * 0.9;
constexpr float FAIL_PRELIM_GOOD = 0.2;
constexpr float PASS_PRELIM_FAIL_STANDARD_GOOD = 0.8 * 0.1;
static_assert(abs(1 - (PASS_PRELIM_PASS_STANDARD_GOOD + FAIL_PRELIM_GOOD + PASS_PRELIM_FAIL_STANDARD_GOOD)) < EPS);

constexpr float PASS_PRELIM_PASS_STANDARD_BAD = 0.2 * 0.1;
constexpr float FAIL_PRELIM_BAD = 0.8;
constexpr float PASS_PRELIM_FAIL_STANDARD_BAD = 0.2 * 0.9;
static_assert(abs(1 - (PASS_PRELIM_PASS_STANDARD_BAD + FAIL_PRELIM_BAD + PASS_PRELIM_FAIL_STANDARD_BAD)) < EPS);

constexpr float PASS_STANDARD_GOOD = 0.9;
constexpr float FAIL_STANDARD_GOOD = 1 - PASS_STANDARD_GOOD;

constexpr float PASS_STANDARD_BAD = 0.1;
constexpr float FAIL_STANDARD_BAD = 1 - PASS_STANDARD_BAD;

consteval array<float, MN> calculate_p(const float p_good, const float p_bad) {
    array<float, MN> arr;
    for (int n = 0; n < MN; ++n) arr[n] = P_GOOD[n] * p_good + (1 - P_GOOD[n]) * p_bad;
    return arr;
}
constexpr array<float, MN> P_FAIL_PRELIM = calculate_p(FAIL_PRELIM_GOOD, FAIL_PRELIM_BAD);
constexpr array<float, MN> P_PASS_PRELIM_FAIL_STANDARD = calculate_p(PASS_PRELIM_FAIL_STANDARD_GOOD, PASS_PRELIM_FAIL_STANDARD_BAD);
constexpr array<float, MN> P_PASS_PRELIM_PASS_STANDARD = calculate_p(PASS_PRELIM_PASS_STANDARD_GOOD, PASS_PRELIM_PASS_STANDARD_BAD);

constexpr array<float, MN> P_FAIL_STANDARD = calculate_p(FAIL_STANDARD_GOOD, FAIL_STANDARD_BAD);
constexpr array<float, MN> P_PASS_STANDARD = calculate_p(PASS_STANDARD_GOOD, PASS_STANDARD_BAD);

consteval array<float, MN> calculate_p_is_good(const float p_good, const float p_bad) {
    array<float, MN> arr;
    for (int n = 0; n < MN; ++n) arr[n] = P_GOOD[n] * p_good / (P_GOOD[n] * p_good + (1 - P_GOOD[n]) * p_bad);
    return arr;
}
constexpr array<float, MN> P_GOOD_PASS_PRELIM_PASS_STANDARD = calculate_p_is_good(PASS_PRELIM_PASS_STANDARD_GOOD, PASS_PRELIM_PASS_STANDARD_BAD);
constexpr array<float, MN> P_GOOD_PASS_STANDARD = calculate_p_is_good(PASS_STANDARD_GOOD, PASS_STANDARD_BAD);

constexpr int SKIPS = 0;
constexpr int PASS = SKIPS;
constexpr int N_OFFSET = PASS;
static_assert(N_OFFSET >= PASS && PASS >= SKIPS);


constexpr int MAX_TIME = 1600;
constexpr int MAX_HIRES = 50;
constexpr int MN_RANGE = 100;
constexpr int MX_RANGE = 50;
float cache[(MN - N_OFFSET + 1) >> 1][MAX_TIME + 1][MAX_HIRES + 1][MN_RANGE + 1][MX_RANGE + 1]; // = expected score, assuming all candidates are good
int N;

float expectimax(const int n, const int time_spent, const int hires, const int mn, const int inv_mx, int& action) {
    if (hires + (N - n) < 5 || time_spent > MAX_TIME || hires > MAX_HIRES) return 0;
    if (n == N) {
        // inv_mx = N - mx - 1
        return SCORE_NUMER[hires] / ((time_spent + 2) * (mn + inv_mx + 1) + 2);
    }

    if (action != -1 && n >= N_OFFSET && ((n - N_OFFSET) & 1) && cache[(n - N_OFFSET) >> 1][time_spent][hires][mn][inv_mx] != 0) {
        return cache[(n - N_OFFSET) >> 1][time_spent][hires][mn][inv_mx];
    }
    action = 0;

    const int new_mn = min(mn, n);
    const int new_mx = min(inv_mx, N - n - 1);
    const float options[4] = {
        // reject immediately
        expectimax(n + 1, time_spent, hires, mn, inv_mx, action),

        // prelim and standard interview
        P_FAIL_PRELIM[n]               * expectimax(n + 1, time_spent + 4,  hires,     mn,     inv_mx, action) +
        P_PASS_PRELIM_FAIL_STANDARD[n] * expectimax(n + 1, time_spent + 16, hires,     mn,     inv_mx, action) +
        P_PASS_PRELIM_PASS_STANDARD[n] * expectimax(n + 1, time_spent + 16, hires + 1, new_mn, new_mx, action) * P_GOOD_PASS_PRELIM_PASS_STANDARD[n],

        // standard interview only
        P_FAIL_STANDARD[n] * expectimax(n + 1, time_spent + 12, hires,     mn,     inv_mx, action) +
        P_PASS_STANDARD[n] * expectimax(n + 1, time_spent + 12, hires + 1, new_mn, new_mx, action) * P_GOOD_PASS_STANDARD[n],

        // accept immediately
        expectimax(n + 1, time_spent + 1, hires + 1, new_mn, new_mx, action) * P_GOOD[n]
    };

    // prioritize actions 1 and 2 first
    if (options[1] >= options[0] && options[1] >= options[2] && options[1] >= options[3]) {
        action = 1;
    } else if (options[2] >= options[0] && options[2] >= options[3]) {
        action = 2;
    } else if (options[0] >= options[3]) {
        action = 0;
    } else {
        action = 3;
    }

    if (n >= N_OFFSET && ((n - N_OFFSET) & 1)) cache[(n - N_OFFSET) >> 1][time_spent][hires][mn][inv_mx] = options[action];
    return options[action];
}

float strategy(const unique_ptr<Interactor>& interactor) {
    int action = -1;
    //for (int i = PASS; i < PASS + 4; ++i) expectimax(i, 0, 0, i, MX_RANGE, action);  // for testing time

    string s;
    for (int i = 0; i < N; ++i) {
        if (i == 50) {
            // figure out how to use k later
            interactor->get_k();
        }

        //if (i < SKIPS) {
        //    interactor->reject();
        //} else if (interactor->selected.empty() && i + 10 < N) {
        //    interactor->prelim();
        //} else if (i < PASS && i + 10 < N) {
        //    interactor->reject();
        //} else {
            action = -1;
            const int mn = min(interactor->min_selected(), MN_RANGE);
            const int inv_mx = min(N - interactor->max_selected() - 1, MX_RANGE);
            float optimal_score = expectimax(i, interactor->time_spent / 5, interactor->selected.size(), mn, inv_mx, action);
            //cerr << i << ' ' << optimal_score << ' ' << interactor->time_spent / 5 << ' ' << interactor->selected.size() << endl;

            if (action == 0) {
                interactor->reject();
            } else if (action == 1) {
                interactor->prelim();
            } else if (action == 2) {
                interactor->full();
            } else if (action == 3) {
                interactor->accept();
            }
        //}
    }
    return interactor->score();
}

constexpr int TESTS = 0; //10000000;
array<double, 8> stats_of(const array<double, TESTS>& scores) {
    double sum = 0;
    for (double x: scores) {
        sum += x;
    }
    double mean = sum / scores.size();

    double variance = 0;
    for (double x: scores) {
        variance += (x - mean) * (x - mean);
    }
    double stddev = sqrt(variance / scores.size());
    double stderror = sqrt(variance) / scores.size();

    array<double, TESTS> tmp(scores);
    sort(tmp.begin(), tmp.end());
    // quartiles are approximate, should be good enough
    return {mean, stddev, stderror, *min_element(scores.begin(), scores.end()), tmp[TESTS / 4], tmp[TESTS / 2], tmp[3 * TESTS / 4], *max_element(scores.begin(), scores.end())};
}

string to_string(const array<double, 8>& arr) {
    string s = to_string(arr[0]);
    for (int i = 1; i < (int)arr.size(); ++i) s += ", " + to_string(arr[i]);
    return s;
}

array<double, TESTS> scores, mn, second, mx, hires, times;  // declaring locally causes crash on my computer
void test() {
    N = 100;
    for (int t = 0; t < TESTS; ++t) {
        unique_ptr<Interactor> interactor = make_unique<SelfInteractor>(N);
        scores[t] = strategy(interactor);
        mn[t] = interactor->min_selected();
        second[t] = interactor->selected[1];
        mx[t] = interactor->max_selected();
        hires[t] = interactor->selected.size();
        times[t] = interactor->time_spent / 5;
        if ((t * 10) % TESTS == 0) cout << t << endl;
    }
    cout << fixed << setprecision(6);
    cout << "TESTS = " << TESTS << endl;
    cout << "MAX_TIME = " << MAX_TIME << ", MAX_HIRES = " << MAX_HIRES << ", MN_RANGE = " << MN_RANGE << ", MX_RANGE = " << MX_RANGE << endl;
    cout << "SKIPS = " << SKIPS << ", PASS = " << PASS << ", " << "N_OFFSET = " << N_OFFSET << endl;
    cout << "score mean, stddev, stderr, min, q1, med, q3, max: " << to_string(stats_of(scores)) << endl;
    cout << "min   mean, stddev, stderr, min, q1, med, q3, max: " << to_string(stats_of(mn)) << endl;
    cout << "2nd   mean, stddev, stderr, min, q1, med, q3, max: " << to_string(stats_of(second)) << endl;
    cout << "max   mean, stddev, stderr, min, q1, med, q3, max: " << to_string(stats_of(mx)) << endl;
    cout << "hires mean, stddev, stderr, min, q1, med, q3, max: " << to_string(stats_of(hires)) << endl;
    cout << "times mean, stddev, stderr, min, q1, med, q3, max: " << to_string(stats_of(times)) << endl;
    /*
    TESTS = 10000000
    MAX_TIME = 900, MAX_HIRES = 21, MN_RANGE = 43, MX_RANGE = 5
    SKIPS = 0, PASS = 0, N_OFFSET = 0
    score mean, stddev, stderr, min, q1, med, q3, max: 37.367548, 73.494189, 0.023241, 0.000000, 0.000000, 13.504726, 50.597977, 2028.985474
    min   mean, stddev, stderr, min, q1, med, q3, max: 15.490889, 10.028453, 0.003171, 0.000000, 8.000000, 14.000000, 22.000000, 90.000000
    2nd   mean, stddev, stderr, min, q1, med, q3, max: 74.649563, 4.524259, 0.001431, 62.000000, 71.000000, 74.000000, 78.000000, 96.000000
    max   mean, stddev, stderr, min, q1, med, q3, max: 97.659988, 1.887403, 0.000597, 74.000000, 97.000000, 98.000000, 99.000000, 99.000000
    hires mean, stddev, stderr, min, q1, med, q3, max: 9.848859, 2.581195, 0.000816, 5.000000, 8.000000, 10.000000, 12.000000, 21.000000
    times mean, stddev, stderr, min, q1, med, q3, max: 360.198766, 116.500981, 0.036841, 65.000000, 284.000000, 356.000000, 440.000000, 896.000000

    SKIPS = 1, PASS = 1, N_OFFSET = 1
    score mean, stddev, stderr, min, q1, med, q3, max: 37.876399, 65.564167, 0.020733, 0.000000, 0.000000, 16.772270, 52.238808, 972.222229
    min   mean, stddev, stderr, min, q1, med, q3, max: 15.827312, 9.866441, 0.003120, 1.000000, 8.000000, 14.000000, 22.000000, 80.000000
    2nd   mean, stddev, stderr, min, q1, med, q3, max: 74.817087, 4.465456, 0.001412, 62.000000, 72.000000, 75.000000, 78.000000, 96.000000
    max   mean, stddev, stderr, min, q1, med, q3, max: 97.645975, 1.897839, 0.000600, 74.000000, 97.000000, 98.000000, 99.000000, 99.000000
    hires mean, stddev, stderr, min, q1, med, q3, max: 9.770697, 2.558719, 0.000809, 5.000000, 8.000000, 10.000000, 12.000000, 21.000000
    times mean, stddev, stderr, min, q1, med, q3, max: 353.862395, 114.935085, 0.036346, 69.000000, 276.000000, 352.000000, 432.000000, 896.000000

    SKIPS = 2, PASS = 2, N_OFFSET = 2
    score mean, stddev, stderr, min, q1, med, q3, max: 37.869114, 59.449626, 0.018800, 0.000000, 0.000000, 19.120459, 53.705692, 662.650574
    min   mean, stddev, stderr, min, q1, med, q3, max: 16.192598, 9.702649, 0.003068, 2.000000, 9.000000, 15.000000, 22.000000, 82.000000
    2nd   mean, stddev, stderr, min, q1, med, q3, max: 75.006618, 4.435562, 0.001403, 62.000000, 72.000000, 75.000000, 78.000000, 96.000000
    max   mean, stddev, stderr, min, q1, med, q3, max: 97.635323, 1.906271, 0.000603, 74.000000, 97.000000, 98.000000, 99.000000, 99.000000
    hires mean, stddev, stderr, min, q1, med, q3, max: 9.688665, 2.538841, 0.000803, 5.000000, 8.000000, 10.000000, 11.000000, 21.000000
    times mean, stddev, stderr, min, q1, med, q3, max: 347.514873, 113.671247, 0.035946, 81.000000, 268.000000, 344.000000, 424.000000, 900.000000


    TESTS = 10000000
    MAX_TIME = 1200, MAX_HIRES = 30, MN_RANGE = 80, MX_RANGE = 10
    SKIPS = 0, PASS = 0, N_OFFSET = 0
    score mean, stddev, stderr, min, q1, med, q3, max: 37.910280, 65.620706, 0.020751, 0.000000, 0.000000, 16.761217, 52.323792, 972.222229
    min   mean, stddev, stderr, min, q1, med, q3, max: 15.829077, 9.868455, 0.003121, 1.000000, 8.000000, 14.000000, 22.000000, 85.000000
    2nd   mean, stddev, stderr, min, q1, med, q3, max: 74.904761, 4.482504, 0.001417, 61.000000, 72.000000, 75.000000, 78.000000, 96.000000
    max   mean, stddev, stderr, min, q1, med, q3, max: 97.685978, 1.809383, 0.000572, 72.000000, 97.000000, 98.000000, 99.000000, 99.000000
    hires mean, stddev, stderr, min, q1, med, q3, max: 9.757145, 2.567173, 0.000812, 5.000000, 8.000000, 10.000000, 11.000000, 23.000000
    times mean, stddev, stderr, min, q1, med, q3, max: 353.271139, 115.160336, 0.036417, 69.000000, 276.000000, 352.000000, 432.000000, 936.000000

    MAX_TIME = 1600, MAX_HIRES = 50, MN_RANGE = 100, MX_RANGE = 50
    SKIPS = 0, PASS = 0, N_OFFSET = 0
    score mean, stddev, stderr, min, q1, med, q3, max: 37.859895, 65.510876, 0.020716, 0.000000, 0.000000, 16.702856, 52.256531, 972.222229
    min   mean, stddev, stderr, min, q1, med, q3, max: 15.834961, 9.872974, 0.003122, 1.000000, 8.000000, 14.000000, 22.000000, 86.000000
    2nd   mean, stddev, stderr, min, q1, med, q3, max: 74.915249, 4.488557, 0.001419, 61.000000, 72.000000, 75.000000, 78.000000, 96.000000
    max   mean, stddev, stderr, min, q1, med, q3, max: 97.687680, 1.803812, 0.000570, 76.000000, 97.000000, 98.000000, 99.000000, 99.000000
    hires mean, stddev, stderr, min, q1, med, q3, max: 9.756430, 2.567385, 0.000812, 5.000000, 8.000000, 10.000000, 11.000000, 23.000000
    times mean, stddev, stderr, min, q1, med, q3, max: 353.277775, 115.171227, 0.036420, 69.000000, 276.000000, 352.000000, 432.000000, 952.000000
    */
}

int main() {
    if (TESTS != 0) {
        test();
        return 0;
    }

    cin >> N;
    strategy(make_unique<GraderInteractor>(N));
}

