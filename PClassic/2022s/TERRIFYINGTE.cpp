#include <bits/stdc++.h>

using namespace std;

using dbl=long double;

const int N = 3;

// CLRS algo book go brrr
// Ax = B, where A is matrix and x, B are vectors

dbl A[N][N], B[N];
dbl x[N];

dbl L[N][N], U[N][N];
int P[N];

// CLRS page 821
// solves for x given L, U, P
void LUP_solve() {  // uses x as y
    for (int i=0; i<N; ++i) {
        x[i] = B[P[i]];
        for (int j=0; j<i; ++j) {
            x[i] -= L[i][j] * x[j];
        }
    }
    for (int i=N-1; i>=0; --i) {
        for (int j=i+1; j<N; ++j) {
            x[i] -= U[i][j] * x[j];
        }
        x[i] /= U[i][i];
    }
}

dbl tmp[N][N];
// CLRS page 824
void LUP_decomp() {
    for (int i=0; i<N; ++i) {
        P[i] = i;
        for (int j=0; j<N; ++j) {
            tmp[i][j] = A[i][j];
        }
    }
    for (int k=0; k<N; ++k) {
        dbl p = 0;
        int k_swap = k;
        for (int i=k; i<N; ++i) {
            if (p < abs(tmp[i][k])) {
                p = abs(tmp[i][k]);
                k_swap = i;
            }
        }
        assert(p > 0);
        swap(P[k], P[k_swap]);
        swap(tmp[k], tmp[k_swap]);

        for (int i=k+1; i<N; ++i) {
            tmp[i][k] /= tmp[k][k];
            for (int j=k+1; j<N; ++j) {
                tmp[i][j] -= tmp[i][k] * tmp[k][j];
            }
        }
    }

    for (int i=0; i<N; ++i) {
        for (int j=0; j<N; ++j) {
            L[i][j] = i > j ? tmp[i][j] : 0;
            U[i][j] = i <= j ? tmp[i][j] : 0;
        }
    }
}

vector<double> terrifyingTetra(const vector<vector<double>>& ps) {
    for (int i=0; i<3; ++i) {
        vector<double> opp_mid(N);
        for (int j=0; j<N; ++j) {
            A[i][j] = ps[(i+1)%4][j] - ps[i][j];  // perpendicular vector has same coefficients as plane
            opp_mid[j] = (ps[(i+3)%4][j] + ps[(i+2)%4][j]) / 2;  // midpoint of opposite edge
        }
        // Ax + By + Cz = D
        B[i] = A[i][0] * opp_mid[0] + A[i][1] * opp_mid[1] + A[i][2] * opp_mid[2];
    }

    //for (int i=0; i<N; ++i) {
    //    for (int j=0; j<N; ++j) {
    //        cerr << A[i][j] << ' ';
    //    } cerr << B[i] << endl;
    //}
    LUP_decomp();
    LUP_solve();

    for (int i=0; i<N; ++i) {  // not sure if printing "-0.0" is a problem
        x[i] += 1e-12;
    }

    return vector<double>(x, x+3);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int t;
    for (cin >> t; t > 0; t--) {
        vector<vector<double>> points;
        for (int j = 0; j < 4; j++) {
            string point0, point1, point2;
            cin >> point0;
            cin >> point1;
            cin >> point2;
            vector<double> temp;
            temp.push_back(stod(point0));
            temp.push_back(stod(point1));
            temp.push_back(stod(point2));
            points.push_back(temp);
        }
        vector<double> output = terrifyingTetra(points);
        cout << setprecision(1) << fixed;
        for (int j = 0; j < output.size(); j++) {
            cout << (round(output[j] * 10.0) / 10.0);
            if (j < output.size() - 1) {
                cout << " ";
            }
        }
		cout << "\n";
    }
}
