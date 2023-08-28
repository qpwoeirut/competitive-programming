//1032d.cpp created at 02/20/21 21:31:33

#include <bits/stdc++.h>

using namespace std;

#define x real()
#define y imag()

typedef long double dbl;
typedef complex<dbl> pt;

const dbl EPS = 1e-9;

dbl a, b, c;
pt A, B;

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> a >> b >> c;
    dbl px, py;
    cin >> px >> py;
    A = pt(px, py);
    cin >> px >> py;
    B = pt(px, py);

    dbl ans = abs(A.x - B.x) + abs(A.y - B.y);
    if (fabs(a) > EPS && fabs(b) > EPS) {
        pt start_x(-(b * A.y + c) / a, A.y), start_y(A.x, -(a * A.x + c) / b);
        pt target_x(-(b * B.y + c) / a, B.y), target_y(B.x, -(a * B.x + c) / b);

        dbl xx = fabs(A.x - start_x.x) + abs(start_x - target_x) + fabs(B.x - target_x.x);
        dbl xy = fabs(A.x - start_x.x) + abs(start_x - target_y) + fabs(B.y - target_y.y);
        dbl yx = fabs(A.y - start_y.y) + abs(start_y - target_x) + fabs(B.x - target_x.x);
        dbl yy = fabs(A.y - start_y.y) + abs(start_y - target_y) + fabs(B.y - target_y.y);
        ans = min(ans, min({xx, xy, yx, yy}));
    }

    cout << fixed << setprecision(12);
    cout << ans << endl;
}

/*
-1 1 0
-1000000000 -1000000000 1000000000 1000000000

-1000000000 1 0
-1000000000 -1000000000 1000000000 1000000000

-2 1 0
-10 -10 10 10
*/
