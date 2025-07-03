#include <iostream>
#include <bitset>
#include <cassert>
#include <cmath>

using namespace std;

inline double square(const double& x) {
    return x * x;
}

struct Color {
    double amount;
    double c, m, y;

    Color() {}

    Color(const Color& c1, const Color& c2) {
        amount = c1.amount + c2.amount;
        c = (c1.c * c1.amount + c2.c * c2.amount) / amount; 
        m = (c1.m * c1.amount + c2.m * c2.amount) / amount; 
        y = (c1.y * c1.amount + c2.y * c2.amount) / amount; 
    }

    double error(const Color& color) const {
        return sqrt(square(c - color.c) + square(m - color.m) + square(y - color.y));
    }
};

const int N = 20;
int K;
const int H = 1000;
int T;
int D;

struct Board {
    bitset<N * N> below, right;

    Board() {
        below.reset();
        right.reset();
    }

    friend ostream& operator<<(ostream& os, const Board& board) {
        for (int r = 0; r < N; ++r) {
            for (int c = 0; c < N - 1; ++c) {
                if (c) os << ' ';
                os << board.right[r * N + c];
            }
            os << '\n';
        }
        for (int r = 0; r < N - 1; ++r) {
            for (int c = 0; c < N; ++c) {
                if (c) os << ' ';
                os << board.below[r * N + c];
            }
            os << '\n';
        }

        return os;
    }
};

Color own[20];
Color target[H];

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int _N, _H;
    cin >> _N >> K >> _H >> T >> D;
    assert(N == _N);
    assert(H == _H);

    for (int k = 0; k < K; ++k) {
        cin >> own[k].c >> own[k].m >> own[k].y;
        own[k].amount = 1;
    }
    for (int h = 0; h < H; ++h) {
        cin >> target[h].c >> target[h].m >> target[h].y;
        target[h].amount = 1;
    }

    Board board;
    cout << board;
    double total_error = 0;
    for (int h = 0; h < H; ++h) {
        double best_err = 3;
        int best_idx = -1;
        for (int k = 0; k < K; ++k) {
            const double error = target[h].error(own[k]);
            if (best_err > error) {
                best_err = error;
                best_idx = k;
            }
        }
        cout << "1 0 0 " << best_idx << '\n';
        cout << "2 0 0\n";

        total_error += best_err;
    }

    const int score = 1 + round(total_error * 10000);

    cerr << score << endl;
}
