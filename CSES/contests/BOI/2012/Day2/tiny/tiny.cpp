//tiny.cpp created at 02/23/21 20:52:40

#include <bits/stdc++.h>

using namespace std;

const int MN = 100005;
const int INIT = 1001001001;

int N;
int A[MN];
bitset<9> board[10];

const bool tp[9][3][3] = {
    {{0, 0, 0},
     {0, 0, 0},
     {1, 0, 0}},
    {{0, 0, 0},
     {1, 0, 0},
     {1, 0, 0}},
    {{0, 0, 0},
     {0, 0, 0},
     {1, 1, 0}},
    {{1, 0, 0},
     {1, 0, 0},
     {1, 0, 0}},
    {{0, 0, 0},
     {0, 0, 0},
     {1, 1, 1}},
    {{0, 0, 0},
     {1, 0, 0},
     {1, 1, 0}},
    {{0, 0, 0},
     {0, 1, 0},
     {1, 1, 0}},
    {{0, 0, 0},
     {1, 1, 0},
     {1, 0, 0}},
    {{0, 0, 0},
     {1, 1, 0},
     {0, 1, 0}},
};
const int lr[9][3] = {
    {0, -1, -1},
    {0, -1, -1},
    {0,  0, -1},
    {0, -1, -1},
    {0,  0,  0},
    {0,  0, -1},
    {0,  0, -1},
    {0,  1, -1},
    {1,  0, -1},
};
const int height[9] = {1, 2, 1, 3, 1, 2, 2, 2, 2};
const int width[9]  = {1, 1, 2 ,1 ,3, 2, 2, 2, 2};

void remove_full() {
    for (int i=0; i<9; ++i) {
        if (board[i].count() == 9) {
            board[i].reset();
            for (int j=i; j>0; --j) {
                swap(board[j-1], board[j]);
            }
        }
    }
}

void print_row(const int i) { string s = board[i].to_string(); reverse(s.begin(), s.end()); cerr << s << '\n'; }
void print() { for (int i=0; i<9; ++i) { print_row(i); } cerr << endl; }

vector<int> rp, cp;
bool place_piece(const int p, const int col, const bool rem=true) {
    assert(0 <= p && p < 9);
    assert(0 <= col && col < 9);

    rp.clear(); cp.clear();
    for (int i=0; i<=9; ++i) {
        for (int j=0; j<3; ++j) {
            if (lr[p][j] != -1 && board[i - lr[p][j]][col + j]) {
                if (i < height[p]) return false;
                
                for (int k=0; k<3; ++k) {
                    for (int l=0; l<3; ++l) {
                        if (tp[p][k][l]) {
                            assert(board[i-3+k][col+l] == false);
                            board[i-3+k][col+l] = true;
                            rp.push_back(i - 3 + k);
                            cp.push_back(col + l);
                        }
                    }
                }

                if (rem) remove_full();
                return true;
            }
        }
    }
    assert(false);
}

const string TASK = "5";

int bestv[9], bestc[9];
void find_spot(const int p) {
    fill(bestv, bestv+9, -INIT);
    fill(bestc, bestc+9, 0);
    assert(0 <= p && p < 9);
    for (int col=0; col+width[p] <= 9; ++col) {
        int score = 0;
        if (!place_piece(p, col, false)) continue;
        for (int i=0; i<9; ++i) {
            if (board[i].count() == 9) score += 5;
            if (TASK == "1" && board[i].count() == 8) score -= 2;
        }
        for (int i=0; i<rp.size(); ++i) {
            if (board[rp[i]+1][cp[i]]) ++score;
        }
        for (int i=0; i<rp.size(); ++i) {
            board[rp[i]][cp[i]] = false;
        }
        int i = *max_element(rp.begin(), rp.end());
        if (bestv[i] < score) {
            bestv[i] = score;
            bestc[i] = col;
        }
    }
}

ifstream fin((string("tiny.i") + TASK));
ofstream fout((string("tiny.0") + TASK));

int ans[MN];
void solve1() {
    for (int i=0; i<N; ++i) {
        int empty = 9 - board[8].count();
        //cerr << "Move: " << i << ' ' << A[i] << endl;
        int spot = -1, val = -INIT;
        find_spot(A[i]);
        //for (int i=0; i<9; ++i) { cerr << bestc[i] << ' ' << bestv[i] << endl; } cerr << endl;
        for (int i=0; i<8; ++i) {
            if (val <= bestv[i]) {
                val = bestv[i];
                spot = bestc[i];
            }
        }
        if (A[i] == 2) {
            if (empty != 3 && val <= bestv[8] || val == -INIT) {
                val = bestv[8];
                spot = bestc[8];
            }
        } else if (A[i] == 4) {
            if (empty != 4 && val <= bestv[8] || val == -INIT) {
                val = bestv[8];
                spot = bestc[8];
            }
        } else assert(false);

        //if (i == 179 || i == 180) spot = 6;
        if (i == 163) spot = 4;
        else if (i == 287 || i == 288 || i == 289) spot = 6;
        else if (164 <= i && i <= 354 && (i % 3) == 2 && A[i] == 4) spot = 0;
        else if (164 <= i && i <= 354 && (i % 3) == 0 && A[i] == 4) spot = 3;
        //cerr << "spot: " << spot << endl;
        assert(place_piece(A[i], spot));
        //print();

        fout << spot + 1 << '\n';
    }
}

int find_move(const int p) {
    find_spot(p);

    int spot = -1, val = -INIT;
    for (int i=0; i<9; ++i) {
        if (val <= bestv[i]) {
            val = bestv[i];
            spot = bestc[i];
        }
    }
    return spot;
}

int main() {
    fin.tie(0)->sync_with_stdio(0);
    cin.tie(0)->sync_with_stdio(0);

    cout << "TASK: " << TASK << endl;
    fin >> N;
    for (int i=0; i<N; ++i) {
        fin >> A[i];
        --A[i];
    }
    board[9] = bitset<9>("111111111");

    if (TASK == "1") {
        solve1();
    } else {
        int best = 0;
        vector<int> cur;
        while (true) {
            cur.clear();
            cur.reserve(N);
            for (int i=0; i<9; ++i) board[i].reset();

            int thres = rand() % 60;

            for (int i=0; i<N; ++i) {
                //int move = rand() % 100 > thres ? (rand() % (9 - width[A[i]] + 1)) : find_move(A[i]);
                int move;
                print();
                cout << A[i] << endl;
                cin >> move;
                if (place_piece(A[i], move)) cur.push_back(move+1);
                else break;
            }

            if (best < cur.size()) {
                best = cur.size();
                fout.close();
                fout = ofstream((string("xtiny.0") + TASK));
                for (const int x: cur) {
                    fout << x << '\n';
                }
                fout.flush();
            }
        }
    }
}

