#include <bits/stdc++.h>

using namespace std;

const double EPS = 1e-12;

const double GOOD_PASS_PRELIM = 0.8;
const double BAD_PASS_PRELIM = 0.2;
const double GOOD_PASS_FULL = 0.9;
const double BAD_PASS_FULL = 0.1;

const int PRELIM_TIME = 20;
const int FULL_TIME = 60;

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
    virtual int get_k() = 0;
    virtual bool selected_ok() = 0;

    int n;
    int time_spent;
    int idx;
    vector<int> selected;

    double score() {
        assert(idx == n);
        const int g = selected.size();
        if (g < 5) return 0;
        if (!selected_ok()) return 0;

        const int r = selected.back() - selected[0];
        return 100000.0 * floor(g * sqrt(sqrt(g))) / ((time_spent + 10) * (n - r) + 10);
    }
};

class SelfInteractor : public Interactor {
private:
    vector<unsigned> p;
    bitset<100> good;
public:
    SelfInteractor(int _n) : Interactor(_n) {
        p = vector<unsigned>(n);
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

        const unsigned p_prelim = (good[idx] ? GOOD_PASS_PRELIM : BAD_PASS_PRELIM) * 10 + EPS;
        if (rng() % 10 < p_prelim) {
            return full();
        } else {
            ++idx;
            return 0;
        }
    }
    int full() {
        time_spent += FULL_TIME;

        const unsigned p_full = (good[idx] ? GOOD_PASS_FULL : BAD_PASS_FULL) * 10 + EPS;
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
        selected.push_back(idx);
        ++idx;
    }
    int get_k() {
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
        if (s == "fail") {
            ++idx;
            return 0;
        }
        else {
            time_spent += FULL_TIME;

            cin >> s;
            if (s == "fail") {
                ++idx;
                return 1;
            }
        }

        ++idx;
        return 2;
    }
    int full() {
        time_spent += FULL_TIME;

        cout << 2 << endl;

        string s;
        cin >> s;
        if (s == "fail") {
            ++idx;
            return 1;
        } else {
            selected.push_back(idx);
            ++idx;
            return 2;
        }
    }
    void accept() {
        cout << 3 << endl;

        selected.push_back(idx);
        ++idx;
    }
    int get_k() {
        int k;
        cin >> k;
        return k;
    }
    bool selected_ok() {
        return true;  // we don't know, so just assume it's fine. this score won't be used anyway.
    }
};

double strategy(int n, const unique_ptr<Interactor> interactor, const int SKIP = 1, const int SPAM_HIRES = 24) {
    int mn = n, mx = -1;
    double p_all_good = 1;

    double base_p_good = 0;
    int base_idx = 0;
    for (int i = 0; i < n; ++i) {
        if (i < SKIP) {
            interactor->reject();
        } else if (i >= n - SPAM_HIRES || mn == n) {
            int result = interactor->prelim();
            if (result == 2) {
                double p_good = base_p_good + ((60 - base_p_good) * (i - base_idx) / (n - base_idx));
                p_all_good *= p_good;

                mn = min(mn, i);
                mx = max(mx, i);
            }
        } else {
            interactor->reject();
        }

        if (i == 49) {
            double k = interactor->get_k();
            double average = k / 50;
            base_p_good = average * 2;
            base_idx = 50;
        }
    }

    return interactor->score();
}


double sum_of(const vector<double>& scores) {
    double sum = 0;
    for (double x: scores) sum += x;
    return sum;
}

const int TESTS = 100000;
vector<double> test_strategy(const int SKIPS, const int SPAM_HIRES) {
    const int n = 100;

    vector<double> scores(TESTS);
    for (int i = 0; i < TESTS; ++i) {
        scores[i] = strategy(n, make_unique<SelfInteractor>(n), SKIPS, SPAM_HIRES);
    }
    return scores;
}

void test_specific() {
    cerr << "TESTS = " << TESTS << endl;

    const int SKIPS = 0;

    ofstream fout("specific-" + to_string(TESTS) + ".txt");
    for (int SPAM_HIRES = 35; SPAM_HIRES <= 70; ++SPAM_HIRES) {
        cerr << SPAM_HIRES << endl;
        const vector<double> scores = test_strategy(SKIPS, SPAM_HIRES);
        fout << SPAM_HIRES << ' ' << sum_of(scores) / TESTS << endl;;
    }
    fout.close();
}


void test_all() {
    cerr << "TESTS = " << TESTS << endl;

    const int S = 6;
    const int H0 = 22;
    const int H = 28;
    vector<vector<double>> sums(S + 1, vector<double>(H + 1));
    for (int SKIPS = 0; SKIPS <= S; ++SKIPS) {
        cerr << SKIPS << endl;
        for (int SPAM_HIRES = H0; SPAM_HIRES + SKIPS <= 100 && SPAM_HIRES <= H; ++SPAM_HIRES) {
            const vector<double> scores = test_strategy(SKIPS, SPAM_HIRES);
            //cerr << SKIPS << ' ' << SPAM_HIRES << ' ' << sum_of(scores) / TESTS << endl;
            sums[SKIPS][SPAM_HIRES] = sum_of(scores) / TESTS;
        }
    }

    ofstream fout("table-" + to_string(TESTS) + ".csv");
    fout << 'x';
    for (int i = H0; i <= H; ++i) {
        fout << ", " << i;
    }
    fout << endl;

    for (int s = 0; s <= S; ++s) {
        fout << s;
        for (int h = H0; h <= H; ++h) {
            fout << ", " << sums[s][h];
        }
        fout << endl;
    }
    fout.close();
}

int main() {
    //test_all(); return 0;
    //test_specific(); return 0;

    int n;
    cin >> n;

    strategy(n, make_unique<GraderInteractor>(n));
}
